#include "module_indication.h"
#include "module_management.h"
#include "module_analog_inputs.h"
#include "menu.h"
#include "module_motor.h"
#include "module_logic_inputs.h"
#include "main.h"
#include <p18cxxx.h>
#include "osa.h"
#include "spi.h"
#include "logicAnalyzer.h"
#include "boardModes.h"

#define INDEX_OF_BLANK_SYMBOL	(sizeof (M_Ind_PortraitsFirstInd) / sizeof (M_Ind_PortraitsFirstInd[0])) - 1 
#define IT_IS_A_TEXT_SYM_AREA 	(sizeof (M_Ind_PortraitsFirstInd) / sizeof (M_Ind_PortraitsFirstInd[0])) - 16
#define INDEX_OF_AREA_FUEL_TYPE (sizeof (M_Ind_PortraitsFirstInd) / sizeof (M_Ind_PortraitsFirstInd[0])) - 9

#define ANODE_FIRST_PORT			  LATE
#define ANODE_SECOND_PORT			  LATD
#define ANODES_ARE_OFF_ON_FIRST_PORT  0b11000000
#define ANODES_ARE_OFF_ON_SECOND_PORT 0b00001111
#define ANODE_1_PIN                   LATEbits.LATE6
#define ANODE_1_TRIS                  TRISEbits.TRISE6
#define ANODE_2_PIN                   LATEbits.LATE7
#define ANODE_2_TRIS                  TRISEbits.TRISE7
#define ANODE_3_PIN                   LATDbits.LATD0
#define ANODE_3_TRIS                  TRISDbits.TRISD0
#define ANODE_4_PIN                   LATDbits.LATD1
#define ANODE_4_TRIS                  TRISDbits.TRISD1
#define ANODE_5_PIN                   LATDbits.LATD2
#define ANODE_5_TRIS                  TRISDbits.TRISD2
#define ANODE_6_PIN                   LATDbits.LATD3
#define ANODE_6_TRIS                  TRISDbits.TRISD3

#define QUANTITY_OF_LEDS		 	  3U
#define LED_BICOLOR_GREEN_PIN		  LATEbits.LATE5
#define LED_BICOLOR_GREEN_TRIS        TRISEbits.TRISE5
#define LED_BICOLOR_RED_PIN           LATEbits.LATE4
#define LED_BICOLOR_RED_TRIS          TRISEbits.TRISE4
#define LED_FAN_PIN					  LATEbits.LATE3
#define LED_FAN_TRIS                  TRISEbits.TRISE3
#define LED_PUMP_PIN                  LATEbits.LATE2
#define LED_PUMP_TRIS                 TRISEbits.TRISE2

#define ANODE_IS_OFF                  1
#define ANODE_IS_ON                   0




#define LEFT_INDICATOR				  0
#define MIDDLE_INDICATOR			  1
#define RIGHT_INDICATOR				  2

#define NO_BLINKING					  0U
#define BLINKING_RED				  1
#define BLINKING_GREEN				  2
#define BLINKING_YELLOW				  3
#define BLINKING_FAN_PIN			  4
#define BLINKING_PUMP_PIN             5
#define INDEX_OF_BICOLOR_LED		  0
#define INDEX_OF_FAN_LED			  1
#define INDEX_OF_PUMP_LED			  2


//****** КОНСТАНТЫ***********************************

/*Таблица портретов для семисегментного индикатора с общим катодом
   _ A _
  |     |
  F     B
  |_ G _|
  |     |
  E     C
  |_ D _|.H 
  
  |Символ   | Сегменты   |
     0	 	 	ABCDEF	 		
     1	   		BC	
     2	   		ABDEG	
     3  		ABCDG
     4     		BCFG
     5  		ACDFG
     6     		ACDEFG
     7  		ABC
     8  		ABCDEFG
     9     		ABCDFG
     А  		ABCEFG
     P 		 	ABEFG
     U 			BCDEF
     Е   		ADEFG
     C    		ADEF
     L    		DEF     
     У	    	BCDFG	
     Б	    	ACDEFG
     П	    	ABCEF
     t	    	DEFG
  	 F			AEFG
  	 d			BCDEG
     H          BCEFG 	 
 
  |Бит|		| Сегмент | - первый индикатор (HL4)
    7     		B
    6   		E	
    5	  		F
    4	  		A
    3	  		D
    2	  		H
    1	  		C
    0	  		G
 
   |Бит|	| Сегмент | - второй индикатор (HL5)
    7     		A
    6   		G	
    5	  		F
    4	  		B
    3	  		C
    2	  		H
    1	  		D
    0	  		E
 */
const rom uint8_t M_Ind_PortraitsFirstInd[] =
{
    0b00000101,		//0 ABCDEF 
    0b01111101,		//1 BC	
    0b00100110, 	//2 ABDEG 
    0b01100100,		//3 ABCDG 
    0b01011100,		//4 BCFG
    0b11000100,		//5 ACDFG
    0b10000100,		//6 ACDEFG
    0b01101101,		//7 ABC
    0b00000100,		//8	ABCDEFG
    0b01000100,		//9 ABCDFG
    0b00001100,		//A ABCEFG
    0b00001110,		//P ABEFG
    0b00010101,		//U BCDEF
    0b10000110,		//E ADEFG 
    0b10000111,		//C ADEF
    0b10010111,		//L DEF
    0b11000100,		//S (как 5) ACDFG
    0b01010100,		//У BCDFG
    0b10000100,		//Б (как 6) ACDEFG
    0b00001101,		//П ABCEF
    0b10010110,		//типа t DEFG
    0b10001110, 	//символ F AEFG
    0b00110100,		//символ d BCDEG
    0b00011100,		//H BCEFG
    0b01111101,		//I BC	
    0b11111111  	//пустой символ
}; 

const rom uint8_t M_Ind_PortraitsSecondInd[] =
{
    0b01000100,		//0 ABCDEF 
    0b11100111,		//1 BC	
    0b00101100, 	//2 ABDEG 
    0b00100101,		//3 ABCDG 
    0b10000111,		//4 BCFG
    0b00010101,		//5 ACDFG
    0b00010100,		//6 ACDEFG
    0b01100111,		//7 ABC
    0b00000100,		//8	ABCDEFG
    0b00000101,		//9 ABCDFG
    0b00000110,		//A ABCEFG
    0b00001110,		//P ABEFG
    0b11000100,		//U BCDEF
    0b00011100,		//E ADEFG 
    0b01011100,		//C ADEF
    0b11011100,		//L DEF
    0b00010101,		//S (как 5) ACDFG
    0b10000101,		//У BCDFG
    0b00010100,		//Б (как 6) ACDEFG
    0b01000110,		//П ABCEF
    0b10011100,		//типа t DEFG
    0b00011110, 	//символ F AEFG
    0b10100100,		//символ d BCDEG
    0b10000110,		//H BCEFG
    0b11100111,		//1 BC	
    0b11111111  	//пустой символ
};
const rom uint8_t* ptrTablePortraits[QUANTITY_OF_SEVEN_SEGMENT_INDICATORS] = { M_Ind_PortraitsFirstInd, M_Ind_PortraitsSecondInd };
  

const rom uint8_t decimals[] = {100,10,1,0};

//Константа времён для отсчёта временных интервалов, использующихся в модуле индикации
const rom uint16_t M_Ind_time_const[] = 
{
	5,  //5 секунд для отсчёта времени отображения версии ПО
	500  //500 мс для отсчёта времени мигания (как семисегментного индикатора, так и светодиодов)
};

#define NO_DOT								0b11111111
#define IS_DOT								0b11111011
#define INDEX_IS_DOT						0
#define INDEX_NO_DOT						1
#define OFFSET_TO_SYMBOL_A                  0
#define OFFSET_TO_SYMBOL_P                  1
#define OFFSET_TO_SYMBOL_U                  2
#define OFFSET_TO_SYMBOL_E					3
#define OFFSET_TO_SYMBOL_C                  4
#define OFFSET_TO_SYMBOL_L					5
#define OFFSET_TO_SYMBOL_S                  6
#define OFFSET_TO_SYMBOL_t					10
#define OFFSET_TO_SYMBOL_F					11
#define OFFSET_TO_SYMBOL_d					12
#define OFFSET_TO_SYMBOL_H                  13
#define OFFSET_TO_SYMBOL_I                  14
#define LEFT_SYMBOL_WITH_DOT				1
#define LEFT_SYMBOL_NO_DOT                  0


typedef struct 
{
	uint16_t time_init;
	uint16_t time_blink;
	uint16_t time_auto_exit;
	uint16_t time_blink_LED;
}TIME_M_Ind;

typedef struct 
{
	BOOL Flag_Blink_seven_segm;                                     //флаг мигания 7-сегментного индикатора
	int8_t index_of_text_sym[QUANTITY_OF_FAMILIARITY];             //смещение до поля текстовых символов A,P,U,E,C,L
	uint8_t data[QUANTITY_OF_FAMILIARITY];                          //выводимые данные
	uint8_t	dot[QUANTITY_OF_FAMILIARITY];                           //для вывода точки	
	const rom uint8_t const_dot[2];
}Ind;

//*******ПЕРЕЧИСЛЕНИЯ*********

typedef enum {
	e_Time_Init = 0,
	e_Time_Blink 
} eIndexConst_Mod_Ind;


//Функции модуля индикации

static void		M_Ind_bin2dec (uint16_t value, uint8_t numInd); 
static void		M_Ind_7_Segment_Out(void);  
static void 	M_Ind_View_SW_version(void);  
static void 	M_Ind_temperature_real(void);   
static void		M_Ind_view_num_page_menu(void); 
static void		M_Ind_view_parameter_menu(void);    
static void	 	M_Ind_blinking_7segm(BOOL state_left_symbol_dot, BOOL need_blink, uint8_t numInd); 
static void		M_Ind_view_temperature_or_fan_level_setup(const uint8_t offset_to_symb, uint8_t parameter);
static void		M_Ind_view_failure(void); 
static void		M_Ind_view_text(const uint8_t left_ind_offset_to_symb, const uint8_t middle_ind_offset_to_symb, 
                                const uint8_t right_ind_offset_to_symb, BOOL need_blink, uint8_t numInd);
static void		M_Ind_LED_blinking(uint8_t action, const uint8_t index);
static void		M_Ind_TimerAutoExit( void );


//*********СТРУКТУРЫ******************************************

Ind M_Ind_data[QUANTITY_OF_SEVEN_SEGMENT_INDICATORS] = { {0, {0,0,0}, {0,0,0}, {0,0,0}, {IS_DOT, NO_DOT}}, 
                                                        {0, {0,0,0}, {0,0,0}, {0,0,0}, {IS_DOT, NO_DOT}} };

TIME_M_Ind time_M_Ind = {0};


//***********ПЕРЕМЕННЫЕ****************************************
uint8_t M_Ind_State = 0;
uint8_t M_Ind_Previous_State = 0;
BOOL blink_mode = OFF;
BOOL Flag_Blink_led[QUANTITY_OF_LEDS];    //флаг мигания светодиодов 	

void M_Ind_ctor(void)
{
    ANODE_1_PIN  = ANODE_IS_OFF;  
    ANODE_1_TRIS = OUT;
    ANODE_2_PIN  = ANODE_IS_OFF; 
    ANODE_2_TRIS = OUT; 
    ANODE_3_PIN  = ANODE_IS_OFF; 
    ANODE_3_TRIS = OUT; 
    ANODE_4_PIN  = ANODE_IS_OFF; 
    ANODE_4_TRIS = OUT; 
    ANODE_5_PIN  = ANODE_IS_OFF; 
    ANODE_5_TRIS = OUT; 
    ANODE_6_PIN  = ANODE_IS_OFF; 
    ANODE_6_TRIS = OUT; 
    LED_BICOLOR_GREEN_TRIS = OUT; 
    LED_BICOLOR_RED_TRIS = OUT;   
    LED_FAN_TRIS = OUT;           
    LED_PUMP_TRIS = OUT;           
    LED_BICOLOR_GREEN_PIN = OFF; 
    LED_BICOLOR_RED_PIN = OFF;   
    LED_FAN_PIN = OFF;           
    LED_PUMP_PIN = OFF; 
    M_Ind_data[0].dot[LEFT_INDICATOR]   = M_Ind_data[0].const_dot[INDEX_NO_DOT];
    M_Ind_data[0].dot[MIDDLE_INDICATOR] = M_Ind_data[0].const_dot[INDEX_NO_DOT];
    M_Ind_data[0].dot[RIGHT_INDICATOR]  = M_Ind_data[0].const_dot[INDEX_NO_DOT];
    M_Ind_data[1].dot[LEFT_INDICATOR]   = M_Ind_data[1].const_dot[INDEX_NO_DOT];
    M_Ind_data[1].dot[MIDDLE_INDICATOR] = M_Ind_data[1].const_dot[INDEX_NO_DOT];
    M_Ind_data[1].dot[RIGHT_INDICATOR]  = M_Ind_data[1].const_dot[INDEX_NO_DOT];
}

void  M_Ind_Set_blink_mode(BOOL value)
{
	blink_mode = value;
}

//**************ФУНКЦИИ**********************************

uint8_t M_Ind_Get_Previous_State(void)
{
	return M_Ind_Previous_State;
}

void M_Ind_Set_Previous_State(uint8_t state) 
{
	M_Ind_Previous_State = state;
}

void M_Ind_Set_state(uint8_t value)
{
	M_Ind_State = value;
}

uint8_t M_Ind_Get_state(void)
{
	return M_Ind_State;
}

/* Вывод на семисегментный индикатор */
static void M_Ind_7_Segment_Out (void)
{
	static uint8_t count_s = 0, numAnode = 0;
    static uint8_t count_indicators = 0;
    
    //Сброс пинов с общими анодами и установка нужного
    ANODE_FIRST_PORT |= ANODES_ARE_OFF_ON_FIRST_PORT;
    ANODE_SECOND_PORT |= ANODES_ARE_OFF_ON_SECOND_PORT;

        //Загружаем данные в сдвиговый регистр
        SW_SPI_writeByte( *(ptrTablePortraits[count_indicators] + M_Ind_data[count_indicators].data[count_s] ) 
                          & M_Ind_data[count_indicators].dot[count_s]);
        switch( numAnode )
        {
            case 0:
                ANODE_1_PIN  = ANODE_IS_ON;
                break;
            case 1:
                ANODE_2_PIN  = ANODE_IS_ON;
                break;
            case 2:
                ANODE_3_PIN  = ANODE_IS_ON;
                break;    
            case 3:
                ANODE_4_PIN  = ANODE_IS_ON;
                break;
            case 4:
                ANODE_5_PIN  = ANODE_IS_ON;
                break;
            case 5:
                ANODE_6_PIN  = ANODE_IS_ON;
        }  
        numAnode++;
        if(++count_s == QUANTITY_OF_FAMILIARITY ) 
        {    
            count_s = 0;
            if(++count_indicators == QUANTITY_OF_SEVEN_SEGMENT_INDICATORS )
            {    
                count_indicators = 0;
                numAnode = 0;
            }
        }
}

/* 
Функция преобразования int числа value  из двоичного в двоично-десятичный формат с заполнением массива data
- гасит незначащие нули в искомом числе
- отрабатывает режим мигания
- определяет число или текстовый символ нужно выводить
Входные параметры:
unsigned  int value - искомое число
*/

static void M_Ind_bin2dec (uint16_t value, uint8_t numInd)
{
 	uint8_t count = 0;
 	uint8_t decimals_temp = decimals[0];
       
        if (M_Ind_data[numInd].Flag_Blink_seven_segm)		 //если нужно мигать, то выводим пустые символы
            M_Ind_data[numInd].data[LEFT_INDICATOR] = M_Ind_data[numInd].data[MIDDLE_INDICATOR] = M_Ind_data[numInd].data[RIGHT_INDICATOR] 
            = INDEX_OF_BLANK_SYMBOL;		
        else
        {
            M_Ind_data[numInd].data[LEFT_INDICATOR] = M_Ind_data[numInd].data[MIDDLE_INDICATOR] 
            = M_Ind_data[numInd].data[RIGHT_INDICATOR] = 0;
            while(count < QUANTITY_OF_FAMILIARITY) 		// цикл по всем цифрам
            {
                    if (M_Ind_data[numInd].index_of_text_sym[count] >= IT_IS_A_TEXT_SYM_AREA) //если нужно выводить не цифру, а текстовый символ
                        M_Ind_data[numInd].data[count] = M_Ind_data[numInd].index_of_text_sym[count];
                else
                {
                    while(value >= decimals_temp) 
                    { 
                        value -= decimals_temp;  
                        M_Ind_data[numInd].data[count]++;
                    }			
                }
                count++;
                decimals_temp = decimals[count];	
            }
            if(M_Ind_data[numInd].data[LEFT_INDICATOR] == 0U) //формирование гашения незначащих нулей
            {		
                M_Ind_data[numInd].data[LEFT_INDICATOR] = INDEX_OF_BLANK_SYMBOL;
                if(M_Ind_data[numInd].data[MIDDLE_INDICATOR] == 0U)
                    M_Ind_data[numInd].data[MIDDLE_INDICATOR] = INDEX_OF_BLANK_SYMBOL;
            } 	
    }    
}

/* Индикация светодиода "Вентилятор" */
static void M_Ind_led_fan_mode(void)
{
	switch(M_Mngm_get_burning_state())
	{
		case CALC_PARAMS_PERIOD:
			LED_FAN_PIN = OFF;
		break;
		case START_BURNING:
		case ECONOM_MODE:
		case INCREASE_TEMPERATURE:
		case MAINTENANCE_TEMPERATURE_INCR:
			LED_FAN_PIN = ON;
		break;
		case MAINTENANCE_TEMPERATURE_CYCLE:
			switch(M_Mngm_get_phase_cycle())
			{
				case PAUSE_IN_CYCLE:
					M_Ind_LED_blinking(BLINKING_FAN_PIN, INDEX_OF_FAN_LED);
				break;
				case WORK_IN_CYCLE:
					LED_FAN_PIN = ON;
				break;
			}
		break;
	}
}	


/* Автомат состояний модуля индикации */
void M_Ind_Run (void)
{
	switch(M_Ind_State)
	{
		case STATE_IND_INIT :						//инициализация (мигание версии ПО), все светоиоды отключены
			M_Ind_View_SW_version();					
			LED_BICOLOR_GREEN_PIN = OFF;
			LED_BICOLOR_RED_PIN = OFF;
			LED_FAN_PIN = OFF;
			M_Ind_LED_blinking(NO_BLINKING, INDEX_OF_BICOLOR_LED);
            break;
		case STATE_VIEW_NUM_PAGE_MENU :		//отображение номера страницы пользовательского меню
			M_Ind_Previous_State = STATE_VIEW_NUM_PAGE_MENU;
			M_Ind_LED_blinking(BLINKING_YELLOW, INDEX_OF_BICOLOR_LED);
			LED_FAN_PIN = OFF;
			M_Ind_view_num_page_menu();
			M_Ind_TimerAutoExit();
		break;
		case STATE_VIEW_PARAMETER_MENU :	//отображение параметра меню на выбранной странице (мигаем Ж+З)
			M_Ind_Previous_State = STATE_VIEW_PARAMETER_MENU;
			M_Ind_LED_blinking(BLINKING_YELLOW, INDEX_OF_BICOLOR_LED);
			LED_FAN_PIN = OFF;
			M_Ind_view_parameter_menu();
			M_Ind_TimerAutoExit();
		break;
		case STATE_VIEW_TEMPERATURE_REAL :		//отображение типа топлива и текущей температуры воды в контуре отопления
			M_Ind_Previous_State = STATE_VIEW_TEMPERATURE_REAL;
			M_Ind_temperature_real();
			switch(M_Mngm_Get_state())
			{
				case STATE_WAITING:		//мигать 2-цветным светодиодом в режиме "Ожидание"
					M_Ind_LED_blinking(BLINKING_GREEN, INDEX_OF_BICOLOR_LED);
					LED_FAN_PIN = OFF;
					LED_BICOLOR_RED_PIN = OFF;
				break;
				case STATE_BURNING:		//светить 2-цветным светодиодом в режиме "Горение"
					switch(M_Mngm_get_burning_state())
					{
						case CALC_PARAMS_PERIOD:
							LED_BICOLOR_RED_PIN = OFF;
							LED_BICOLOR_GREEN_PIN = OFF;
						break;
						case START_BURNING:
						case INCREASE_TEMPERATURE:
						case ECONOM_MODE:
							LED_BICOLOR_RED_PIN = ON;
							LED_BICOLOR_GREEN_PIN = OFF;
						break;
						case MAINTENANCE_TEMPERATURE_INCR:
						case MAINTENANCE_TEMPERATURE_CYCLE:	
							LED_BICOLOR_RED_PIN = OFF;
							LED_BICOLOR_GREEN_PIN = ON;
						break;
					}
					M_Ind_led_fan_mode();
				break;
			}
		break;
		case STATE_VIEW_TEMPERATURE_SETUP :				//отображение мигающего значения устанавливаемого пользователем значения температуры (мигаем К+З)
			M_Ind_Previous_State = STATE_VIEW_TEMPERATURE_SETUP;
			M_Ind_view_temperature_or_fan_level_setup(OFFSET_TO_SYMBOL_t, M_Mngm_Get_parameters_buffer()->menu_parameters.temper_setup);
			M_Ind_LED_blinking(BLINKING_YELLOW, INDEX_OF_BICOLOR_LED);
		break;
		case STATE_VIEW_SPEED_FAN_SETUP:		//отображение мигающего значения устанавливаемого пользователем значения уровня оборотов вентилятора (мигаем К+З)	
			M_Ind_Previous_State = STATE_VIEW_SPEED_FAN_SETUP;
			M_Ind_view_temperature_or_fan_level_setup(OFFSET_TO_SYMBOL_F, (*M_Mngm_get_pFanLevel()) - 1);
			M_Ind_LED_blinking(BLINKING_YELLOW, INDEX_OF_BICOLOR_LED);
		break;
		case STATE_VIEW_PAUSE :								//отображение в режиме "Пауза" (открыта крышка бункера, светим К+З)
			M_Ind_view_text(IT_IS_A_TEXT_SYM_AREA + OFFSET_TO_SYMBOL_P, 
			IT_IS_A_TEXT_SYM_AREA + OFFSET_TO_SYMBOL_A, IT_IS_A_TEXT_SYM_AREA + OFFSET_TO_SYMBOL_U, NEED_BLINK, 0);
			LED_BICOLOR_GREEN_PIN = ON;
			LED_BICOLOR_RED_PIN = ON;
			LED_FAN_PIN = OFF;
			M_Ind_LED_blinking(NO_BLINKING, INDEX_OF_BICOLOR_LED);
		break;
		case STATE_VIEW_CLEAN_CHIMNEY :					//отображение в режиме "Чистка дымохода" (светим К+З)
			M_Ind_Previous_State = STATE_VIEW_CLEAN_CHIMNEY;
			M_Ind_view_text(IT_IS_A_TEXT_SYM_AREA + OFFSET_TO_SYMBOL_C, 
			IT_IS_A_TEXT_SYM_AREA + OFFSET_TO_SYMBOL_L, IT_IS_A_TEXT_SYM_AREA + OFFSET_TO_SYMBOL_E, blink_mode, 0);
			M_Ind_view_text(IT_IS_A_TEXT_SYM_AREA + OFFSET_TO_SYMBOL_C, 
			IT_IS_A_TEXT_SYM_AREA + OFFSET_TO_SYMBOL_H, IT_IS_A_TEXT_SYM_AREA + OFFSET_TO_SYMBOL_I, blink_mode, 1);
            LED_BICOLOR_GREEN_PIN = ON;
			LED_BICOLOR_RED_PIN = ON;
			LED_FAN_PIN = OFF;
			M_Ind_LED_blinking(NO_BLINKING, INDEX_OF_BICOLOR_LED);
		break;
		case STATE_VIEW_SUPPLY_FUEL :						//отображение в режиме "Загрузка топлива"
			M_Ind_Previous_State = STATE_VIEW_SUPPLY_FUEL;
			M_Ind_view_text(IT_IS_A_TEXT_SYM_AREA + OFFSET_TO_SYMBOL_S, 
			IT_IS_A_TEXT_SYM_AREA + OFFSET_TO_SYMBOL_U, IT_IS_A_TEXT_SYM_AREA + OFFSET_TO_SYMBOL_P, blink_mode, 0);
			M_Ind_view_text(IT_IS_A_TEXT_SYM_AREA + OFFSET_TO_SYMBOL_F, 
			IT_IS_A_TEXT_SYM_AREA + OFFSET_TO_SYMBOL_U, IT_IS_A_TEXT_SYM_AREA + OFFSET_TO_SYMBOL_E, blink_mode, 1);
            if(M_Motor_get_direction() == TIME_PAUSE_DISPENSER || M_Motor_get_direction() == TIME_PAUSE_SHATTER)
				M_Ind_LED_blinking(BLINKING_YELLOW, INDEX_OF_BICOLOR_LED); 
			else
			{
				M_Ind_LED_blinking(NO_BLINKING, INDEX_OF_BICOLOR_LED);
				LED_BICOLOR_GREEN_PIN = ON;
				LED_BICOLOR_RED_PIN = ON;
			}
		break;
		case STATE_VIEW_FAILURE :						//отображение в режиме "Авария "
			M_Ind_view_failure();
			M_Ind_LED_blinking(BLINKING_RED, INDEX_OF_BICOLOR_LED);
			LED_FAN_PIN = OFF;
		break;
		//default:
	}
	M_Ind_7_Segment_Out();
}

/*Отображение текстовых символов на индикаторе */
static void M_Ind_view_text(const uint8_t left_ind_offset_to_symb, const uint8_t middle_ind_offset_to_symb, 
						const uint8_t right_ind_offset_to_symb, BOOL need_blink, uint8_t numInd)
{
	uint8_t i;
    
    if(M_Mngm_Get_Code_Failure() != CODE_FAILURE_IS_NO_FAILURE)
		M_Ind_State = STATE_VIEW_FAILURE;
	else
	{
        M_Ind_data[numInd].index_of_text_sym[LEFT_INDICATOR] = left_ind_offset_to_symb;
        M_Ind_data[numInd].index_of_text_sym[MIDDLE_INDICATOR] = middle_ind_offset_to_symb;
        M_Ind_data[numInd].index_of_text_sym[RIGHT_INDICATOR] = right_ind_offset_to_symb;
        M_Ind_data[numInd].dot[LEFT_INDICATOR] = M_Ind_data[numInd].const_dot[INDEX_NO_DOT];
        M_Ind_data[numInd].dot[MIDDLE_INDICATOR] = M_Ind_data[numInd].const_dot[INDEX_NO_DOT];
        M_Ind_data[numInd].dot[RIGHT_INDICATOR] = M_Ind_data[numInd].const_dot[INDEX_NO_DOT];
        M_Ind_blinking_7segm(LEFT_SYMBOL_NO_DOT, need_blink, numInd);
        M_Ind_bin2dec(IT_IS_A_TEXT_SYM_AREA, numInd);
    }
}

/*Индикация в режиме "Авария" */
void M_Ind_view_failure(void)
{
	if(M_Mngm_Get_Code_Failure() == CODE_FAILURE_IS_NO_FAILURE)
		M_Ind_State = M_Ind_Previous_State;
	else
	{
		M_Ind_data[0].index_of_text_sym[LEFT_INDICATOR] = IT_IS_A_TEXT_SYM_AREA + OFFSET_TO_SYMBOL_E; 
		M_Ind_data[0].index_of_text_sym[MIDDLE_INDICATOR] = M_Ind_data[0].index_of_text_sym[RIGHT_INDICATOR] = 0;
		M_Ind_data[0].dot[LEFT_INDICATOR] = M_Ind_data[0].const_dot[INDEX_IS_DOT];
		M_Ind_data[0].dot[MIDDLE_INDICATOR] = M_Ind_data[0].const_dot[INDEX_NO_DOT];
        M_Ind_data[0].dot[RIGHT_INDICATOR] = M_Ind_data[0].const_dot[INDEX_NO_DOT];
        M_Ind_blinking_7segm(LEFT_SYMBOL_WITH_DOT, NEED_BLINK, 0);
		M_Ind_bin2dec(M_Mngm_Get_Code_Failure(), 0);	
	}	
}


//Реализация мигания символов
static void M_Ind_blinking_7segm(BOOL state_left_symbol_dot, BOOL need_blink, uint8_t numInd)
{	
	if(state_left_symbol_dot) //если в мигании участвует левое из 3-х знакомест с точкой
		M_Ind_data[numInd].dot[LEFT_INDICATOR] = M_Ind_data[numInd].const_dot[M_Ind_data[numInd].Flag_Blink_seven_segm];
	else
		M_Ind_data[numInd].dot[LEFT_INDICATOR] = M_Ind_data[numInd].const_dot[INDEX_NO_DOT];
	if(need_blink)
	{
		if(time_M_Ind.time_blink++ == M_Ind_time_const[e_Time_Blink])
		{
			time_M_Ind.time_blink = 0;
			M_Ind_data[numInd].Flag_Blink_seven_segm = !M_Ind_data[numInd].Flag_Blink_seven_segm;
		}
	}	
	else
		M_Ind_data[numInd].Flag_Blink_seven_segm = OFF;
}

/* Отображение в режиме "Индикация установленной температуры", "Индикация установленных оборотов вентилятора" */
static void M_Ind_view_temperature_or_fan_level_setup(const uint8_t offset_to_symb, uint8_t parameter)
{
	if(M_Mngm_Get_Code_Failure() != CODE_FAILURE_IS_NO_FAILURE)
		M_Ind_State = STATE_VIEW_FAILURE;
	else
	{
		M_Ind_data[1].index_of_text_sym[LEFT_INDICATOR] = IT_IS_A_TEXT_SYM_AREA + offset_to_symb; 
		M_Ind_data[1].index_of_text_sym[MIDDLE_INDICATOR] = M_Ind_data[1].index_of_text_sym[RIGHT_INDICATOR] = 0;
		M_Ind_blinking_7segm(LEFT_SYMBOL_WITH_DOT, NEED_BLINK, 1);
		M_Ind_bin2dec(parameter, 1);
	}
}

/* Установка счётчикак таймера автовыхода по енажатию ни на одну из кнопок в меню*/
void M_Ind_setTimeAutoExit( uint8_t value )
{
	time_M_Ind.time_auto_exit = value;
}

/* Организация таймера автовыхода по ненажатию ни на одну из кнопок в меню */
void M_Ind_TimerAutoExit( void )
{
	//Организация автоматического выхода по таймеру, если не нажата ни одна из кнопок
	if(time_M_Ind.time_auto_exit++ == (M_Mngm_Get_parameters_buffer()->menu_parameters.time_auto_exit) * 1000U)
	{
		time_M_Ind.time_auto_exit = 0;
		if((M_LI_Get_Key_State()->M_LI_Code_Key) == 0U) //если по истечении времени автовыхода не нажата ни одна из кнопок
			M_Ind_State = STATE_VIEW_TEMPERATURE_REAL;	
	}
}

/* Отображение номера страницы инженерного меню  */
static void M_Ind_view_num_page_menu(void) 
{
	if(M_Mngm_Get_Code_Failure() != CODE_FAILURE_IS_NO_FAILURE)
	{
		M_Ind_State = STATE_VIEW_FAILURE;
		time_M_Ind.time_auto_exit = 0;
	}
	else
	{
		M_Ind_data[0].index_of_text_sym[LEFT_INDICATOR] = IT_IS_A_TEXT_SYM_AREA + OFFSET_TO_SYMBOL_P; 	
		M_Ind_data[0].index_of_text_sym[MIDDLE_INDICATOR] = M_Ind_data[0].index_of_text_sym[RIGHT_INDICATOR] = 0;
		M_Ind_bin2dec(Menu_Get_Num_Page_Menu(), 0);
		M_Ind_data[0].dot[LEFT_INDICATOR] = M_Ind_data[0].const_dot[INDEX_IS_DOT];
	}
}

/* Отображение параметра инженерного меню, подлежащего изменению и сохранению */
static void M_Ind_view_parameter_menu(void)
{
	
	if(M_Mngm_Get_Code_Failure() != CODE_FAILURE_IS_NO_FAILURE)
		M_Ind_State = STATE_VIEW_FAILURE;
	else
	{
		M_Ind_data[1].dot[LEFT_INDICATOR] = NO_DOT;
		M_Ind_data[1].index_of_text_sym[LEFT_INDICATOR] = M_Ind_data[1].index_of_text_sym[MIDDLE_INDICATOR]
		= M_Ind_data[1].index_of_text_sym[RIGHT_INDICATOR] = 0; //в этом режиме выводятся только цифры
		M_Ind_bin2dec(M_Mngm_Get_parameters_buffer()->buffer[Menu_Get_Num_Page_Menu()], 1);
	}
}

/* Вывод на индикатор температуры воды и типа топлива с точкой */
static void M_Ind_temperature_real(void)
{
	if(M_Mngm_Get_Code_Failure() != CODE_FAILURE_IS_NO_FAILURE)
	    M_Ind_State = STATE_VIEW_FAILURE;
	else
	{	
		M_Ind_data[0].index_of_text_sym[MIDDLE_INDICATOR] = M_Ind_data[0].index_of_text_sym[RIGHT_INDICATOR] = 0; 
		if(Menu_get_temper_water_or_gas())
		{
			M_Ind_data[0].index_of_text_sym[LEFT_INDICATOR] = IT_IS_A_TEXT_SYM_AREA + OFFSET_TO_SYMBOL_d;
			M_Ind_bin2dec(M_AI_Get_ADC_Data(CHN_T_GAS)->param, 0);
		}
		else
		{
			M_Ind_bin2dec(M_AI_Get_ADC_Data(CHN_T_WATER)->param, 0);
			M_Ind_data[0].index_of_text_sym[LEFT_INDICATOR] = M_Mngm_Get_parameters_buffer()->menu_parameters.fuel_type 
				+ INDEX_OF_AREA_FUEL_TYPE;
		}
		M_Ind_data[0].dot[LEFT_INDICATOR] = M_Ind_data[1].dot[LEFT_INDICATOR] = M_Ind_data[0].const_dot[INDEX_IS_DOT];
		M_Ind_data[0].Flag_Blink_seven_segm = M_Ind_data[1].Flag_Blink_seven_segm = FALSE;
        M_Ind_data[1].index_of_text_sym[LEFT_INDICATOR] = IT_IS_A_TEXT_SYM_AREA + OFFSET_TO_SYMBOL_t; 
		M_Ind_data[1].index_of_text_sym[MIDDLE_INDICATOR] = M_Ind_data[1].index_of_text_sym[RIGHT_INDICATOR] = 0;
		M_Ind_bin2dec(M_Mngm_Get_parameters_buffer()->menu_parameters.temper_setup, 1);
    }
}

/* Отображение номера версии ПО по старту программы  */
static void M_Ind_View_SW_version(void)
{
	//Проверка - прошло ли время инициализации модуля индикации
	if(time_M_Ind.time_init++ == M_Ind_time_const[e_Time_Init]*1000U)
	{
		time_M_Ind.time_init = 0;
		M_Ind_data[0].Flag_Blink_seven_segm = FALSE;
		M_Ind_data[0].dot[LEFT_INDICATOR] = NO_DOT;
		M_Ind_State = STATE_VIEW_TEMPERATURE_REAL;
		//разрешить внешние прерывания INT2 (для детектирования переходов через нуль сетевого напряжения) 
		//INTCON3 = 0xD8;		//и INT1 (для опроса датчика ворошителя)
	}
	else //иначе мигаем версией программного обеспечения
	{
		M_Ind_blinking_7segm(LEFT_SYMBOL_WITH_DOT, NEED_BLINK, 0);
		M_Ind_bin2dec(M_Mngm_Get_parameters_buffer()->menu_parameters.software_version, 0);
        M_Ind_view_text(IT_IS_A_TEXT_SYM_AREA + OFFSET_TO_SYMBOL_S, 
			IT_IS_A_TEXT_SYM_AREA + OFFSET_TO_SYMBOL_F, IT_IS_A_TEXT_SYM_AREA + OFFSET_TO_SYMBOL_L, NO_NEED_BLINK, 1);
		M_Ind_State = STATE_IND_INIT;		
	}
}

/* Мигание светодиодов  */
static void M_Ind_LED_blinking(uint8_t action, const uint8_t index)
{
	if(action != NO_BLINKING)
	{
		if(time_M_Ind.time_blink_LED++ == M_Ind_time_const[e_Time_Blink])
		{
			time_M_Ind.time_blink_LED = 0;
			Flag_Blink_led[index] = !Flag_Blink_led[index];
		}
		switch(action)
		{
			case BLINKING_RED:	//мигание красного
				LED_BICOLOR_RED_PIN = Flag_Blink_led[index];
				LED_BICOLOR_GREEN_PIN = OFF;
				break;
			case BLINKING_GREEN:	//мигание зелёного
				LED_BICOLOR_RED_PIN = OFF;
				LED_BICOLOR_GREEN_PIN = Flag_Blink_led[index];
				break;	
			case BLINKING_YELLOW:	//мигание жёлтого (Ж = К+З)
				LED_BICOLOR_RED_PIN = LED_BICOLOR_GREEN_PIN = Flag_Blink_led[index]; 
				break;
			case BLINKING_FAN_PIN:	//мигание светодиода "Вентилятор" (при горении, в подсостояния подержания температуры)
				LED_FAN_PIN =  Flag_Blink_led[index];
            case BLINKING_PUMP_PIN:  //to do!!!
                LED_PUMP_PIN = Flag_Blink_led[index]; //Мигание светодиода "Насос"
                break;
        }
	}
	else
	{
		Flag_Blink_led[index] = NO_BLINKING; 
		time_M_Ind.time_blink_LED = 0;
	}
}
