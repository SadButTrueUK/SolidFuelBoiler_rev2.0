#include "module_sound.h"
#include <p18cxxx.h>
#include "module_management.h"
#include "module_logic_inputs.h"

#define TIME_BUTTON_SUBMERGENCE_CONST		75U				//время подзвучки кнопки в мс
#define TIME_FLASH_SOUND_CONST				500U			//время звука в аварийном режиме в мс
#define SOUND_PIN							LATCbits.LATC5	//пин звука
#define SOUND_TRIS							TRISCbits.TRISC5	//пин звука

typedef struct 
{
	uint16_t time_flash_sound;
	BOOL flag_flash_sound;
	uint16_t time_button_submergence;
}TimeMSound;


/*Структуры модуля  */
static TimeMSound time_M_Sound = { 0, 0, 0};


/* Переменные модуля */
BOOL button_submergence = 0; 	//флаг подзвучки кнопки


/*Методы модуля */

void M_Sound_ctor( void )
{
    SOUND_TRIS = OUT;
    SOUND_PIN = OFF;
}

/* Установка флага подзвучки кнопок */
void M_Sound_set_button_submergence (BOOL value)
{
	button_submergence = value;
}


void M_Sound_run (void)
{
	if(M_Mngm_Get_parameters_buffer()->menu_parameters.enable_sound && M_Mngm_Get_state() != STATE_PAUSE)  //если звук разрешён
	{
		if(button_submergence) 	//если установлено разрешение подзвучки кнопок
		{
			SOUND_PIN = !SOUND_PIN;
			//отсчёт времени подзвучки кнопок
			if(time_M_Sound.time_button_submergence++ == TIME_BUTTON_SUBMERGENCE_CONST)
			{
				time_M_Sound.time_button_submergence = 0;
				SOUND_PIN = OFF;
				button_submergence = OFF;
			}
		}	
		//в состоянии аварии звук "меандром" с периодом TIME_FLASH_SOUND_CONST*2
		if(M_Mngm_Get_state() ==  STATE_FAILURE) 
		{
			SOUND_PIN = time_M_Sound.flag_flash_sound ? OFF : !SOUND_PIN; 
			if(time_M_Sound. time_flash_sound++ == TIME_FLASH_SOUND_CONST)
			{
				time_M_Sound. time_flash_sound = 0;
				time_M_Sound.flag_flash_sound = !time_M_Sound.flag_flash_sound;
				SOUND_PIN = !SOUND_PIN;	
			}	
		}
		else
		{
			if(!button_submergence)  
			{	
				SOUND_PIN = OFF;	
				time_M_Sound.flag_flash_sound = OFF;
			}
		}
	}
	else
	{
		SOUND_PIN = OFF;
		button_submergence = FALSE;
		time_M_Sound.time_button_submergence = 0;
		time_M_Sound.flag_flash_sound = OFF;
	}
}
