#ifndef _MODULE_LOGIC_INPUTS_H_
#define _MODULE_LOGIC_INPUTS_H_

#include "stdint.h"
#include "boardModes.h"

//Коды кнопок
#define CODE_KEY_INC_PRESSED_AND_FREE 		0b00010110U  
#define CODE_KEY_MENU_PRESSED_AND_FREE      0b00011010U
#define CODE_KEY_DEC_PRESSED_AND_FREE		0b00001110U
#define CODE_KEY_ESC_PRESSED_AND_FREE		0b00011100U
#define CODE_KEY_INC_LONG__PRESSED			0b00010110U
#define CODE_KEY_MENU_LONG__PRESSED         0b00011010U
#define CODE_KEY_DEC_LONG__PRESSED 			0b00001110U
#define CODE_KEY_ESC_LONG__PRESSED			0b00011100U
#define NO_KEY_PRESSED                      0b00011110U	

typedef struct
{
	BOOL  ls_dispenser_start_state; 			//дозатор (начальный)
	BOOL  ls_dispenser_finish_state;			//дозатор (конечный)
	BOOL  ls_shatter_start_state;				//заслонка (начальный)			
	BOOL  ls_shatter_finish_state;				//заслонка (конечный)
	BOOL  ls_shatter_after_finish_state;		//концевик после конечного концевика заслонки (для режима чистки дымохода)
	BOOL  ls_agitator_state;					//ворошитель
	BOOL  ls_hopper_cover_state;				//крышка бункера
    #ifdef ENABLE_ASH_CLEANER_INDUCTIVE_SENSORS
        BOOL  ls_clean_ash_start_state;             //чистка золы (стартовый)
        BOOL  ls_clean_ash_finish_state;            //чистка золы (финишный)
    #else
        BOOL overheat;     //датчик перегрева
    #endif
}LimitSwitch;	


/*Объявление структуры состояния кнопки  */
typedef struct 
{
	BOOL Any_Key_pressed ; 	 	//флаг кнопка нажата
	BOOL Long_pressed ;     		//флаг длительного нажатия кнопки
	uint8_t M_LI_Code_Key;	  	//код нажатой кнопки		 	
}KeyState;


void 		 M_LI_Run(void);
void 		 M_LI_Key_Question(void);
BOOL 		 M_LI_is_LS_worked(uint8_t ls_pin, BOOL ls_direction);
KeyState*    M_LI_Get_Key_State(void);
LimitSwitch* M_LI_Get_Limit_Switches(void);
void 	     M_LI_ls_question(void);
BOOL* 		 M_LI_get_ptr_to_ls(void);
void 		 M_LI_set_ptr_to_ls(BOOL* ls);
void         M_LI_ctor( void );

#endif