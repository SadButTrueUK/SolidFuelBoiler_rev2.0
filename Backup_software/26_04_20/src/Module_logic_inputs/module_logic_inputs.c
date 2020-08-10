#include "module_logic_inputs.h"
#include "module_management.h"
#include "module_sound.h"
#include "menu.h"
#include <p18cxxx.h>


/*�����������*/
//����� ������ �/� ����������(����� ��������� �� �������, ������ ����������)
#define LS_DISPENSER_START_PIN 		 PORTBbits.RB5       //�������(���������)
#define LS_DISPENSER_START_TRIS		 TRISBbits.TRISB5
#define LS_DISPENSER_FINISH_PIN		 PORTJbits.RJ7       //�������(��������)
#define LS_DISPENSER_FINISH_TRIS     TRISJbits.TRISJ7
#define LS_SHATTER_START_PIN		 PORTCbits.RC0       //��������(���������)
#define LS_SHATTER_START_TRIS		 TRISCbits.TRISC0       
#define LS_SHATTER_FINISH_PIN		 PORTJbits.RJ4       //��������(��������)
#define LS_SHATTER_FINISH_TRIS		 TRISJbits.TRISJ4
#define LS_HOPPER_COVER_PIN			 PORTBbits.RB4       //������
#define LS_HOPPER_COVER_TRIS		 TRISBbits.TRISB4
#define LS_AGITATOR_PIN				 PORTBbits.RB1       //����������
#define LS_AGITATOR_TRIS			 TRISBbits.TRISB1 
#define LS_SHATTER_AFTER_FINISH_PIN	 PORTJbits.RJ6       //��������(����� ���������)
#define LS_SHATTER_AFTER_FINISH_TRIS TRISJbits.TRISJ6

#ifdef ENABLE_ASH_CLEANER_INDUCTIVE_SENSORS
    #define LS_CLEAN_ASH_START_PIN       PORTCbits.RC1       //������ ���� (���������)
    #define LS_CLEAN_ASH_START_TRIS      TRISCbits.TRISC1   
    #define LS_CLEAN_ASH_FINISH_PIN      PORTCbits.RC2       //������ ���� (��������)
    #define LS_CLEAN_ASH_FINISH_TRIS     TRISCbits.TRISC2
#else
    #define SENSOR_OVERHEAT_PIN       PORTCbits.RC1       //������ ���� (���������)
    #define SENSOR_OVERHEAT_TRIS      TRISCbits.TRISC1
#endif

#define KEY_INC_TRIS                 TRISJbits.TRISJ3
#define KEY_DEC_TRIS                 TRISBbits.TRISB0   
#define KEY_MENU_TRIS                TRISJbits.TRISJ2
#define KEY_ESC_TRIS                 TRISJbits.TRISJ1

#define LS_IS_WORKED_TO_NC              1
#define LS_IS_WORKED_TO_NO              0


#define NO_KEY_PRESSED_ON_PORTJ         0b00001110U
#define NO_KEY_PRESSED_ON_PORTB         0b00000001U
#define THRESHOLD_LONG_PRESSED          5000U
#define THRESHOLD_ACCUMULATION          10U


//���������� ���������� ������������� ���������� �� PORTB, PORTJ
#define PULLUPS_ENABLE \
{                       \
    INTCON2bits.RBPU = 0; \
	PORTGbits.RJPU = 1; \
}

//������ ���������� ������������� ���������� �� PORTB, PORTJ
#define PULLUPS_DISABLE \
{                       \
    INTCON2bits.RBPU = 1; \
	PORTGbits.RJPU = 0; \
}


KeyState M_LI_Key_State = {0, 0, 0};

LimitSwitch M_LI_Limit_Sw = {0};
BOOL* ptr_to_ls = &(M_LI_Limit_Sw.ls_shatter_after_finish_state);

//������� ������������� ������ ��������� ���������� ������
void M_LI_ctor( void )
{

    LS_DISPENSER_START_TRIS	     = IN;
    LS_DISPENSER_FINISH_TRIS     = IN;
    LS_SHATTER_START_TRIS		 = IN; 
    LS_SHATTER_FINISH_TRIS		 = IN; 
    LS_HOPPER_COVER_TRIS		 = IN; 
    LS_AGITATOR_TRIS			 = IN; 
    LS_SHATTER_AFTER_FINISH_TRIS = IN;
    
    #ifdef ENABLE_ASH_CLEANER_INDUCTIVE_SENSORS
        LS_CLEAN_ASH_START_TRIS      = IN;
        LS_CLEAN_ASH_FINISH_TRIS     = IN;
    #else
        SENSOR_OVERHEAT_TRIS = IN;  //������ ���� (���������)
    #endif 
    KEY_INC_TRIS  = IN;
    KEY_DEC_TRIS  = IN;
    KEY_MENU_TRIS = IN;
    KEY_ESC_TRIS  = IN;
}

BOOL* M_LI_get_ptr_to_ls(void)
{
	return ptr_to_ls;
}

void M_LI_set_ptr_to_ls(BOOL* ls)
{
	ptr_to_ls = ls;
}

LimitSwitch* M_LI_Get_Limit_Switches(void)
{
	return &M_LI_Limit_Sw;
}

KeyState* M_LI_Get_Key_State(void) 
{
	return &M_LI_Key_State;
}


BOOL M_LI_is_LS_worked(uint8_t ls_pin, BOOL ls_direction) 
{
	return ls_pin ^ ls_direction;
}

//����� ���������� (��� ����������� ��������)
void M_LI_ls_question(void)
{
	#ifdef  ENABLE_PULLUPS_ON_PORTB_AND_PORTJ
        PULLUPS_ENABLE;
    #endif
    M_LI_Limit_Sw.ls_dispenser_start_state =      M_LI_is_LS_worked(LS_DISPENSER_START_PIN, LS_IS_WORKED_TO_NC);  
	M_LI_Limit_Sw.ls_dispenser_finish_state =     M_LI_is_LS_worked(LS_DISPENSER_FINISH_PIN, LS_IS_WORKED_TO_NC);
	M_LI_Limit_Sw.ls_shatter_start_state =        M_LI_is_LS_worked(LS_SHATTER_START_PIN, LS_IS_WORKED_TO_NC);  
	M_LI_Limit_Sw.ls_shatter_finish_state =       M_LI_is_LS_worked(LS_SHATTER_FINISH_PIN, LS_IS_WORKED_TO_NC);
	M_LI_Limit_Sw.ls_agitator_state =             M_LI_is_LS_worked(LS_AGITATOR_PIN, LS_IS_WORKED_TO_NC);  
	M_LI_Limit_Sw.ls_hopper_cover_state =         M_LI_is_LS_worked(LS_HOPPER_COVER_PIN, LS_IS_WORKED_TO_NC);
	M_LI_Limit_Sw.ls_shatter_after_finish_state = M_LI_is_LS_worked(LS_SHATTER_AFTER_FINISH_PIN, LS_IS_WORKED_TO_NC);
    #ifdef  ENABLE_PULLUPS_ON_PORTB_AND_PORTJ
        PULLUPS_DISABLE;
    #endif
    #ifdef ENABLE_ASH_CLEANER_INDUCTIVE_SENSORS
        M_LI_Limit_Sw.ls_clean_ash_start_state =      M_LI_is_LS_worked(LS_CLEAN_ASH_START_PIN, LS_IS_WORKED_TO_NC);
        M_LI_Limit_Sw.ls_clean_ash_finish_state =     M_LI_is_LS_worked(LS_CLEAN_ASH_FINISH_PIN, LS_IS_WORKED_TO_NC);
    #else
        M_LI_Limit_Sw.overheat =  M_LI_is_LS_worked(SENSOR_OVERHEAT_PIN, LS_IS_WORKED_TO_NC);
    #endif     
}

//����� ������
void M_LI_Key_Question(void)
{
	uint8_t temp_PORTB, temp_PORTJ;
	static uint16_t M_LI_accum_pressed = 0;
	
	#ifdef  ENABLE_PULLUPS_ON_PORTB_AND_PORTJ
        PULLUPS_ENABLE;
    #endif
	temp_PORTB = PORTB & NO_KEY_PRESSED_ON_PORTB;
	temp_PORTJ = PORTJ & NO_KEY_PRESSED_ON_PORTJ;
	#ifdef  ENABLE_PULLUPS_ON_PORTB_AND_PORTJ
        PULLUPS_DISABLE;
    #endif
    
    temp_PORTB += temp_PORTJ; 	//�������� � temp_PORTB ����������� ������ (���� 3,2,1,0)
	temp_PORTB <<= 1; 
	if(!M_LI_Key_State.Any_Key_pressed) //���� ������� ������ �� ���� ������ �����
	{
		if (temp_PORTB != NO_KEY_PRESSED)   //�����-���� ������ ������
		{
			if(M_LI_accum_pressed++ == THRESHOLD_ACCUMULATION) //�������� ����� ������� �� ������
			{
				
				M_LI_Key_State.M_LI_Code_Key = temp_PORTB; 
				M_LI_Key_State.Any_Key_pressed = ON;	
				M_LI_Key_State.Long_pressed = ON; //���������� ���� ����������� �������
				M_LI_accum_pressed = 0; 
				M_Sound_set_button_submergence (ON);  //���������� ���� ��������� ������
			}
		}
	}
	else 
	{
			if (temp_PORTB == NO_KEY_PRESSED) //������ ������ � �������� (�������� �������)
			{
				if(M_LI_Key_State.Long_pressed)
				{	
					M_LI_Key_State.M_LI_Code_Key &= 0x7E;
					M_LI_Key_State.M_LI_Code_Key += 0x80;  //������ ����, ��� ������ ������ � ��������
				}
				M_LI_Key_State.Any_Key_pressed = FALSE;	
				M_LI_accum_pressed = 0;
				M_LI_Key_State.Long_pressed = FALSE;
			}
			else //���� ������ ������ � �� ���� �������� ��� �������� �������/���������� 
			{
				if(M_LI_Key_State.Long_pressed)
				{
					if(M_LI_accum_pressed++ >= THRESHOLD_LONG_PRESSED) // ������ ����� ����������� ������� CountLongPressed 
					{
						M_LI_accum_pressed = 0;
						M_LI_Key_State.Long_pressed = FALSE;
						M_LI_Key_State.M_LI_Code_Key &= 0x7E;
						M_LI_Key_State.M_LI_Code_Key += 0x01;
						M_LI_Key_State.Any_Key_pressed = TRUE;	
						M_Sound_set_button_submergence (ON);  //���������� ���� ��������� ������
					}
				}
			}
	}
}

void M_LI_Run(void)
{
		
	//����� ������ (�� ���������� � ������ "�����")
	if(M_Mngm_Get_state() != STATE_PAUSE)
	{
		//����� ������
        M_LI_Key_Question();
		
		//��������� ������
		Menu_Key_handler(&M_LI_Key_State);	
	}	
		/*����� ���������� � ���������� ��������� ��������� ���������� 
        (������� ����������, ��� ��� ��� ������ � ������� ����� 
		��������� ����) */
		M_LI_ls_question();
	
}

