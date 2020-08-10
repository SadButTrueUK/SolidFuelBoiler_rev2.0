#include "menu.h"
#include "stdint.h"
#include "module_indication.h"
#include "module_management.h"
#include "module_motor.h"
#include "module_logic_inputs.h"
#include "module_analog_inputs.h"
#include "module_fan.h"
#include <string.h>
#include "eeprom.h"
#include "module_sound.h"
#include "crc8.h"


/* Константа минимальных и максимальных значений порогов величин, 
значения которых устанавливаются в меню.
Размещены последовательно по 2 элемента. 1-ый элемент - минимальное значение,
2-ой элемент - максимальное значение
*/
const rom uint8_t Menu_items_thresholds[] = 
{
/* №стр Значение параметра   */
/*P0*/  10, 99,		//время разгона двигателя(дозатора) в 1/100 с. Диапазон значений 10...99 (100мс...990мс)
/*P1*/  1, 60,		//максимальное время вращения двигателя(дозатора) в секундах. Диапазон значений 1...60 (1с...60с)
/*P2*/  28, 100,	//минимальный процент скважности ШИМа при разгоне двигателя(дозатора). Диапазон значений 28...100
/*P3*/  0, 3,		//количество повторных попыток вращения двигателя(дозатора) при несрабатывании концевика, после которого появляется признак аварии
/*P4*/  10, 99,		//время разгона двигателя(ворошителя) в 1/100 с. Диапазон значений 10...99 (100мс...990мс)
/*P5*/  1, 60,		//максимальное время вращения двигателя(ворошителя) в секундах. Диапазон значений 1...60 (1с...60с)
/*P6*/  28, 100,	//минимальный процент скважности ШИМа при разгоне двигателя(ворошителя). Диапазон значений 28...100
/*P7*/  0, 0,		//количество повторных попыток вращения двигателя(ворошителя) при несрабатывании концевика, после которого появляется признак аварии
/*P8*/  10, 99,		//время разгона двигателя(заслонки) в 1/100 с. Диапазон значений 10...99 (100мс...990мс)
/*P9*/  1, 60,		//максимальное время вращения двигателя(заслонки) в секундах. Диапазон значений 1...60 (1с...60с)
/*P10*/ 28, 100,	//минимальный процент скважности ШИМа при разгоне двигателя(заслонки). Диапазон значений 28...100
/*P11*/ 0, 7, 		//количество повторных попыток вращения двигателя(заслонки) при несрабатывании концевика, после которого появляется признак аварии
/*P12*/ 10, 99,		//время разгона двигателя(чистка золы) в 1/100 с. Диапазон значений 10...99 (100мс...990мс)
/*P13*/ 1, 60,		//максимальное время вращения двигателя(чистка золы) в секундах. Диапазон значений 1...60 (1с...60с)
/*P14*/ 28, 100,	//минимальный процент скважности ШИМа при разгоне двигателя(чистка золы). Диапазон значений 28...100
/*P15*/ 0, 0,		//количество повторных попыток вращения двигателя(чистка золы) при несрабатывании концевика, после которого появляется признак аварии
/*P16*/ 2, 2,		//минимальный уровень оборотов вентилятора в режиме поддержания температуры при горении топлива. Диапазон значений 2...2 
/*P17*/ 4, 8,		//максимальный процент скорости оборотов вентилятора. Диапазон значений 4...8
/*P18*/ 5, 120,		//время работы вентилятора в цикле работа-пауза режима продувки в секундах (для угля)
/*P19*/ 5, 120,		//время работы вентилятора в цикле работа-пауза режима продувки в секундах (для щепы)
/*P20*/ 5, 120,		//время работы вентилятора в цикле работа-пауза режима продувки в секундах (для пеллет)
/*P21*/ 1, 36,		//время простоя вентилятора в цикле работа-пауза режима продувки в сотнях секунд (для угля)
/*P22*/ 1, 36,  	//время простоя вентилятора в цикле работа-пауза режима продувки в сотнях секунд (для щепы)
/*P23*/ 1, 36,  	//время простоя вентилятора в цикле работа-пауза режима продувки в сотнях секунд (для пеллет)
/*P24*/ 1, 10,		//разница между текущей и установленной температурами, при которой отключается режим продувки при остывании котла (для угля)
/*P25*/ 1, 10,		//разница между текущей и установленной температурами, при которой отключается режим продувки при остывании котла (для щепы)
/*P26*/ 1, 10, 		//разница между текущей и установленной температурами, при которой отключается режим продувки при остывании котла (для пеллет)
/*P27*/ 6, 42,		//время разгона вентилятора от мин до макс оборотов при входе в режим горения в десятках секунд от 6 до 42 (для угля)
/*P28*/ 6, 42,		//время разгона вентилятора от мин до макс оборотов при входе в режим горения в десятках секунд от 6 до 42 (для щепы)
/*P29*/ 6, 42,		//время разгона вентилятора от мин до макс оборотов при входе в режим горения в десятках секунд от 6 до 42 (для пеллет)
/*P30*/ 1, 15,		//разница между установленной и текущей температурой, по которой  вентилятор переходит на минимальные обороты (для экономного сжигания топлива) для угля
/*P31*/ 1, 8,		//разница между установленной и текущей температурой, по которой  вентилятор переходит на минимальные обороты (для экономного сжигания топлива) для щепы
/*P32*/ 1, 8,		//разница между установленной и текущей температурой, по которой  вентилятор переходит на минимальные обороты (для экономного сжигания топлива) для пеллет
/*P33*/ 1, 8,		// уровень оборотов вентилятора в эконом-режиме от 2 до 8 для угля
/*P34*/ 1, 8,		// уровень оборотов вентилятора в эконом-режиме от 2 до 8 для щепы
/*P35*/ 1, 8,		// уровень оборотов вентилятора в эконом-режиме от 2 до 8 для пеллет
/*P36*/ 1, 8,		// уровень оборотов вентилятора в режиме продувки от 2 до 8 для угля
/*P37*/ 1, 8,		// уровень оборотов вентилятора в режиме продувки от 2 до 8 для щепы
/*P38*/ 1, 8,		// уровень оборотов вентилятора в режиме продувки от 2 до 8 для пеллет
/*P39*/ 30, 90, 	//установленная температура
/*P40*/ 0, 2, 		//тип топлива
/*P41*/ 0, 1, 		//флаг разрешения звука. 1 - разрешён, 0 - запрещён
/*P42*/ 8, 60,		//время в секундах, по истечении которого, если нет действий пользователя, выходим из меню
/*P43*/ 1, 63,		//период загрузок топлива "Уголь"  (в сотнях секунд, от 1 до 54, т.е. от 100 секунд до 1 часа 45 минут) 
/*P44*/ 1, 63, 		//период загрузок топлива "Брикеты" (в сотнях секунд, от 1 до 54, т.е. от 100 секунд до 1.5 часа) 
/*P45*/ 1, 63,		//период загрузок топлива "Пеллеты" (в сотнях секунд, от 1 до 54, т.е. от 100 секунд до 1.5 часа)
/*P46*/ 2, 10,		//пороговое значение разницы между текущей и установленной температурой, по которому делается выход из циклического режима работы вентилятора
/*P47*/ 1, 8,		//уровень оборотов вентилятора для режима горения (фактически, это время, в течение которого симистор открыт в каждом полупериоде синусоиды)  
/*P48*/ 5, 20,       //время работы двигателя чистки золы (в секундах)
/*P49*/ 18, 216     //период между включениями двигателя чистки золы (от 30 минут до 6 часов)
};


#define INCREMENT	1
#define DECREMENT	0

const rom uint8_t QUANTITY_OF_MENU_PARAMETERS =  49;  //количество страниц меню, которіе можно изменять

uint8_t Menu_Num_Page_Menu = 0; 
uint8_t M_Menu_src_param_menu = 0;
BOOL temper_water_or_gas = 0;
BOOL Menu_manual_supply = OFF;

BOOL Menu_get_manual_supply(void)
{
	return Menu_manual_supply;
}

BOOL Menu_get_temper_water_or_gas(void)
{
	return temper_water_or_gas;
}


uint8_t Menu_Get_Num_Page_Menu(void)
{
	return Menu_Num_Page_Menu;
}

//Функция увеличения параметра меню до установленного предела
void Menu_inc_param(uint8_t* parameter, const uint8_t threshold_up)
{
	if(*parameter < threshold_up) (*parameter)++;
}

//Функция уменьшения параметра меню до установленного предела
void Menu_dec_param(uint8_t* parameter, const uint8_t threshold_down)
{
	if(*parameter > threshold_down) (*parameter)--;
}

/*Функция изменения параметра меню в зависимости от направления изменения (инкремент/декремент)
direction = 1 - инкремент
direction = 0 -декремент
*/
void Menu_item_change(uint8_t* menu_param, uint8_t index, BOOL direction)
{
	if(direction) //увеличение параметра
	{
		Menu_inc_param(&menu_param[index], Menu_items_thresholds[index*2 + 1]);  			
	}
	else
	{
		Menu_dec_param(&menu_param[index], Menu_items_thresholds[index*2]);
	}
}

/* Установка указателя на текущий параметр меню, который подлежит изменению */
void M_Menu_Set_src_param_menu(uint8_t* menu_param, uint8_t num_page)
{
	M_Menu_src_param_menu = menu_param[num_page];		
}


BOOL M_Menu_write_changed_param(uint8_t addr_param, uint8_t src_param, uint8_t changed_param)
{
	if(src_param != changed_param) //параметр изменился
	{
		DataEEWrite (changed_param, addr_param );
		return TRUE;
	}		
	else
	{
		return FALSE;
	}	
}

/* 
Проверка того, изменился ли параметр меню
Возвращает:
1 - изменился
0 - не изменился 
*/
BOOL M_Menu_parameter_is_changed(uint8_t* menu_param, uint8_t num_page)
{
	return (M_Menu_src_param_menu != menu_param[num_page]);	
}

/* Функция сохранения параметра меню, если он изменился, а также контрольной суммы */
void M_Menu_write_parameter(uint8_t* menu_param, uint8_t num_page)
{
	uint8_t crcEEPROM;
    if(M_Menu_parameter_is_changed(menu_param, num_page))
	{	
        DataEEWrite (menu_param[num_page], num_page );
        DataEEWrite( crc8_update( 0xFF, menu_param, SIZE_BUFFER ), SIZE_BUFFER );
    }
}


void M_Menu_entry_rotation_clean_chimney(void)
{	M_Ind_Set_Previous_State(M_Ind_Get_state());
	M_Ind_Set_state(STATE_VIEW_CLEAN_CHIMNEY);
	M_Mngm_Set_state(STATE_CLEAN_CHIMNEY);
	M_Ind_Set_blink_mode(NO_NEED_BLINK);
	M_Motor_set_state(STATE_MODULE_MOTOR_WAITING_FOR_MOVE_CLEAN_CHIMNEY);
	M_Motor_set_ctrl_shatter(WAITING_MOVEMENT);
}



/* Обработчик нажатых кнопок 
В зависимости от кода нажатой кнопки устанавливает переменную автомата состояний следущих модулей:
- модуль управления 
- модуль индикации 
*/
void Menu_Key_handler(KeyState* key_str)
{
	if(M_Ind_Get_state() == STATE_IND_INIT)
		return;
    // Все длительные нажатия кнопок обрабатываются только в режиме ожидания
	if ((((key_str->M_LI_Code_Key) & 0x01) == 1U) && 
	((M_Mngm_Get_state() == STATE_WAITING) || ((M_Mngm_Get_state() == STATE_BURNING) && 
     ((key_str->M_LI_Code_Key & NO_KEY_PRESSED) == CODE_KEY_DEC_LONG__PRESSED)))) //произошло длительное нажатие какой-либо кнопки
	{
		//M_Sound_set_button_submergence (ON);  //установить флаг подзвучки кнопки
		switch ((key_str->M_LI_Code_Key) & NO_KEY_PRESSED)
		{
			case CODE_KEY_ESC_LONG__PRESSED:
                M_Ind_Set_Previous_State(M_Ind_Get_state());
                M_Ind_Set_state(STATE_VIEW_ASH_CLEAN);
                break;
            case CODE_KEY_MENU_LONG__PRESSED:
				
					M_Ind_Set_Previous_State(M_Ind_Get_state());
					M_Ind_Set_state(STATE_VIEW_NUM_PAGE_MENU);
					Menu_Num_Page_Menu = 0;
			break;
			case CODE_KEY_INC_LONG__PRESSED:
				M_Ind_Set_Previous_State(M_Ind_Get_state());
				M_Ind_Set_state(STATE_VIEW_SUPPLY_FUEL);
				M_Mngm_Set_state(STATE_FUEL_SUPPLY);
				M_Ind_Set_blink_mode(NO_NEED_BLINK);
				Menu_manual_supply = ON;
				break;	
			case CODE_KEY_DEC_LONG__PRESSED: //уловие перехода в режим чистки дымохода
				if(M_Mngm_Get_state() == STATE_BURNING)
				{
					temper_water_or_gas = !temper_water_or_gas;
				}
				else
				{
					if(M_AI_Get_ADC_Data(CHN_T_GAS)->param <=  MAX_TEMPER_GAS_SENSOR_FOR_CLEAN_CHIMNEY && 
					M_LI_Get_Limit_Switches()->ls_dispenser_start_state && M_LI_Get_Limit_Switches()->ls_shatter_start_state && 
					!M_LI_Get_Limit_Switches()->ls_shatter_after_finish_state)
					{
						M_Menu_entry_rotation_clean_chimney();
					}
				}
				break;	
                
        }
		key_str->M_LI_Code_Key = 0;
	}
	else if ((key_str->M_LI_Code_Key & 0x80) == 0x80) //произошло короткое нажатие какой-либо кнопки и её отпускание
	{
		switch ((key_str->M_LI_Code_Key) & NO_KEY_PRESSED)
		{
			case CODE_KEY_MENU_PRESSED_AND_FREE:
				switch(M_Ind_Get_state())
				{
					case STATE_VIEW_PARAMETER_MENU:
						M_Ind_Set_state(STATE_VIEW_NUM_PAGE_MENU);	
						//Сохранение в ЕЕПРОМ параметра, если он изменился
						M_Menu_write_parameter(M_Mngm_Get_parameters_buffer()->buffer, Menu_Num_Page_Menu);
						M_Ind_setTimeAutoExit(0);
						break;
					case STATE_VIEW_NUM_PAGE_MENU:
						M_Ind_Set_state(STATE_VIEW_PARAMETER_MENU);
						M_Menu_Set_src_param_menu(M_Mngm_Get_parameters_buffer()->buffer, Menu_Num_Page_Menu);
						M_Ind_setTimeAutoExit(0);
						break;
					case STATE_VIEW_CLEAN_CHIMNEY:
						if((M_Motor_get_ctrl_shatter() == WAITING_MOVEMENT/*NO_MOVEMENT*/) && M_LI_Get_Limit_Switches()->ls_shatter_start_state && !M_LI_Get_Limit_Switches()->ls_shatter_after_finish_state)
							M_Ind_Set_state(STATE_VIEW_TEMPERATURE_REAL);
						break;
                }
				switch(M_Mngm_Get_state())
				{
					case STATE_WAITING:
						if((M_Ind_Get_state() !=  STATE_VIEW_TEMPERATURE_SETUP) && 
						(M_Ind_Get_state() !=  STATE_VIEW_SPEED_FAN_SETUP)
						&&(M_Ind_Get_state() !=  STATE_VIEW_PARAMETER_MENU) && 
						(M_Ind_Get_state() !=  STATE_VIEW_NUM_PAGE_MENU) && !M_Motor_get_work() /* && (M_Ind_Get_state() != STATE_VIEW_CLEAN_CHIMNEY) */)
						{
								M_Mngm_Set_state(STATE_BURNING);
								M_Mngm_set_saved_temperature_water(M_AI_Get_ADC_Data(CHN_T_WATER)->param);
						}
						if((M_Ind_Get_state() ==  STATE_VIEW_PARAMETER_MENU) ||
							(M_Ind_Get_state() ==  STATE_VIEW_NUM_PAGE_MENU))
							break;	
						else
						{
							if(M_Ind_Get_state() ==  STATE_VIEW_TEMPERATURE_SETUP)
								M_Menu_write_changed_param(INDEX_OF_TEMPER_SETUP, 
								  	DataEERead (INDEX_OF_TEMPER_SETUP), M_Mngm_Get_parameters_buffer()->menu_parameters.temper_setup);
							else if (M_Ind_Get_state() ==  STATE_VIEW_SPEED_FAN_SETUP)
								M_Menu_write_changed_param( INDEX_OF_LEVEL_FAN_ROTATION_SPEED_INCREASE, 
						  		DataEERead ( INDEX_OF_LEVEL_FAN_ROTATION_SPEED_INCREASE), M_Mngm_Get_parameters_buffer()->menu_parameters.rotational_speed_fan);		
							M_Ind_Set_state(STATE_VIEW_TEMPERATURE_REAL);
						}
						break;
					case STATE_FUEL_SUPPLY:
						if(M_Motor_get_state() == STATE_MODULE_MOTOR_WAITING)  //из рабочего кода
						{
							M_Mngm_Set_state(STATE_BURNING);
							M_Ind_Set_state(STATE_VIEW_TEMPERATURE_REAL); //добавил
							M_Motor_clear_parameters();
							Menu_manual_supply = OFF;
						}
						break;
					case STATE_BURNING:
						if(M_Ind_Get_state() !=  STATE_VIEW_TEMPERATURE_SETUP && 
							M_Ind_Get_state() !=  STATE_VIEW_SPEED_FAN_SETUP && M_Motor_get_state() == STATE_MODULE_MOTOR_WAITING )
						{	
							M_fan_set_ctrl_fan(OFF);
							M_Mngm_Set_state(STATE_WAITING);
							M_Mngm_clear_timeouts();
							M_Mngm_clear_accel_fan();
							M_Mngm_clear_cyclic_mode();
							M_Mngm_set_burning_state(CALC_PARAMS_PERIOD);
						}
						else
						{
							if(M_Ind_Get_state() ==  STATE_VIEW_TEMPERATURE_SETUP)
								M_Menu_write_changed_param(INDEX_OF_TEMPER_SETUP, 
								DataEERead (INDEX_OF_TEMPER_SETUP), M_Mngm_Get_parameters_buffer()->menu_parameters.temper_setup);
							else if (M_Ind_Get_state() ==  STATE_VIEW_SPEED_FAN_SETUP)
							{
								M_Menu_write_changed_param(M_Mngm_get_fanParamOffset() >> 1, 
						  		DataEERead (M_Mngm_get_fanParamOffset() >> 1), *M_Mngm_get_pFanLevel());
							}
							M_Ind_Set_state(STATE_VIEW_TEMPERATURE_REAL);
						}
						break;
					case STATE_CLEAN_CHIMNEY:
						if(M_LI_Get_Limit_Switches()->ls_shatter_start_state && !M_LI_Get_Limit_Switches()->ls_shatter_after_finish_state)  //если заслонка закрыта
						{
							M_Mngm_Set_state(STATE_WAITING);
							M_Motor_set_ctrl_shatter(NO_MOVEMENT);
							M_Ind_Set_blink_mode(NO_NEED_BLINK);
							M_Motor_set_state(STATE_MODULE_MOTOR_WAITING);
							M_Ind_Set_state(STATE_VIEW_TEMPERATURE_REAL);
						}
						break;
					case STATE_FAILURE: 	//при аварии сбросить код аварии
						M_Mngm_Set_Code_Failure(CODE_FAILURE_IS_NO_FAILURE);
						M_Mngm_Get_parameters_buffer()->menu_parameters.code_failure = CODE_FAILURE_IS_NO_FAILURE;
						DataEEWrite (CODE_FAILURE_IS_NO_FAILURE, INDEX_OF_CODE_FAILURE );
						M_Ind_Set_state( M_Ind_Get_Previous_State());
						M_Motor_clear_struct_failure_motor();
						M_Motor_clear_false_state_LS(QUANTITY_FALSE_LS);
						M_Mngm_Set_state_draught(IS_DRAUGHT);
						if(M_Motor_get_prev_state() == STATE_MODULE_MOTOR_CLEAN_CHIMNEY)
						{
							M_Motor_set_state(STATE_MODULE_MOTOR_CLEAN_CHIMNEY);
						}
						else
						{
							M_Motor_set_state(M_Motor_get_prev_state());
						}
						//M_Ind_Set_blink_mode(NO_NEED_BLINK);
						break;
				}
			break;
			case CODE_KEY_INC_PRESSED_AND_FREE:   
				switch(M_Ind_Get_state())
				{
					case STATE_VIEW_TEMPERATURE_REAL:  	//просмотр текущей температуры
						M_Ind_Set_state(STATE_VIEW_TEMPERATURE_SETUP);
						break;
					case STATE_VIEW_NUM_PAGE_MENU:  		//увеличение номера страницы сервисного меню
						M_Ind_setTimeAutoExit(0);
						Menu_inc_param(&Menu_Num_Page_Menu, QUANTITY_OF_MENU_PARAMETERS);
					break;
					case STATE_VIEW_PARAMETER_MENU: 	 //увеличение параметра сервисного меню
						M_Ind_setTimeAutoExit(0);
						Menu_item_change(M_Mngm_Get_parameters_buffer()->buffer, Menu_Num_Page_Menu, INCREMENT); 
					break;
					case STATE_VIEW_TEMPERATURE_SETUP: 	//установка температуры
						Menu_inc_param(&(M_Mngm_Get_parameters_buffer()->menu_parameters.temper_setup), 
							Menu_items_thresholds[INDEX_TEMPER_SETUP_MAX]);
					break;
					case STATE_VIEW_SUPPLY_FUEL :
						M_Motor_set_work(ON); 		//включить алгоритм работы дозатора-заслонки-ворошителя
						M_Ind_Set_blink_mode(NEED_BLINK);
					break;
					case STATE_VIEW_SPEED_FAN_SETUP: 	//увеличение уровня оборотов вентилятора
						if(M_Mngm_Get_state() == STATE_BURNING)
						{
							Menu_inc_param(M_Mngm_get_pFanLevel(), Menu_items_thresholds[M_Mngm_get_fanParamOffset() + 1]);
						}
						break; 	
					case STATE_VIEW_CLEAN_CHIMNEY:
						if(M_Motor_get_ctrl_shatter() == WAITING_MOVEMENT/*NO_MOVEMENT */ && M_LI_Get_Limit_Switches()->ls_shatter_start_state 
							&& !M_LI_Get_Limit_Switches()->ls_shatter_after_finish_state)
							M_Motor_set_ctrl_shatter(MOVEMENT_FORWARD);
						break;
				}
			break;
			case CODE_KEY_DEC_PRESSED_AND_FREE: 
				switch(M_Ind_Get_state())
				{
					case STATE_VIEW_NUM_PAGE_MENU :
						M_Ind_setTimeAutoExit(0);
						Menu_dec_param(&Menu_Num_Page_Menu, 0);
					break;
					case STATE_VIEW_PARAMETER_MENU:
						M_Ind_setTimeAutoExit(0);
						Menu_item_change(M_Mngm_Get_parameters_buffer()->buffer, Menu_Num_Page_Menu, DECREMENT);
					break;
					case STATE_VIEW_TEMPERATURE_SETUP:
						Menu_dec_param(&(M_Mngm_Get_parameters_buffer()->menu_parameters.temper_setup), 
							Menu_items_thresholds[INDEX_TEMPER_SETUP_MIN]);	
					break;
					case STATE_VIEW_TEMPERATURE_REAL:  					//просмотр текущей температуры
						M_Ind_Set_state(STATE_VIEW_SPEED_FAN_SETUP);
					break;
					case STATE_VIEW_SPEED_FAN_SETUP:		 	//увеличение уровня оборотов вентилятора

						if(M_Mngm_Get_state() == STATE_BURNING)
						{
							Menu_dec_param(M_Mngm_get_pFanLevel(), Menu_items_thresholds[M_Mngm_get_fanParamOffset()]);
						}
					break; 
					case STATE_VIEW_CLEAN_CHIMNEY:
						if(M_Motor_get_ctrl_shatter() == WAITING_MOVEMENT && !M_LI_Get_Limit_Switches()->ls_shatter_start_state 
							&& M_LI_Get_Limit_Switches()->ls_shatter_after_finish_state)
							M_Motor_set_ctrl_shatter(MOVEMENT_BACKWARD);
					break;
				}
			break;
			case CODE_KEY_ESC_PRESSED_AND_FREE:
                switch(M_Ind_Get_state())
				{
                    case STATE_VIEW_NUM_PAGE_MENU :
						M_Ind_setTimeAutoExit(0);
						M_Ind_Set_state(STATE_VIEW_TEMPERATURE_REAL);
					break;
					case STATE_VIEW_PARAMETER_MENU:
						M_Ind_setTimeAutoExit(0);
						M_Ind_Set_state(STATE_VIEW_TEMPERATURE_REAL);
					break;
                }    
		}
		memset(key_str, 0, sizeof *(key_str));
	}	
}
