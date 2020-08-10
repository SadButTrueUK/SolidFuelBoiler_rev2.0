#include "module_sound.h"
#include <p18cxxx.h>
#include "module_management.h"
#include "module_logic_inputs.h"

#define TIME_BUTTON_SUBMERGENCE_CONST		75U				//����� ��������� ������ � ��
#define TIME_FLASH_SOUND_CONST				500U			//����� ����� � ��������� ������ � ��
#define SOUND_PIN							LATCbits.LATC5	//��� �����
#define SOUND_TRIS							TRISCbits.TRISC5	//��� �����

typedef struct 
{
	uint16_t time_flash_sound;
	BOOL flag_flash_sound;
	uint16_t time_button_submergence;
}TimeMSound;


/*��������� ������  */
static TimeMSound time_M_Sound = { 0, 0, 0};


/* ���������� ������ */
BOOL button_submergence = 0; 	//���� ��������� ������


/*������ ������ */

void M_Sound_ctor( void )
{
    SOUND_TRIS = OUT;
    SOUND_PIN = OFF;
}

/* ��������� ����� ��������� ������ */
void M_Sound_set_button_submergence (BOOL value)
{
	button_submergence = value;
}


void M_Sound_run (void)
{
	if(M_Mngm_Get_parameters_buffer()->menu_parameters.enable_sound && M_Mngm_Get_state() != STATE_PAUSE)  //���� ���� ��������
	{
		if(button_submergence) 	//���� ����������� ���������� ��������� ������
		{
			SOUND_PIN = !SOUND_PIN;
			//������ ������� ��������� ������
			if(time_M_Sound.time_button_submergence++ == TIME_BUTTON_SUBMERGENCE_CONST)
			{
				time_M_Sound.time_button_submergence = 0;
				SOUND_PIN = OFF;
				button_submergence = OFF;
			}
		}	
		//� ��������� ������ ���� "��������" � �������� TIME_FLASH_SOUND_CONST*2
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
