#include "module_logic_inputs.h"
#include "module_management.h"
#include "module_sound.h"
#include "menu.h"
#include <p18cxxx.h>


/*Определения*/
//Ножки портов в/в концевиков(через указатели не выходит, делаем говнокодом)
#define LS_DISPENSER_START_PIN 		 PORTBbits.RB5       //дозатор(стартовый)
#define LS_DISPENSER_START_TRIS		 TRISBbits.TRISB5
#define LS_DISPENSER_FINISH_PIN		 PORTJbits.RJ7       //дозатор(финишный)
#define LS_DISPENSER_FINISH_TRIS     TRISJbits.TRISJ7
#define LS_SHATTER_START_PIN		 PORTCbits.RC0       //заслонка(стартовый)
#define LS_SHATTER_START_TRIS		 TRISCbits.TRISC0       
#define LS_SHATTER_FINISH_PIN		 PORTJbits.RJ4       //заслонка(финишный)
#define LS_SHATTER_FINISH_TRIS		 TRISJbits.TRISJ4
#define LS_HOPPER_COVER_PIN			 PORTBbits.RB4       //крышка
#define LS_HOPPER_COVER_TRIS		 TRISBbits.TRISB4
#define LS_AGITATOR_PIN				 PORTBbits.RB1       //ворошитель
#define LS_AGITATOR_TRIS			 TRISBbits.TRISB1 
#define LS_SHATTER_AFTER_FINISH_PIN	 PORTJbits.RJ6       //заслонка(после финишного)
#define LS_SHATTER_AFTER_FINISH_TRIS TRISJbits.TRISJ6

#ifdef ENABLE_ASH_CLEANER_INDUCTIVE_SENSORS
    #define LS_CLEAN_ASH_START_PIN       PORTCbits.RC1       //чистка золы (стартовый)
    #define LS_CLEAN_ASH_START_TRIS      TRISCbits.TRISC1   
    #define LS_CLEAN_ASH_FINISH_PIN      PORTCbits.RC2       //чистка золы (финишный)
    #define LS_CLEAN_ASH_FINISH_TRIS     TRISCbits.TRISC2
#else
    #define SENSOR_OVERHEAT_PIN       PORTCbits.RC1       //чистка золы (стартовый)
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


//Разрешение внутренних подтягивающих резисторов на PORTB, PORTJ
#define PULLUPS_ENABLE \
{                       \
    INTCON2bits.RBPU = 0; \
	PORTGbits.RJPU = 1; \
}

//Запрет внутренних подтягивающих резисторов на PORTB, PORTJ
#define PULLUPS_DISABLE \
{                       \
    INTCON2bits.RBPU = 1; \
	PORTGbits.RJPU = 0; \
}


KeyState M_LI_Key_State = {0, 0, 0};

LimitSwitch M_LI_Limit_Sw = {0};
BOOL* ptr_to_ls = &(M_LI_Limit_Sw.ls_shatter_after_finish_state);

//Функция инициализации модуля обработки логических входов
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
        SENSOR_OVERHEAT_TRIS = IN;  //чистка золы (стартовый)
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

//Опрос концевиков (или индуктивных датчиков)
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

//Опров кнопок
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
    
    temp_PORTB += temp_PORTJ; 	//упаковка в temp_PORTB прочитанных кнопок (биты 3,2,1,0)
	temp_PORTB <<= 1; 
	if(!M_LI_Key_State.Any_Key_pressed) //если никакая кнопка не была нажата ранее
	{
		if (temp_PORTB != NO_KEY_PRESSED)   //какая-либо кнопка нажата
		{
			if(M_LI_accum_pressed++ == THRESHOLD_ACCUMULATION) //накоплен порог нажатия на кнопку
			{
				
				M_LI_Key_State.M_LI_Code_Key = temp_PORTB; 
				M_LI_Key_State.Any_Key_pressed = ON;	
				M_LI_Key_State.Long_pressed = ON; //установить флаг длительного нажатия
				M_LI_accum_pressed = 0; 
				M_Sound_set_button_submergence (ON);  //установить флаг подзвучки кнопки
			}
		}
	}
	else 
	{
			if (temp_PORTB == NO_KEY_PRESSED) //кнопка нажата и отпущена (короткое нажатие)
			{
				if(M_LI_Key_State.Long_pressed)
				{	
					M_LI_Key_State.M_LI_Code_Key &= 0x7E;
					M_LI_Key_State.M_LI_Code_Key += 0x80;  //маркер того, что кнопка нажата и отпущена
				}
				M_LI_Key_State.Any_Key_pressed = FALSE;	
				M_LI_accum_pressed = 0;
				M_LI_Key_State.Long_pressed = FALSE;
			}
			else //если кнопка нажата и не была отпущена при коротком нажатии/отпускании 
			{
				if(M_LI_Key_State.Long_pressed)
				{
					if(M_LI_accum_pressed++ >= THRESHOLD_LONG_PRESSED) // прошло время длительного нажатия CountLongPressed 
					{
						M_LI_accum_pressed = 0;
						M_LI_Key_State.Long_pressed = FALSE;
						M_LI_Key_State.M_LI_Code_Key &= 0x7E;
						M_LI_Key_State.M_LI_Code_Key += 0x01;
						M_LI_Key_State.Any_Key_pressed = TRUE;	
						M_Sound_set_button_submergence (ON);  //установить флаг подзвучки кнопки
					}
				}
			}
	}
}

void M_LI_Run(void)
{
		
	//Опрос кнопок (не опрашивать в режиме "Пауза")
	if(M_Mngm_Get_state() != STATE_PAUSE)
	{
		//Опрос кнопок
        M_LI_Key_Question();
		
		//Отработка кнопок
		Menu_Key_handler(&M_LI_Key_State);	
	}	
		/*Опрос концевиков и заполнение структуры состояний концевиков 
        (сделано говнокодом, так как при работе с портами через 
		указатели лажа) */
		M_LI_ls_question();
	
}

