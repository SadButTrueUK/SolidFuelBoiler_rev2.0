#ifndef _MODULE_MANAGEMENT_H_
#define _MODULE_MANAGEMENT_H_

#include "stdint.h"

#define QUANTITY_MOTORS 			4
#define QUANTITY_OF_FUEL_TYPE		3
#define SIZE_BUFFER     			53
#define IS_FAILURE 					1
#define NO_FAILURE 					0U

/* �������� �������� ��������� ������ ����������  */
#define STATE_WAITING				0U
#define STATE_FUEL_SUPPLY			1U
#define STATE_BURNING				2U
#define STATE_PAUSE					3U
#define STATE_CLEAN_CHIMNEY			4U
#define STATE_FAILURE				5U

#define IS_DRAUGHT                  1
#define NO_DRAUGHT                  0

/*���� ������ */
#define CODE_FAILURE_IS_NO_FAILURE							0U
#define CODE_FAILURE_BREAK_T_GAS_SENSOR                     1U
#define CODE_FAILURE_SHORT_CIRCUIT_T_GAS_SENSOR             2U
#define CODE_FAILURE_BREAK_T_WATER_SENSOR					3U
#define CODE_FAILURE_SHORT_CIRCUIT_T_WATER_SENSOR			4U
#define CODE_FAILURE_MOTOR_LS_DISPENSER_START				5U
#define CODE_FAILURE_MOTOR_LS_DISPENSER_FINISH				6U
#define CODE_FAILURE_MOTOR_LS_SHATTER_START                 7U
#define CODE_FAILURE_MOTOR_LS_SHATTER_FINISH				8U
#define CODE_FAILURE_MOTOR_LS_AFTER_SHATTER_FINISH			9U

#define CODE_FAILURE_MOTOR_LS_DISPENSER_START_FALSE_ON			10U
#define CODE_FAILURE_MOTOR_LS_DISPENSER_FINISH_FALSE_ON			11U
#define CODE_FAILURE_MOTOR_LS_SHATTER_START_FALSE_ON			12U
#define CODE_FAILURE_MOTOR_LS_SHATTER_FINISH_FALSE_ON			13U
#define CODE_FAILURE_MOTOR_LS_AFTER_SHATTER_FINISH_FALSE_ON		14U

#define CODE_FAILURE_MOTOR_LS_AGITATOR							15U
#define CODE_FAILURE_DRAUGHT									16U
#define CODE_FAILURE_NO_220V									17U
#define CODE_FAILURE_12V_CURRENT_OVERLOAD                       18U
#define CODE_FAILURE_OVERHEAT                                   19U


/*���� ������ ��������� � ��������� ������� */
#define CALC_PARAMS_PERIOD				0U
#define START_BURNING					1U
#define INCREASE_TEMPERATURE			2U
#define ECONOM_MODE                     3U
#define MAINTENANCE_TEMPERATURE_CYCLE	4U
#define MAINTENANCE_TEMPERATURE_INCR	5U
 
/* ������ */
#define MAINTENANCE_TEMPERATURE     5U
#define BURNING_OFF					6U


#define LOW_THRESHOLD_IN_BURNING_TEMPER_GAS             6U   //��������� �������� ����������� ���� (60 ��������), 
																	 //���� �������� ������ ������� �� ������ ����
#define TIMEOUT_CHECK_FAILURE_DRAUGHT					6000U 		//600 ������ (10 �����)	
#define TIMEOUT_CHECK_CHANGE_TEMPERATURE_WATER          18000U   //30 �����


/*������� ������� ���������� */
#define INDEX_OF_DISPENSER			0
#define INDEX_OF_AGITATOR			1
#define INDEX_OF_SHATTER			2

//to do ������������ ��� �������
#define INDEX_OF_CODE_FAILURE							50
#define INDEX_OF_TEMPER_SETUP							39
#define INDEX_OF_LEVEL_FAN_ROTATION_SPEED_MAINTENANCE	16
#define INDEX_OF_LEVEL_FAN_ROTATION_SPEED_INCREASE		47

#define TEMPERATURE_DECREASED				1
#define TEMPERATURE_INCREASED_OR_EQUAL		0
#define NUMBER_OF_FUEL_TYPE	3

#define PAUSE_IN_CYCLE	0
#define WORK_IN_CYCLE	1

typedef struct 
{
	uint8_t  time_accel;   				//����� ������� ��������� � 1/100 �. �������� �������� 10...100 (100��...1�)
	uint8_t  max_time_work;			//������������ ����� �������� ��������� � �. �������� �������� 1...60 (1�...60�)  
	uint8_t  min_PWM_accel; 			//����������� ������� ���������� ���� ��� ������� ���������. �������� �������� 28...100 
	uint8_t  quantity_repeat_try;   		//���������� ��������� ������� �������� ��������� ��� �������������� ���������, 
									//����� �������� ���������� ������� ������
}Motor_t;

typedef struct 
{
	uint8_t min_turn_percent;									//����������� ������� �������� �������� �����������. �������� �������� 2...4 
	uint8_t max_turn_percent;									//������������ ������� �������� �������� �����������. �������� �������� 4...8. ������� �� �������� ��������
	uint8_t time_work_in_cycle[NUMBER_OF_FUEL_TYPE];			//����� ������ ����������� � ����� ������-����� � ��������. �������� �������� 5...120
	uint8_t time_pause_in_cycle[NUMBER_OF_FUEL_TYPE];			//����� ������� ����������� � ����� ������-����� � �������� ������. 
                                                                //�������� �������� 12...360 (2 - 60 �����)
	uint8_t delta_from_cycle_to_heat[NUMBER_OF_FUEL_TYPE];		//������� ����� ������� � ������������� ������������� (2...5), ��� ������� ����������� ����� 
                                                                //������-����� (��� ��������� �����)
	uint8_t time_accel_fan[NUMBER_OF_FUEL_TYPE];				//����� ������� ����������� �� ��� �� ���� �������� ��� ����� � ����� ������� � �������� ������ �� 12 �� 30
	uint8_t delta_temper_for_econom_mode[NUMBER_OF_FUEL_TYPE];  //������� ����� ������������� � ������� ������������, �� ������� 
                                                                // ���������� ��������� �� ����������� ������� (��� ���������� �������� �������)
	uint8_t level_fan_in_econom_mode[NUMBER_OF_FUEL_TYPE];		// ������� �������� ����������� � �������� �� ������-����� �� 2 �� 4
	uint8_t level_fan_in_smoldering[NUMBER_OF_FUEL_TYPE];		// ������� �������� ����������� � ������ ��������/������ �� 2 �� 4
}Fan_t;

typedef struct 
{
	Motor_t Motor[QUANTITY_MOTORS]; 	//������ �������� ���������� (�������, ����������, ��������)
	Fan_t   Fan; 					  		  	//��������� �����������
	uint8_t temper_setup;				  		//������������� �����������
	uint8_t fuel_type;					  		//��� �������
	uint8_t enable_sound;				  		//���� ���������� �����. 1 - ��������, 0 - ��������
	uint8_t time_auto_exit;	  			  		//����� � �������� �� ��������� ��������, ���� ��� �������� ������������, ������� �� ����
	uint8_t period_load_fuel_in_heat[QUANTITY_OF_FUEL_TYPE];   //������ �������� ������� � ������ ������� � ����������� �� ������� ���� �������
	uint8_t delta_temper_threshold;				//��������� �������� ������� ����� ������� � ������������� ������������, 
                                                //�� ������� ����������� ����������
	uint8_t rotational_speed_fan;		  		//������� �������� �������� ����������� � ������� ������
	uint8_t time_work_ashCleaner;               //����� ������ ��������� ������ ���� (� ��������)
    uint8_t period_work_ashCleaner;             //������ ����� ����������� ��������� ������ ���� (� ������ ������)
    uint8_t code_failure;	  			     	//���  ������
	uint8_t last_state;	  				  		//��� �������� ��������� � �������� ���������
	uint8_t software_version;			  		//������ ������������ ����������� ��. ���������� � 1.00
}MENU_PARAMETERS; 

typedef union 
{
	MENU_PARAMETERS menu_parameters;
	uint8_t buffer[SIZE_BUFFER]; 
}ParametersBuffer;

ParametersBuffer*  M_Mngm_Get_parameters_buffer(void);
uint8_t             M_Mngm_Get_state(void);
uint8_t             M_Mngm_Get_Code_Failure(void);
uint8_t             M_Mngm_Check_Failure(void);
uint8_t             M_Mngm_Get_previous_state(void);
uint8_t             M_Mngm_get_burning_state(void);
void                M_Mngm_Run (void);
void                M_Mngm_waiting(void);
void                M_Mngm_fuel_supply(void);
void                M_Mngm_burning(void);
void                M_Mngm_pause(void);
void                M_Mngm_clean_chimney(void);
void                M_Mngm_failure(void);
void                M_Mngm_Set_state(uint8_t value);
void                M_Mngm_need_to_pause(const uint8_t prev_state);
void                M_Mngm_Set_Code_Failure(uint8_t value);
void                M_Mngm_clear_timeouts(void);
void                M_Mngm_set_saved_temperature_water(uint8_t value);
void                M_Mngm_check_draught_failure(void);
BOOL                M_Mngm_check_change_temperature_water(void);
void                M_Mngm_Set_state_draught(BOOL value);
BOOL    			M_Mngm_accel_fan(void);
BOOL 				M_Mngm_cyclic_mode(void);
void 				M_Mngm_clear_accel_fan(void);
void 				M_Mngm_clear_cyclic_mode(void);
BOOL 				M_Mngm_get_phase_cycle(void);
uint8_t* 			M_Mngm_get_pFanLevel(void);
uint8_t 			M_Mngm_get_fanParamOffset(void);
void 				M_Mngm_set_burning_state(uint8_t value);


#endif
