
#include "interrupts.h"
#include <p18cxxx.h>
#include "osa.h"
#include "module_motor.h"
#include "logicAnalyzer.h"
#include "main.h"

#ifdef ENABLE_INT2
    #define TRIS_INTR_NULL_SIN  TRISBbits.TRISB2
#endif

#pragma code InterruptVectorHigh = 0x08

static uint16_t cnt_zero_crossing = 0;
static BOOL is_zero_cross = FALSE;  				 //признак перехода через нуль сетевого напряжения
static BOOL  is_impulse_agitator_sensor = FALSE; 	 //признак наличия импульса датчика ворошителя

void InterruptHandlerHigh (void);
void InterruptVectorHigh (void);

void InterruptVectorHigh (void)
{
    _asm
        goto InterruptHandlerHigh //jump to interrupt routine
    _endasm
}


#pragma code
#pragma interrupt InterruptHandlerHigh

/*
Прерывание т/с0 для формирования системного "тика" 1мс
Прерывание т/с3 50мс для формирования временной сетки с шагом 1с 
Прерывание по заднему фронту INT2 (переход через ноль сетевого напряжения 220В)
Прерывание т/с2 215 мкс для формирования программного ШИМа разгона двигателя 
*/
void InterruptHandlerHigh (void)
{
 	OS_EnterInt();
 	if (INTCONbits.TMR0IF)      //отсчёт системного тика 1 мс
    {                           //check for TMR0 overflow
    	//DEBUG_PIN_1_TOGGLE;
        TMR0L=0x48;
    	INTCONbits.TMR0IF = 0;  //clear interrupt flag
       	OS_Timer();
	}
    if(INTCON3bits.INT2IF && INTCON3bits.INT2IE) //прерывание по переходу через ноль сетевого напряжения каждые 20 мс
	{
		INTCON3bits.INT2IF = 0;
		is_zero_cross = TRUE;
		cnt_zero_crossing++;
	}
	if(INTCON3bits.INT1IF && INTCON3bits.INT1IE) //прерывание по заднему фронту на RB1 для опроса датчика ворошителя
	{
		is_impulse_agitator_sensor = TRUE;
		INTCON3bits.INT1IF = 0;
	}
	if(PIR1bits.TMR2IF && PIE1bits.TMR2IE) //период прерывания 205 мкс (для формирования ШИМа разгона двигателя)
	{
		PIR1bits.TMR2IF = 0;
		M_Motor_software_PWM_interrrupt(M_Motor_get_ptr_to_motor_pins());
	}	
	OS_LeaveInt();
}

void Intr_ctor( void )
{
    INTCON = 0x20;                 //disable global and enable TMR0 interrupt
	INTCON2 = 0x84;                //TMR0 high priority
#ifdef ENABLE_INT2
    INTCON3 = 0xD8;		//разрешить внешние прерывания INT2 (для детектирования переходов через нуль 
#else                   //сетевого напряжения)и INT1 (для опроса датчика ворошителя)
	INTCON3 = 0xC8;
#endif
    RCONbits.IPEN = 1;  //enable priority levels
	TMR0H = 0;          //clear timer
	TMR0L = 0;          //clear timer
	T0CON = 0xC5;
	INTCONbits.GIEH = 1; //enable interrupts
    IPR2 = 0x02;        //установить высокий приоритет прерыванию от т/с3
	T2CON = 0;
	PIE1 = 0;
	PIE2 = 0;
    IPR1 = 0x02;                //установить высокий приоритет прерыванию от т/с2
#ifdef ENABLE_INT2    
    TRIS_INTR_NULL_SIN = IN;    //установить на вход пин внешнего прерівания INT2 (имрульс перехода через нуль 220В)
#endif
}

void Intr_set_cnt_zero_crossing(uint8_t value)
{
	cnt_zero_crossing = value;
}

uint16_t Intr_get_cnt_zero_crossing(void)
{
	return cnt_zero_crossing;
}

void Intr_set_is_zero_cross (BOOL value)
{
	is_zero_cross = value;
}

BOOL Intr_get_is_zero_cross(void)
{
	return is_zero_cross;
}

BOOL Intr_get_is_impulse_agitator_sensor(void)
{
	return is_impulse_agitator_sensor;
}

void Intr_set_is_impulse_agitator_sensor (BOOL value)
{
	is_impulse_agitator_sensor = value;
}




