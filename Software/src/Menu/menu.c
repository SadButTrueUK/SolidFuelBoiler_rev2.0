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


/* ��������� ����������� � ������������ �������� ������� �������, 
�������� ������� ��������������� � ����.
��������� ��������������� �� 2 ��������. 1-�� ������� - ����������� ��������,
2-�� ������� - ������������ ��������
*/
const rom uint8_t Menu_items_thresholds[] = 
{
/* ���� �������� ���������   */
/*P0*/  10, 99,		//����� ������� ���������(��������) � 1/100 �. �������� �������� 10...99 (100��...990��)
/*P1*/  1, 60,		//������������ ����� �������� ���������(��������) � ��������. �������� �������� 1...60 (1�...60�)
/*P2*/  28, 100,	//����������� ������� ���������� ���� ��� ������� ���������(��������). �������� �������� 28...100
/*P3*/  0, 3,		//���������� ��������� ������� �������� ���������(��������) ��� �������������� ���������, ����� �������� ���������� ������� ������
/*P4*/  10, 99,		//����� ������� ���������(����������) � 1/100 �. �������� �������� 10...99 (100��...990��)
/*P5*/  1, 60,		//������������ ����� �������� ���������(����������) � ��������. �������� �������� 1...60 (1�...60�)
/*P6*/  28, 100,	//����������� ������� ���������� ���� ��� ������� ���������(����������). �������� �������� 28...100
/*P7*/  0, 0,		//���������� ��������� ������� �������� ���������(����������) ��� �������������� ���������, ����� �������� ���������� ������� ������
/*P8*/  10, 99,		//����� ������� ���������(��������) � 1/100 �. �������� �������� 10...99 (100��...990��)
/*P9*/  1, 60,		//������������ ����� �������� ���������(��������) � ��������. �������� �������� 1...60 (1�...60�)
/*P10*/ 28, 100,	//����������� ������� ���������� ���� ��� ������� ���������(��������). �������� �������� 28...100
/*P11*/ 0, 7, 		//���������� ��������� ������� �������� ���������(��������) ��� �������������� ���������, ����� �������� ���������� ������� ������
/*P12*/ 10, 99,		//����� ������� ���������(������ ����) � 1/100 �. �������� �������� 10...99 (100��...990��)
/*P13*/ 1, 60,		//������������ ����� �������� ���������(������ ����) � ��������. �������� �������� 1...60 (1�...60�)
/*P14*/ 28, 100,	//����������� ������� ���������� ���� ��� ������� ���������(������ ����). �������� �������� 28...100
/*P15*/ 0, 0,		//���������� ��������� ������� �������� ���������(������ ����) ��� �������������� ���������, ����� �������� ���������� ������� ������
/*P16*/ 2, 2,		//����������� ������� �������� ����������� � ������ ����������� ����������� ��� ������� �������. �������� �������� 2...2 
/*P17*/ 4, 8,		//������������ ������� �������� �������� �����������. �������� �������� 4...8
/*P18*/ 5, 120,		//����� ������ ����������� � ����� ������-����� ������ �������� � �������� (��� ����)
/*P19*/ 5, 120,		//����� ������ ����������� � ����� ������-����� ������ �������� � �������� (��� ����)
/*P20*/ 5, 120,		//����� ������ ����������� � ����� ������-����� ������ �������� � �������� (��� ������)
/*P21*/ 1, 36,		//����� ������� ����������� � ����� ������-����� ������ �������� � ������ ������ (��� ����)
/*P22*/ 1, 36,  	//����� ������� ����������� � ����� ������-����� ������ �������� � ������ ������ (��� ����)
/*P23*/ 1, 36,  	//����� ������� ����������� � ����� ������-����� ������ �������� � ������ ������ (��� ������)
/*P24*/ 1, 10,		//������� ����� ������� � ������������� �������������, ��� ������� ����������� ����� �������� ��� ��������� ����� (��� ����)
/*P25*/ 1, 10,		//������� ����� ������� � ������������� �������������, ��� ������� ����������� ����� �������� ��� ��������� ����� (��� ����)
/*P26*/ 1, 10, 		//������� ����� ������� � ������������� �������������, ��� ������� ����������� ����� �������� ��� ��������� ����� (��� ������)
/*P27*/ 6, 42,		//����� ������� ����������� �� ��� �� ���� �������� ��� ����� � ����� ������� � �������� ������ �� 6 �� 42 (��� ����)
/*P28*/ 6, 42,		//����� ������� ����������� �� ��� �� ���� �������� ��� ����� � ����� ������� � �������� ������ �� 6 �� 42 (��� ����)
/*P29*/ 6, 42,		//����� ������� ����������� �� ��� �� ���� �������� ��� ����� � ����� ������� � �������� ������ �� 6 �� 42 (��� ������)
/*P30*/ 1, 15,		//������� ����� ������������� � ������� ������������, �� �������  ���������� ��������� �� ����������� ������� (��� ���������� �������� �������) ��� ����
/*P31*/ 1, 8,		//������� ����� ������������� � ������� ������������, �� �������  ���������� ��������� �� ����������� ������� (��� ���������� �������� �������) ��� ����
/*P32*/ 1, 8,		//������� ����� ������������� � ������� ������������, �� �������  ���������� ��������� �� ����������� ������� (��� ���������� �������� �������) ��� ������
/*P33*/ 1, 8,		// ������� �������� ����������� � ������-������ �� 2 �� 8 ��� ����
/*P34*/ 1, 8,		// ������� �������� ����������� � ������-������ �� 2 �� 8 ��� ����
/*P35*/ 1, 8,		// ������� �������� ����������� � ������-������ �� 2 �� 8 ��� ������
/*P36*/ 1, 8,		// ������� �������� ����������� � ������ �������� �� 2 �� 8 ��� ����
/*P37*/ 1, 8,		// ������� �������� ����������� � ������ �������� �� 2 �� 8 ��� ����
/*P38*/ 1, 8,		// ������� �������� ����������� � ������ �������� �� 2 �� 8 ��� ������
/*P39*/ 30, 90, 	//������������� �����������
/*P40*/ 0, 2, 		//��� �������
/*P41*/ 0, 1, 		//���� ���������� �����. 1 - ��������, 0 - ��������
/*P42*/ 8, 60,		//����� � ��������, �� ��������� ��������, ���� ��� �������� ������������, ������� �� ����
/*P43*/ 1, 63,		//������ �������� ������� "�����"  (� ������ ������, �� 1 �� 54, �.�. �� 100 ������ �� 1 ���� 45 �����) 
/*P44*/ 1, 63, 		//������ �������� ������� "�������" (� ������ ������, �� 1 �� 54, �.�. �� 100 ������ �� 1.5 ����) 
/*P45*/ 1, 63,		//������ �������� ������� "�������" (� ������ ������, �� 1 �� 54, �.�. �� 100 ������ �� 1.5 ����)
/*P46*/ 2, 10,		//��������� �������� ������� ����� ������� � ������������� ������������, �� �������� �������� ����� �� ������������ ������ ������ �����������
/*P47*/ 1, 8,		//������� �������� ����������� ��� ������ ������� (����������, ��� �����, � ������� �������� �������� ������ � ������ ����������� ���������)  
/*P48*/ 5, 20,       //����� ������ ��������� ������ ���� (� ��������)
/*P49*/ 18, 216     //������ ����� ����������� ��������� ������ ���� (�� 30 ����� �� 6 �����)
};


#define INCREMENT	1
#define DECREMENT	0

const rom uint8_t QUANTITY_OF_MENU_PARAMETERS =  49;  //���������� ������� ����, ������ ����� ��������

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

//������� ���������� ��������� ���� �� �������������� �������
void Menu_inc_param(uint8_t* parameter, const uint8_t threshold_up)
{
	if(*parameter < threshold_up) (*parameter)++;
}

//������� ���������� ��������� ���� �� �������������� �������
void Menu_dec_param(uint8_t* parameter, const uint8_t threshold_down)
{
	if(*parameter > threshold_down) (*parameter)--;
}

/*������� ��������� ��������� ���� � ����������� �� ����������� ��������� (���������/���������)
direction = 1 - ���������
direction = 0 -���������
*/
void Menu_item_change(uint8_t* menu_param, uint8_t index, BOOL direction)
{
	if(direction) //���������� ���������
	{
		Menu_inc_param(&menu_param[index], Menu_items_thresholds[index*2 + 1]);  			
	}
	else
	{
		Menu_dec_param(&menu_param[index], Menu_items_thresholds[index*2]);
	}
}

/* ��������� ��������� �� ������� �������� ����, ������� �������� ��������� */
void M_Menu_Set_src_param_menu(uint8_t* menu_param, uint8_t num_page)
{
	M_Menu_src_param_menu = menu_param[num_page];		
}


BOOL M_Menu_write_changed_param(uint8_t addr_param, uint8_t src_param, uint8_t changed_param)
{
	if(src_param != changed_param) //�������� ���������
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
�������� ����, ��������� �� �������� ����
����������:
1 - ���������
0 - �� ��������� 
*/
BOOL M_Menu_parameter_is_changed(uint8_t* menu_param, uint8_t num_page)
{
	return (M_Menu_src_param_menu != menu_param[num_page]);	
}

/* ������� ���������� ��������� ����, ���� �� ���������, � ����� ����������� ����� */
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



/* ���������� ������� ������ 
� ����������� �� ���� ������� ������ ������������� ���������� �������� ��������� �������� �������:
- ������ ���������� 
- ������ ��������� 
*/
void Menu_Key_handler(KeyState* key_str)
{
	if(M_Ind_Get_state() == STATE_IND_INIT)
		return;
    // ��� ���������� ������� ������ �������������� ������ � ������ ��������
	if ((((key_str->M_LI_Code_Key) & 0x01) == 1U) && 
	((M_Mngm_Get_state() == STATE_WAITING) || ((M_Mngm_Get_state() == STATE_BURNING) && 
     ((key_str->M_LI_Code_Key & NO_KEY_PRESSED) == CODE_KEY_DEC_LONG__PRESSED)))) //��������� ���������� ������� �����-���� ������
	{
		//M_Sound_set_button_submergence (ON);  //���������� ���� ��������� ������
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
			case CODE_KEY_DEC_LONG__PRESSED: //������ �������� � ����� ������ ��������
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
	else if ((key_str->M_LI_Code_Key & 0x80) == 0x80) //��������� �������� ������� �����-���� ������ � � ����������
	{
		switch ((key_str->M_LI_Code_Key) & NO_KEY_PRESSED)
		{
			case CODE_KEY_MENU_PRESSED_AND_FREE:
				switch(M_Ind_Get_state())
				{
					case STATE_VIEW_PARAMETER_MENU:
						M_Ind_Set_state(STATE_VIEW_NUM_PAGE_MENU);	
						//���������� � ������ ���������, ���� �� ���������
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
						if(M_Motor_get_state() == STATE_MODULE_MOTOR_WAITING)  //�� �������� ����
						{
							M_Mngm_Set_state(STATE_BURNING);
							M_Ind_Set_state(STATE_VIEW_TEMPERATURE_REAL); //�������
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
						if(M_LI_Get_Limit_Switches()->ls_shatter_start_state && !M_LI_Get_Limit_Switches()->ls_shatter_after_finish_state)  //���� �������� �������
						{
							M_Mngm_Set_state(STATE_WAITING);
							M_Motor_set_ctrl_shatter(NO_MOVEMENT);
							M_Ind_Set_blink_mode(NO_NEED_BLINK);
							M_Motor_set_state(STATE_MODULE_MOTOR_WAITING);
							M_Ind_Set_state(STATE_VIEW_TEMPERATURE_REAL);
						}
						break;
					case STATE_FAILURE: 	//��� ������ �������� ��� ������
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
					case STATE_VIEW_TEMPERATURE_REAL:  	//�������� ������� �����������
						M_Ind_Set_state(STATE_VIEW_TEMPERATURE_SETUP);
						break;
					case STATE_VIEW_NUM_PAGE_MENU:  		//���������� ������ �������� ���������� ����
						M_Ind_setTimeAutoExit(0);
						Menu_inc_param(&Menu_Num_Page_Menu, QUANTITY_OF_MENU_PARAMETERS);
					break;
					case STATE_VIEW_PARAMETER_MENU: 	 //���������� ��������� ���������� ����
						M_Ind_setTimeAutoExit(0);
						Menu_item_change(M_Mngm_Get_parameters_buffer()->buffer, Menu_Num_Page_Menu, INCREMENT); 
					break;
					case STATE_VIEW_TEMPERATURE_SETUP: 	//��������� �����������
						Menu_inc_param(&(M_Mngm_Get_parameters_buffer()->menu_parameters.temper_setup), 
							Menu_items_thresholds[INDEX_TEMPER_SETUP_MAX]);
					break;
					case STATE_VIEW_SUPPLY_FUEL :
						M_Motor_set_work(ON); 		//�������� �������� ������ ��������-��������-����������
						M_Ind_Set_blink_mode(NEED_BLINK);
					break;
					case STATE_VIEW_SPEED_FAN_SETUP: 	//���������� ������ �������� �����������
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
					case STATE_VIEW_TEMPERATURE_REAL:  					//�������� ������� �����������
						M_Ind_Set_state(STATE_VIEW_SPEED_FAN_SETUP);
					break;
					case STATE_VIEW_SPEED_FAN_SETUP:		 	//���������� ������ �������� �����������

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
