#include "stdint.h"
#include "module_fan.h"
#include "module_indication.h"
#include "interrupts.h"
#include "module_management.h"
#include "main.h"
#include <p18cxxx.h>


#define THRESHOLD_ZERO_CROSS 			480U	//порог накоплени€ количества переходов через нуль дл€ определени€ наличи€ напр€жени€ ~220¬
#define M_FAN_WAITING					1
#define M_FAN_FAILURE					2
#define M_FAN_WORK_OR_OFF				3
#define M_FAN_WORK_CYCLE_TIMER          4
#define TIME_CHECK_SYNCHRO_IMPULSE		25U //25мс

#define HALF_SINUS_PERIOD_MS			10
#define FAN_PIN							LATFbits.LATF2
#define FAN_TRIS                        TRISFbits.TRISF2
#define TIMEOUT_TASK_FAN				1
#define TIME_TRIAK_IS_ON				1
#define FIRST_HALF_SINUS_PERIOD			0
#define SECOND_HALF_SINUS_PERIOD		1
#define FAN_MAX_LEVEL_ROTATION_SPEED	8U
#define MIN_FAN_LEVEL					2


typedef struct 
{
	uint16_t time_detect_zero_cross;
	uint16_t time_before_triac_is_on;
}TIME_M_Fan;


const rom uint16_t M_fan_time_accum_zero_cross = 10000;  //10 с - врем€ накоплени€ переходов через ноль напр€жени€ 220¬ 

/* ѕеременные модул€ */
BOOL M_fan_is_220V = ON;
BOOL ctrl_fan = FALSE;
uint8_t M_fan_state = M_FAN_WAITING;
uint8_t M_fan_previous_state = M_FAN_WAITING;
uint8_t level_fan = MIN_FAN_LEVEL;
uint8_t step_force_fan = 0;
uint16_t timer_force_fan = 0;


/* —труктуры модул€  */
TIME_M_Fan time_M_Fan = {0};



void M_Fan_ctor( void )
{
    FAN_TRIS = OUT;
    FAN_PIN = OFF;		
}

void M_fan_set_level_fan(uint8_t value)
{
	level_fan = value;
}

/* ‘ункции*/
void M_fan_set_ctrl_fan (BOOL value)
{
	ctrl_fan = value;
}

BOOL M_fan_get_ctrl_fan(void)
{
	return ctrl_fan;
}

BOOL M_fan_get_is_220V(void)
{
	return M_fan_is_220V;
}

/* ‘ункци€ проверки наличи€ 220¬  */
BOOL  M_fan_check_220V(void)
{
	#ifdef NO_220V_CONTROL
		M_fan_is_220V = ON;
	#else		
		if(time_M_Fan.time_detect_zero_cross++ >= M_fan_time_accum_zero_cross)
		{
			time_M_Fan.time_detect_zero_cross = 0;
			M_fan_is_220V = (Intr_get_cnt_zero_crossing() >= THRESHOLD_ZERO_CROSS);
			Intr_set_cnt_zero_crossing(0);
		}	
	#endif
	return M_fan_is_220V;
}

void M_fan_clear_timeouts(void)
{
	time_M_Fan.time_before_triac_is_on = step_force_fan = timer_force_fan = 0;
}

void M_fan_run(void)
{
	
 	#define LEVEL_FORCE_FAN 	4U
	#define TIMEOUT_FORCE_FAN	3500U
	
	if(M_Ind_Get_state() == STATE_IND_INIT)
		return;
	
	M_fan_check_220V(); //проверка наличи€ 220¬
	
	if(M_Mngm_Get_state() == STATE_PAUSE)	
	{
		FAN_PIN = OFF;	
	}
	else
	{
		switch(M_fan_state)
		{
			case M_FAN_WAITING:
				M_fan_previous_state = M_fan_state;
				/* отладка (в рабочей версии убрать)*/ //ctrl_fan = TRUE;  
				if(!M_fan_is_220V) 
				{
					M_fan_state = M_FAN_FAILURE; 	
				}
				else
				{
					if( ctrl_fan ) 
						M_fan_state = M_FAN_WORK_OR_OFF;
				}
			break;
			case M_FAN_FAILURE:
				if(M_fan_is_220V) 		//условие выхода из состо€ни€ аварии
				{		
					M_fan_state = M_fan_previous_state;
				}
				else
				{
					FAN_PIN = OFF;
				}
			break;
			case M_FAN_WORK_OR_OFF:
				M_fan_previous_state = M_fan_state;
				if(!M_fan_is_220V) 
				{
					M_fan_state = M_FAN_FAILURE; 	
					Intr_set_is_zero_cross (FALSE); 
					M_fan_clear_timeouts();
				}
				else
				{
					if( !ctrl_fan )
					{	
						M_fan_state = M_FAN_WAITING;
						FAN_PIN = OFF;	
						M_fan_clear_timeouts();
					}
					else
					{
						//0 - форсированный старт (на 5 секунд включить вентил€тор на 3-ем уровне), 1 - работа по передаваемому level_fan
						/*
						switch (step_force_fan) 
						{
							case 0:
								if(timer_force_fan ++ >= TIMEOUT_FORCE_FAN)
								{
									timer_force_fan = 0;
									step_force_fan++;		
								}
								else
								{
									M_Fan_work_fan(LEVEL_FORCE_FAN);
								}
							break;
							case 1:
								M_Fan_work_fan(level_fan);
							break;
						}
					    */
					    M_Fan_work_fan(level_fan);
					}
				}
			break;
		}
	}
}

/* ‘ункци€, в которой устанавливаетс€ врем€ работы симистора в зависимости от уровн€, заданного в меню */
void M_Fan_work_fan ( uint8_t level )
{
	static uint8_t counter = 0;
	static BOOL cnt_half_period = FIRST_HALF_SINUS_PERIOD;
	
		
	if( level == FAN_MAX_LEVEL_ROTATION_SPEED )  //при максимальном уровне оборотов вентил€тор всегда включен
	{
		FAN_PIN = ON;		
	}
	else if (level == 1U)
	{	
		FAN_PIN = OFF;
	}
	else
	{
		if (Intr_get_is_zero_cross())		//если был переход через нуль сетевого напр€жени€
		{
		
				switch (counter)  //реализаци€ фазового регулировани€ оборотов вентил€тора
				{
					case 0:  	//отсчЄт времени паузы, затем включение симистора
						if(time_M_Fan.time_before_triac_is_on++ < (HALF_SINUS_PERIOD_MS - level - TIMEOUT_TASK_FAN - 1))
							break;
						else
						{
							time_M_Fan.time_before_triac_is_on = 0;
							FAN_PIN = ON;		
							counter++;	
						}
						break;
					case 1:  	//выключение симистора и отсчЄт времени до конца полупериода
						FAN_PIN = OFF;
						counter = 0;
						Intr_set_is_zero_cross (FALSE); 	 //в конце полупериода синуса (10мс) сбросить флаг синхроимпульса
						break;
				}
			}
		
		else
		{
			cnt_half_period = FIRST_HALF_SINUS_PERIOD;	
		}
	}
}