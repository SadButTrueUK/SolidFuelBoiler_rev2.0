#ifndef _MENU_H_
#define _MENU_H_

#include "stdint.h"
#include "module_logic_inputs.h"

	
#define INDEX_TEMPER_SETUP_MAX		 				79
#define INDEX_TEMPER_SETUP_MIN						78
#define INDEX_ROTATIONAL_SPEED_FAN_MIN_SMOLDERING	72
#define INDEX_ROTATIONAL_SPEED_FAN_MIN_ECONOM		66
#define INDEX_ROTATIONAL_SPEED_FAN_MIN_INCREASE		94

/*Function prototypes for menu.h*/

void 	Menu_inc_param (uint8_t* parameter, const uint8_t threshold_up);
//Функция уменьшения параметра меню до установленного предела
void 	Menu_dec_param (uint8_t* parameter, const uint8_t threshold_down);
//Функция изменения параметра меню в зависимости от направления изменения (инкремент/декремент)
void 	Menu_item_change (uint8_t* menu_param, uint8_t index, BOOL direction);
uint8_t Menu_Get_Num_Page_Menu(void);
void 	Menu_Key_handler(KeyState* key_str);
void 	M_Menu_Set_src_param_menu(uint8_t* menu_param, uint8_t num_page);
BOOL 	M_Menu_parameter_is_changed(uint8_t* menu_param, uint8_t num_page);
void 	M_Menu_write_parameter(uint8_t* menu_param, uint8_t num_page);
BOOL 	M_Menu_write_changed_param(uint8_t addr_param, uint8_t src_param, uint8_t changed_param);
void    M_Menu_entry_rotation_clean_chimney(void);
BOOL 	Menu_get_temper_water_or_gas(void);
BOOL 	Menu_get_manual_supply(void);



#endif