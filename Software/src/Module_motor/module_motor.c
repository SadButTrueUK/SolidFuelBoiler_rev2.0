#include "module_management.h"
#include <p18cxxx.h>
#include <string.h>
#include "module_motor.h"
#include "module_logic_inputs.h"
#include "module_indication.h"
#include "interrupts.h"
#include "main.h"
#include "OSA.h"


#define PWM_PERIOD                  25U  			//25 ����� ����. ������ ���� �������� 211���*25
#define MAX_PWM_DUTY_PERCENT        100U

#define ENABLE_TMR2_INTR            2
#define DISABLE_TMR2_INTR           0

#define NULL                        0

#define ACCELERATION_MOTOR			0U
#define WORKING_MOTOR				1U
#define STOPPING_MOTOR				2U
#define BRAKING_MOTOR				3U

#define CALC_PARAMS									0U
#define ACCELERATION								1U
#define MOTOR_IS_ACCELERATED						2U

#define MOTOR_IN_START_OR_END_POSITION              1U
#define MOTOR_IN_FAILURE                            2U
#define MOTOR_CHECKING                              0U

#define TIME_BRAKE_MOTOR_CONST                      50U  	 //����� ���������� ��������� 20 ��
#define TIME_PAUSE_DISPENSER_CONST                  2000U   //����� ����� �������� ��� �������� ������� (� ��)
#define TIME_AGITATOR_SENSOR_SURVEY                 8500U

//����� (�c), �� ��������� �������� ��� �������� ��������� ������ �������� ��������� ��������
#define TIME_CTRL_LS_AFTER_BEGIN				3000U
#define TIME_ROTATE_MOTOR_IN_REVERSE            45U  	 //����� (�c) ���������� �����������������
//#define TIME_ROTATE_MOTOR_IN_REVERSE          30U
#define TIME_PAUSE_SHATTER_CONST                2000U    //����� ����� �������� ��� �������� �������

#define TIMER2_INIT_VALUE                       0b00001101
#define TIMER2_OFF_VALUE                        0

#define FAILURE                                 3U
#define NEED_REVERSE                            2U
#define NEED_NEXT_STEP                          1U
#define IS_BUSY                                 0U

#define IS_FALSE_LS_FAILURE                     1
#define NO_FALSE_LS_FAILURE                     0

#define BRAKE_HIGH_SW                           1
#define ROTATE_REVERSE                          0


#define QUESTION_LS_FALSE_OFF 		1
#define QUESTION_LS_FALSE_ON 		0

#define PIN_COMMON_HALF_BRIDGE_H        LATHbits.LATH0     
#define PIN_COMMON_HALF_BRIDGE_L        LATHbits.LATH1
#define TRIS_COMMON_HALF_BRIDGE_H       TRISHbits.TRISH0
#define TRIS_COMMON_HALF_BRIDGE_L       TRISHbits.TRISH1

#define PIN_AGITATOR_1_SECOND_HALF_H    LATHbits.LATH3
#define PIN_AGITATOR_1_SECOND_HALF_L    LATEbits.LATE0
#define TRIS_AGITATOR_1_SECOND_HALF_H   TRISHbits.TRISH3
#define TRIS_AGITATOR_1_SECOND_HALF_L   TRISEbits.TRISE0

#define PIN_AGITATOR_2_SECOND_HALF_H    LATHbits.LATH2   
#define PIN_AGITATOR_2_SECOND_HALF_L    LATEbits.LATE1
#define TRIS_AGITATOR_2_SECOND_HALF_H   TRISHbits.TRISH2
#define TRIS_AGITATOR_2_SECOND_HALF_L   TRISEbits.TRISE1

#define PIN_DISPENSER_SECOND_HALF_H     LATGbits.LATG3
#define PIN_DISPENSER_SECOND_HALF_L     LATGbits.LATG0
#define TRIS_DISPENSER_SECOND_HALF_H    TRISGbits.TRISG3
#define TRIS_DISPENSER_SECOND_HALF_L    TRISGbits.TRISG3

#define PIN_SHATTER_SECOND_HALF_H       LATFbits.LATF5   
#define PIN_SHATTER_SECOND_HALF_L       LATFbits.LATF6
#define TRIS_SHATTER_SECOND_HALF_H      TRISFbits.TRISF5
#define TRIS_SHATTER_SECOND_HALF_L      TRISFbits.TRISF6

#define PIN_ASH_CLEANING_SECOND_HALF_H  LATFbits.LATF7
#define PIN_ASH_CLEANING_SECOND_HALF_L  LATGbits.LATG4
#define TRIS_ASH_CLEANING_SECOND_HALF_H TRISFbits.TRISF7
#define TRIS_ASH_CLEANING_SECOND_HALF_L TRISGbits.TRISG4

typedef struct 
{
	uint16_t time_step_accel;				//��� ������� ������� ���������� ������� ���������
	uint16_t time_work_motor;               //��� ������� ������� ������������ ������ ���������		
	uint16_t time_brake_motor;              //��� ������� ������� ���������� ���������
	uint16_t time_rotate_motor_in_reverse;  //��� ������� ������� ������� ��������� ��� ����������
	uint16_t time_pause;					//��� ������� ����� ����� ����� ������������ �������� ��� �������� �����	
	uint16_t time_ctrl_ls_after_begin;		//��� ������� ������� ����� �������� ����������� ��������� ��������� ��� �������� ���������
	uint16_t time_ls_agitator_survey;		//��� ������� ������� �������� �������� ������� ����������
}TIME_M_Motor;


//TO DO ��������� ����� ������ ���������� � 15 � �� 30 �, ����� ������ ������� � 5 � �� 15 � (#define TIME_AGITATOR_SENSOR_SURVEY)

uint8_t cnt_duty = 0;
uint8_t accel_state = 0;
uint8_t saved_cnt_duty = 0;
uint8_t M_Motor_PWM_period = 0;
uint8_t M_Motor_state = 0;
BOOL ctrl = OFF;
uint8_t direction = TO_FORWARD_DISPENSER;
uint8_t num_motor = 0;
uint8_t ctrl_shatter = NO_MOVEMENT;  //��� ���������� ��������� � ������ ������ ��������
uint8_t cnt_step = 0;
BOOL M_Motor_false_state_LS[QUANTITY_FALSE_LS] = {0, 0, 0, 0, 0};   				//��� ������ ����� ����������� ����������
BOOL M_Motor_direction_question_LS[QUANTITY_FALSE_LS] = {0, 0, 0, 0, 0};  	//1 - ����� �� ������ ����������, 0 - ����� �� ������ ���������
BOOL* temp_start_ls = NULL;
uint8_t temp_index;
uint8_t M_Motor_prev_state = 0;

TIME_M_Motor time_M_Motor = {0, 0, 0, 0, 0, 0, 0};
FailureMotor M_Motor_failure_motor[QUANTITY_MOTORS] = {{0, 0}, {0, 0}, {0,0}}; 


/* ������ �������� ����� ������� � ������ ������ ��� �������� ��������� � ������ ����������� */
const rom IOport_motor motor_pins_forward[QUANTITY_MOTORS] =
{
	//�������
	{
        (volatile uint8_t* const)&LATH, 0,  //������� ���� 1-�� ���������
        (volatile uint8_t* const)&LATG, 0   //������ ���� 2-�� ���������
    }, 			
	
	//����������
	{
        (volatile uint8_t* const)&LATH, 0,	//������� ���� 1-�� ���������
        (volatile uint8_t* const)&LATE, 0   //������ ���� 3-�� ���������
    }, 			
	
    //�������� 
	{
        (volatile uint8_t* const)&LATH, 0,		//������� ���� 1-�� ���������
        (volatile uint8_t* const)&LATF, 6        //������ ���� 5-�� ���������
    },			
    
    //������ ����
    {
        (volatile uint8_t* const)&LATH, 0,		//������� ���� 1-�� ���������
        (volatile uint8_t* const)&LATG, 4      //������ ���� 4-�� ���������
    }
};

/* ������ �������� ������� � ������ ������ ��� �������� ��������� � �������� ����������� */
const rom IOport_motor motor_pins_backward[QUANTITY_MOTORS] =
{
	//�������
	{
        (volatile uint8_t* const)&LATG, 3,	//������� ���� 2-�� ���������
        (volatile uint8_t* const)&LATH, 1   //������ ���� 1-�� ���������
    }, 		

	//����������
	{
        (volatile uint8_t* const)&LATH, 3,	//������� ���� 3-�� ���������
        (volatile uint8_t* const)&LATH, 1   //������ ���� 1-�� ���������
    }, 		
    	
    //�������� 
	{
        (volatile uint8_t* const)&LATF, 5,	//������� ���� 4-�� ���������
        (volatile uint8_t* const)&LATH, 1   //������ ���� 1-�� ���������
    },		
    
    //������ ����
    {
        (volatile uint8_t* const)&LATF, 7,	//������� ���� 1-�� ���������
        (volatile uint8_t* const)&LATH, 1   //������ ���� 1-�� ���������
    }
};

/* ������ �������� ������� ������ ���� ���������� ��� ���������� */
const rom IOport_motor  motor_pins_brake_high_sw[QUANTITY_MOTORS] = 
{
	//�������
	{
        (volatile uint8_t* const)&LATH, 0,	//������� ���� 1-�� ���������
        (volatile uint8_t* const)&LATG, 3   //������� ���� 2-�� ���������
    }, 		

	//����������
	{
        (volatile uint8_t* const)&LATH, 0,	//������� ���� 1-�� ���������
        (volatile uint8_t* const)&LATH, 3   //������� ���� 3-�� ���������
    }, 		

	//�������� 
	{
        (volatile uint8_t* const)&LATH, 0,	//������� ���� 1-�� ���������
        (volatile uint8_t* const)&LATF, 5   //������� ���� 4-�� ���������
    },		
    
    //������ ����
    {
        (volatile uint8_t* const)&LATH, 0,		//������� ���� 1-�� ���������
        (volatile uint8_t* const)&LATF, 7   //������ ���� 1-�� ���������
    }
};

/* ������ �������� ������ ������ ���� ���������� ��� ���������� */
const rom IOport_motor  motor_pins_brake_low_sw[QUANTITY_MOTORS] = 
{
	//�������
	{
        (volatile uint8_t* const)&LATH, 1,	//������ ���� 1-�� ���������
        (volatile uint8_t* const)&LATG, 0   //������ ���� 2-�� ���������
    }, 		

	//����������
	{
        (volatile uint8_t* const)&LATH, 1,	//������ ���� 1-�� ���������
        (volatile uint8_t* const)&LATE, 0   //������ ���� 3-�� ���������
    }, 		

	//�������� 
	{
        (volatile uint8_t* const)&LATH, 1,	//������ ���� 1-�� ���������
        (volatile uint8_t* const)&LATG, 4   //������ ���� 4-�� ���������
    },		

    //������ ���� 
	{
        (volatile uint8_t* const)&LATH, 1,	//������ ���� 1-�� ���������
        (volatile uint8_t* const)&LATF, 6   //������ ���� 4-�� ���������
    }	
};

const rom IOport_motor*  ptr_to_motor_pins = &motor_pins_forward [INDEX_OF_DISPENSER]; 
											
//��������� ������� ������ 
static BOOL    M_Motor_check_ls_after_begin_start(BOOL ls, uint8_t index);
static void    M_Motor_check_false_LS (LimitSwitch* struct_ls, const uint8_t size);
static void    M_motor_forming_direction_question_LS(BOOL disp_st, BOOL disp_fin, BOOL shat_st, BOOL shat_fin, BOOL shat_after_fin);
static uint8_t M_Motor_check_motor(uint8_t index, BOOL limit_switch, uint8_t type_of_ls, uint8_t* cnt_fail);
static BOOL    M_Motor_is_brake(const rom IOport_motor* motor_pins, uint8_t which_ls, uint8_t num);
static void    M_Motor_Timer2_change(const uint8_t value_timer_ctrl, const uint8_t en_intr);
static void    M_Motor_clear_accel_state ( void );
static uint8_t M_Motor_rotate (uint8_t index, BOOL limit_switch, uint8_t type_of_ls );
static void    M_Motor_is_stopped ( const rom IOport_motor* motor_pins );
static void    M_Motor_is_worked ( const rom IOport_motor* motor_pins );
static void    M_Motor_accel ( uint8_t index );


void M_Motor_ctor( void )
{
    PIN_COMMON_HALF_BRIDGE_H           = OFF;         
    PIN_COMMON_HALF_BRIDGE_L           = OFF;  
    TRIS_COMMON_HALF_BRIDGE_H          = OUT;  
    TRIS_COMMON_HALF_BRIDGE_L          = OUT;  

    PIN_AGITATOR_1_SECOND_HALF_H       = OFF;   
    PIN_AGITATOR_1_SECOND_HALF_L       = OFF; 
    TRIS_AGITATOR_1_SECOND_HALF_H      = OUT; 
    TRIS_AGITATOR_1_SECOND_HALF_L      = OUT; 

    PIN_AGITATOR_2_SECOND_HALF_H       = OFF;           
    PIN_AGITATOR_2_SECOND_HALF_L       = OFF;    
    TRIS_AGITATOR_2_SECOND_HALF_H      = OUT; 
    TRIS_AGITATOR_2_SECOND_HALF_L      = OUT; 

    PIN_DISPENSER_SECOND_HALF_H        = OFF;     
    PIN_DISPENSER_SECOND_HALF_L        = OFF;     
    TRIS_DISPENSER_SECOND_HALF_H       = OUT; 
    TRIS_DISPENSER_SECOND_HALF_L       = OUT; 

    PIN_SHATTER_SECOND_HALF_H          = OFF;      
    PIN_SHATTER_SECOND_HALF_L          = OFF;        
    TRIS_SHATTER_SECOND_HALF_H         = OUT; 
    TRIS_SHATTER_SECOND_HALF_L         = OUT; 

    PIN_ASH_CLEANING_SECOND_HALF_H     = OFF;  
    PIN_ASH_CLEANING_SECOND_HALF_L     = OFF;   
    TRIS_ASH_CLEANING_SECOND_HALF_H    = OUT; 
    TRIS_ASH_CLEANING_SECOND_HALF_L    = OUT; 
}


void M_Motor_clear_parameters(void)
{
	M_Motor_state = STATE_MODULE_MOTOR_WAITING;
	direction = TO_FORWARD_DISPENSER;
	cnt_step = 0;
	num_motor = INDEX_OF_AGITATOR;
	ctrl = OFF;
}

/* 
������� �������� ��������� ��������� ��������� ����� ������ �������� ��������� 
����� ����� TIME_CTRL_LS_AFTER_BEGIN 
������� ���������:

*/
static BOOL M_Motor_check_ls_after_begin_start(BOOL ls, uint8_t index)
{
	if(M_LI_Get_Limit_Switches()->ls_hopper_cover_state)  //� ������ "����� ��� �������� �� ��������"
	{
		if(time_M_Motor.time_ctrl_ls_after_begin++ == TIME_CTRL_LS_AFTER_BEGIN )
		{
			M_Motor_false_state_LS[index] = ls;
			time_M_Motor.time_ctrl_ls_after_begin = 0;
			if(ls)
			{	
				M_Motor_state = STATE_MODULE_MOTOR_FAILURE;			
			 	M_Motor_is_stopped(ptr_to_motor_pins);
			 	return IS_FALSE_LS_FAILURE;
			}
			else
				return NO_FALSE_LS_FAILURE;
		}	
	}
	return NO_FALSE_LS_FAILURE;
}

/* ������������ ����� ������ ���������� � ������ M_Motor_direction_question_LS */
static void M_motor_forming_direction_question_LS(BOOL disp_st, BOOL disp_fin, BOOL shat_st, BOOL shat_fin, BOOL shat_after_fin)
{
	M_Motor_direction_question_LS[0] = disp_st; 
	M_Motor_direction_question_LS[1] = disp_fin;
	M_Motor_direction_question_LS[2] = shat_st;
	M_Motor_direction_question_LS[3] = shat_fin;
	M_Motor_direction_question_LS[4] = shat_after_fin;
}

void M_Motor_clear_false_state_LS(const uint8_t size)
{
	uint8_t counter;	

	for(counter = 0; counter < size; counter++)
	{
		M_Motor_false_state_LS[counter] = 0;
	}
}

/* �������� ������� ��������� ���������� � ����������� �������� ���������� */
static void M_Motor_check_false_LS (LimitSwitch* struct_ls, const uint8_t size)
{
	uint8_t counter;	

	for(counter = 0; counter < size; counter++)
	{
		#ifdef NO_CONTROL_FALSE_STATE_LS
			M_Motor_false_state_LS[counter] = 0;
		#else
			M_Motor_false_state_LS[counter] = *((BOOL*)struct_ls + counter) ^ M_Motor_direction_question_LS[counter] ;
		#endif
	}
}

BOOL* M_Motor_get_false_state_LS(void)
{
	return M_Motor_false_state_LS;
}

void M_Motor_set_state (uint8_t value)
{
	M_Motor_state = value;
}

uint8_t M_Motor_get_direction(void)
{
	return direction;
}

void M_Motor_set_work (BOOL value)
{
	ctrl = value;
}

BOOL M_Motor_get_work(void)
{
	return ctrl;
}

uint8_t	M_Motor_get_state(void)
{
	return M_Motor_state;
}

void M_Motor_set_ctrl_shatter (uint8_t value)
{
	ctrl_shatter = value;
}

uint8_t M_Motor_get_ctrl_shatter (void)
{
	return ctrl_shatter;
}


FailureMotor* M_Motor_get_state_failure(uint8_t index)
{
	return &M_Motor_failure_motor[index];
}

void M_Motor_clear_struct_failure_motor(void)
{
	uint8_t count;
	for(count = 0; count < SIZE_STRUCT_MOTORS; count++)
		memset(&M_Motor_failure_motor[count], 0, sizeof M_Motor_failure_motor[count]);
	memset(&time_M_Motor, 0, sizeof time_M_Motor);
}


uint8_t M_Motor_get_prev_state(void)
{
	return M_Motor_prev_state;
}


/*��������� ���������� � ��������� ���������
������� ���������: 
- ������ ������� �������� ���������� index
- ��������� ���������������� ���������� ��������� limit_switch
- ��� ��������� type_of_ls
*/
static uint8_t M_Motor_rotate(uint8_t index, BOOL limit_switch, uint8_t type_of_ls)
{
	
	uint8_t pos_motor = MOTOR_CHECKING; 
	static BOOL is_motor_failure = FALSE;
	
	if(!M_LI_Get_Limit_Switches()->ls_hopper_cover_state )
	{
		M_Motor_is_stopped(ptr_to_motor_pins);
	}
	else
	{
		switch(cnt_step) 
		{
			case ACCELERATION_MOTOR:   		//��������� ������� ���������
				if(limit_switch && type_of_ls != AGITATOR_LS) //��������� � ��������� ���������, ������� �� ������� (�� ��������� ��� ������� ����������) 
				{
					if(!accel_state)
					{
						pos_motor =  MOTOR_IN_START_OR_END_POSITION;
						break;		
					}
					else
					{
						M_Motor_is_stopped(ptr_to_motor_pins);
						M_Motor_failure_motor[index].is_failure = OFF;
						M_Motor_clear_accel_state();
						time_M_Motor.time_step_accel = 0;
						cnt_step = STOPPING_MOTOR;
						 is_motor_failure = FALSE;
						break;
					}
				}
				M_Motor_accel(index); 							//��������� ���������
				if (accel_state == MOTOR_IS_ACCELERATED) 		//���� ��������� ��������
				{
					M_Motor_clear_accel_state(); 	
					cnt_step++; 									//������� � ����� ������������� ������� ������ ���������
				}	
				break;
			case WORKING_MOTOR:			//������� ��������� ��������� (������ �� ������������ ��������)
				M_Motor_is_worked(ptr_to_motor_pins); 		//�������� ��������������� ������� � ������ ���� ����������
				if(limit_switch && type_of_ls != AGITATOR_LS) //��������� � ��������� ��������� 
				{
					cnt_step++;
					time_M_Motor.time_work_motor = 0;
					M_Motor_failure_motor[index].is_failure = OFF;
					M_Motor_is_stopped(ptr_to_motor_pins);
					is_motor_failure = FALSE;
					break;
				}
				else if(type_of_ls == AGITATOR_LS)  //��� ����������
				{
					//���� �������� �������� ������ ������� ����������
					if(time_M_Motor.time_ls_agitator_survey ++ == TIME_AGITATOR_SENSOR_SURVEY )
					{
						time_M_Motor.time_ls_agitator_survey = 0;
						if(Intr_get_is_impulse_agitator_sensor())  //�� ������ ������ ��� ������� �� �������	
						{
							Intr_set_is_impulse_agitator_sensor(FALSE);	
						}
						else  //������� � ���������� ��������� � ��������� �������� ������
						{
							time_M_Motor.time_work_motor = 0;
							cnt_step++;
							M_Motor_is_stopped(ptr_to_motor_pins);
							is_motor_failure = TRUE;
							break;
						}
					}
				}
				//���� ������ ������������� ������� ������ ��������� �������, � ��������� �������� �� ��������
				if(time_M_Motor.time_work_motor++ == (M_Mngm_Get_parameters_buffer()->menu_parameters.Motor[index].max_time_work)*1000U)
				{
					cnt_step++;
					Intr_set_is_impulse_agitator_sensor(FALSE);
					time_M_Motor.time_ls_agitator_survey = 0;
					M_Motor_is_stopped(ptr_to_motor_pins);
					time_M_Motor.time_work_motor = 0;
				}
				break;
			case STOPPING_MOTOR:		//������� ���������
				M_Motor_is_stopped(&motor_pins_brake_high_sw[index]);
				cnt_step++;
				break;
			case BRAKING_MOTOR:		//���������� ��������� (��������� ������� ������ � ������ ����������)
				if(M_Motor_is_brake(&motor_pins_brake_high_sw[index], type_of_ls, index))
				{
					M_Motor_is_stopped(&motor_pins_brake_high_sw[index]);
					cnt_step = ACCELERATION_MOTOR;  
					if((limit_switch && type_of_ls != AGITATOR_LS) || (type_of_ls == AGITATOR_LS && !is_motor_failure))
						pos_motor =  MOTOR_IN_START_OR_END_POSITION;
					if((!limit_switch && type_of_ls != AGITATOR_LS) ||  (type_of_ls == AGITATOR_LS && is_motor_failure))
					{
						is_motor_failure = FALSE;
						pos_motor =  MOTOR_IN_FAILURE;
						M_Motor_failure_motor[index].is_failure = ON; //������������ ��� ������
						M_Motor_failure_motor[index].type_ls = type_of_ls;
					}
				}
				break;
		}
	}
	return pos_motor;
}


const rom  IOport_motor* M_Motor_get_ptr_to_motor_pins(void)
{
	return ptr_to_motor_pins;
}


static uint8_t M_Motor_check_motor(uint8_t index, BOOL limit_switch, uint8_t type_of_ls, uint8_t* cnt_fail)
{
	if(M_Motor_rotate(index, limit_switch, type_of_ls) != MOTOR_CHECKING)
	{ 
		if(M_Motor_failure_motor[index].is_failure)  //���� ���� ������� ������
		{
			if((*cnt_fail) == M_Mngm_Get_parameters_buffer()->menu_parameters.Motor[index].quantity_repeat_try)
			{		
				*cnt_fail = 0;
				return FAILURE;
			}
			else
			{
				(*cnt_fail)++;
				M_Motor_failure_motor[index].is_failure = 0;		/*������� �� ����� ������� */
				return NEED_REVERSE;
			}
		}
		else
		{	
			*cnt_fail = 0;
			return NEED_NEXT_STEP;
		}
	}
	else
	{
		return IS_BUSY;
	}
}

/* ���������� �������� ��������� ������ ����������  */
void M_Motor_Run(void)
{
	static uint8_t cnt_failure_forward = 0;
	static uint8_t cnt_failure_backward = 0;
	static BOOL after_pause = OFF;
	static BOOL shatter_reverse = OFF;
	static uint8_t ls_type;
		
	if(M_Ind_Get_state() == STATE_IND_INIT)
	{
		return;
	}
	
	switch(M_Motor_state)
	{
		//�������� ���������� ��������� ���������� (�������� � ��������)
		//�������� ����������� ������ ����� ��������� �������� ��������
		//����� ������� ���� � ��������� ��������, ���� � ��������� ������ ������
		case CHECK_START_POSITION: 				
			M_Motor_prev_state = M_Motor_state;
			switch(num_motor)
			{
				case INDEX_OF_DISPENSER:
					ptr_to_motor_pins = &motor_pins_backward[INDEX_OF_DISPENSER];
					if (M_Motor_rotate(INDEX_OF_DISPENSER, M_LI_Get_Limit_Switches()->ls_dispenser_start_state, 
					START_LS) != MOTOR_CHECKING)
					{
						if(M_Motor_failure_motor[INDEX_OF_DISPENSER].is_failure)
						{
							cnt_step = 0;
							M_Motor_state = STATE_MODULE_MOTOR_FAILURE;
						}
						else
						{
							cnt_step = 0;
							num_motor = INDEX_OF_SHATTER;
							ptr_to_motor_pins = &motor_pins_backward[INDEX_OF_SHATTER];
						}
					}
				break;	
				case INDEX_OF_SHATTER:		
					if(M_Motor_rotate(INDEX_OF_SHATTER, M_LI_Get_Limit_Switches()->ls_shatter_start_state,
					START_LS) != MOTOR_CHECKING)
					{
						if(M_Motor_failure_motor[INDEX_OF_SHATTER].is_failure)
						{
							cnt_step = 0;
							M_Motor_state = STATE_MODULE_MOTOR_FAILURE;		
						}
						else 
						{
							cnt_step = 0;
							M_Motor_state = STATE_MODULE_MOTOR_WAITING;
							num_motor = INDEX_OF_AGITATOR;
						}
					}
				break;
			}
			break;
		
		case STATE_MODULE_MOTOR_FAILURE:	//����� "������"
			ctrl = OFF;

			break;
		case STATE_MODULE_MOTOR_WAITING:	//����� �������� ������� �������� ������
			//ctrl = TRUE; //!!!!!!��� �������
			M_Motor_prev_state = M_Motor_state;
			if(ctrl)
			{
				cnt_step = 0;
				M_Motor_state = STATE_MODULE_MOTOR_WORKING;
				M_Ind_Set_state(STATE_VIEW_SUPPLY_FUEL);
				M_Ind_Set_blink_mode(NEED_BLINK);
			}
				M_motor_forming_direction_question_LS(QUESTION_LS_FALSE_OFF, QUESTION_LS_FALSE_ON, QUESTION_LS_FALSE_OFF, QUESTION_LS_FALSE_ON, QUESTION_LS_FALSE_ON);
				//#ifndef NO_CONTROL_FALSE_STATE_LS
					M_Motor_check_false_LS(M_LI_Get_Limit_Switches(), QUANTITY_FALSE_LS);
				//#endif
		break;
		case STATE_MODULE_MOTOR_CLEAN_CHIMNEY:		//����� "������ ��������"
				M_Motor_prev_state = M_Motor_state;
				M_Ind_Set_blink_mode(NEED_BLINK);
				if(M_Motor_check_ls_after_begin_start(*temp_start_ls, temp_index))
				{	
					time_M_Motor.time_ctrl_ls_after_begin = 0;
					M_Motor_state = STATE_MODULE_MOTOR_FAILURE;
					break;		
				}
				if (M_Motor_rotate(INDEX_OF_SHATTER, *(M_LI_get_ptr_to_ls()), 
				ls_type) != MOTOR_CHECKING)
				{
					time_M_Motor.time_ctrl_ls_after_begin = 0;
					if(M_Motor_failure_motor[INDEX_OF_SHATTER].is_failure)
					{
						M_Motor_state = STATE_MODULE_MOTOR_FAILURE;
					}
					else
					{
						M_Motor_state = STATE_MODULE_MOTOR_WAITING_FOR_MOVE_CLEAN_CHIMNEY;
						ctrl_shatter = WAITING_MOVEMENT;
						M_Ind_Set_blink_mode(NO_NEED_BLINK);
					}
				}
		break;
		case STATE_MODULE_MOTOR_WAITING_FOR_MOVE_CLEAN_CHIMNEY:		//��������� ���������� ����� ��������� ��������� �������� � ������ "������ ��������"
			M_Motor_prev_state = M_Motor_state;
			if(ctrl_shatter == MOVEMENT_FORWARD) 		//���������� � �������� ������ �������� ��� � ��������
			{
				M_LI_set_ptr_to_ls(&(M_LI_Get_Limit_Switches()->ls_shatter_after_finish_state));	
				M_Motor_state = STATE_MODULE_MOTOR_CLEAN_CHIMNEY;
				ptr_to_motor_pins = &motor_pins_forward[INDEX_OF_SHATTER];
				ls_type = AFTER_FINISH_LS;
				M_Ind_Set_blink_mode(NEED_BLINK);
				cnt_step = 0;
				temp_start_ls = &(M_LI_Get_Limit_Switches()->ls_shatter_start_state); 
				temp_index =  INDEX_FALSE_STATE_LS_START_SHATTER;
			}
			else if(ctrl_shatter == MOVEMENT_BACKWARD)		//���������� � �������� ������ �������� ��� � ��������	
			{
				M_LI_set_ptr_to_ls(&(M_LI_Get_Limit_Switches()->ls_shatter_start_state));
				M_Motor_state = STATE_MODULE_MOTOR_CLEAN_CHIMNEY;
				ptr_to_motor_pins = &motor_pins_backward[INDEX_OF_SHATTER];
				ls_type = START_LS;
				M_Ind_Set_blink_mode(NEED_BLINK);
				cnt_step = 0;
				temp_start_ls = &(M_LI_Get_Limit_Switches()->ls_shatter_after_finish_state);
				temp_index = INDEX_FALSE_STATE_LS_AFTER_FINISH_SHATTER;
			}
			else if(ctrl_shatter == NO_MOVEMENT)
			{
				M_Motor_state = STATE_MODULE_MOTOR_WAITING;
			}
			else if(ctrl_shatter == WAITING_MOVEMENT)
			{
			
			}
		break;
		
		case STATE_MODULE_MOTOR_WORKING:	//�������� ������� ������� �� ������� � ����
			M_Motor_prev_state = M_Motor_state;
			switch(num_motor)
			{
				case INDEX_OF_AGITATOR:		//�������� ����������
						//LED_FAN_PIN = ON;
						ptr_to_motor_pins = &motor_pins_forward[INDEX_OF_AGITATOR];
						switch(M_Motor_check_motor(INDEX_OF_AGITATOR, M_LI_Get_Limit_Switches()->ls_agitator_state, AGITATOR_LS,
						&cnt_failure_forward))
						{
							case FAILURE:
								M_Motor_state = STATE_MODULE_MOTOR_FAILURE;
								cnt_step = 0;
							break;
							case NEED_NEXT_STEP:
								cnt_step = 0;
								num_motor = INDEX_OF_SHATTER; 
								direction = TO_FORWARD_SHATTER;
								//LED_FAN_PIN = OFF;
								break;
							case IS_BUSY:
							
							break;
						}
					break;
				case INDEX_OF_DISPENSER:	//�������� ��������
					switch(direction)		
					{
						case TO_FORWARD_DISPENSER:	//����������� �������� "�����"
							ptr_to_motor_pins = &motor_pins_forward[INDEX_OF_DISPENSER];
							if(M_Motor_check_ls_after_begin_start(M_LI_Get_Limit_Switches()->ls_dispenser_start_state, INDEX_FALSE_STATE_LS_START_DISPENSER))
							{	
								M_Motor_state = STATE_MODULE_MOTOR_FAILURE;
								break;
							}
							switch(M_Motor_check_motor(INDEX_OF_DISPENSER, M_LI_Get_Limit_Switches()->ls_dispenser_finish_state, FINISH_LS,
							&cnt_failure_forward))
							{
								case FAILURE:
									cnt_step = 0;
									M_Motor_state = STATE_MODULE_MOTOR_FAILURE;
									time_M_Motor.time_ctrl_ls_after_begin = 0;
								break;
								case NEED_NEXT_STEP:
									cnt_step = 0;
									direction = TIME_PAUSE_DISPENSER;
									time_M_Motor.time_ctrl_ls_after_begin = 0;
								break;
								case NEED_REVERSE:
									cnt_step = 0;
									direction = TO_BACKWARD_DISPENSER;							
									time_M_Motor.time_ctrl_ls_after_begin = 0;
								break;
								case IS_BUSY:
								break;	
							}
							break;
						case TO_BACKWARD_DISPENSER:		//����������� �������� "�����"
							ptr_to_motor_pins = &motor_pins_backward[INDEX_OF_DISPENSER];
							if(M_Motor_check_ls_after_begin_start(M_LI_Get_Limit_Switches()->ls_dispenser_finish_state, INDEX_FALSE_STATE_LS_FINISH_DISPENSER))
							{	
								M_Motor_state = STATE_MODULE_MOTOR_FAILURE;	
								break;
							}
							switch(M_Motor_check_motor(INDEX_OF_DISPENSER, M_LI_Get_Limit_Switches()->ls_dispenser_start_state, 
							START_LS, &cnt_failure_backward))
							{
								case FAILURE:
									cnt_step = 0;
									M_Motor_state = STATE_MODULE_MOTOR_FAILURE;
									time_M_Motor.time_ctrl_ls_after_begin = 0;
								break;
								case NEED_NEXT_STEP:
									direction = TO_FORWARD_DISPENSER;
									cnt_step = 0;
									if(after_pause)
									{
										num_motor = INDEX_OF_SHATTER;
										after_pause = OFF;
										direction = TO_BACKWARD_SHATTER;
									}
									time_M_Motor.time_ctrl_ls_after_begin = 0;
								break;
								case NEED_REVERSE:
									cnt_step = 0;
									direction = TO_FORWARD_DISPENSER;							
									time_M_Motor.time_ctrl_ls_after_begin = 0;
									break;
								case IS_BUSY:
								break;	
							}
							break;
						
						case TIME_PAUSE_DISPENSER:		//����� ����� �������� ����� � ����������� ���������� �� ����� TIME_PAUSE_DISPENSER_CONST
							if(time_M_Motor.time_pause++ == TIME_PAUSE_DISPENSER_CONST)
							{
								time_M_Motor.time_pause = 0;
								direction = TO_BACKWARD_DISPENSER;	
								after_pause = ON;
							}	
							break;
						
					}
					break;
				case INDEX_OF_SHATTER:	//�������� ��������� ��������
					switch(direction)		
					{
						case TO_FORWARD_SHATTER:		//����������� �������� "�����"
							ptr_to_motor_pins = &motor_pins_forward[INDEX_OF_SHATTER];
							if(M_Motor_check_ls_after_begin_start(M_LI_Get_Limit_Switches()->ls_shatter_start_state, INDEX_FALSE_STATE_LS_START_SHATTER))
							{	
								M_Motor_state = STATE_MODULE_MOTOR_FAILURE;
								break;
							}
							switch(M_Motor_check_motor(INDEX_OF_SHATTER, M_LI_Get_Limit_Switches()->ls_shatter_finish_state, FINISH_LS,
							&cnt_failure_forward))
							{
								case FAILURE:
									cnt_step = 0;
									M_Motor_state = STATE_MODULE_MOTOR_FAILURE;
									time_M_Motor.time_ctrl_ls_after_begin = 0;
									break;
								case NEED_NEXT_STEP:
									cnt_step = 0;
									time_M_Motor.time_ctrl_ls_after_begin = 0;
									if(!shatter_reverse) 
									{
									
										num_motor = INDEX_OF_DISPENSER; 
										direction = TO_FORWARD_DISPENSER;
									}
									else  //���� �������� �� �������� ��� �������� �������� �����, ���������� � ����� � ��������� �������� �����
									{
										shatter_reverse = OFF;
										direction = TO_BACKWARD_SHATTER;	
									}
									break;
								case NEED_REVERSE:
									cnt_step = 0;
									direction = TO_BACKWARD_SHATTER;							
									time_M_Motor.time_ctrl_ls_after_begin = 0;
									break;
								case IS_BUSY:
									break;	
							}
							break;
						case TO_BACKWARD_SHATTER:		//����������� �������� "�����"
							ptr_to_motor_pins = &motor_pins_backward[INDEX_OF_SHATTER];
							if(M_Motor_check_ls_after_begin_start(M_LI_Get_Limit_Switches()->ls_shatter_finish_state, INDEX_FALSE_STATE_LS_FINISH_SHATTER))
							{	
								M_Motor_state = STATE_MODULE_MOTOR_FAILURE;
								break;
							}
							switch(M_Motor_check_motor(INDEX_OF_SHATTER, M_LI_Get_Limit_Switches()->ls_shatter_start_state, START_LS,
							&cnt_failure_backward))
							{
								case FAILURE:
									cnt_step = 0;
									M_Motor_state = STATE_MODULE_MOTOR_FAILURE;
									time_M_Motor.time_ctrl_ls_after_begin = 0;
									break;
								case NEED_NEXT_STEP:
									cnt_step = 0;
									direction = TO_FORWARD_SHATTER;
									num_motor = INDEX_OF_AGITATOR;
									ctrl = OFF;
									after_pause = OFF;
									M_Ind_Set_blink_mode(NO_NEED_BLINK);
									M_Motor_state = STATE_MODULE_MOTOR_WAITING;
									if(M_Mngm_Get_state() == STATE_BURNING) 
										M_Ind_Set_state(STATE_VIEW_TEMPERATURE_REAL);
									time_M_Motor.time_ctrl_ls_after_begin = 0;
									break;
								case NEED_REVERSE:
									cnt_step = 0;
									direction = TO_FORWARD_SHATTER;							
									time_M_Motor.time_ctrl_ls_after_begin = 0;
									shatter_reverse = ON;
									break;
								case IS_BUSY:
									break;	
							}
							break;
				}
				break;
			}	
			break;
	}
}


static void M_Motor_clear_accel_state(void)
{
	accel_state = 0;
	M_Motor_PWM_period = 0;
	M_Motor_Timer2_change(TIMER2_OFF_VALUE, DISABLE_TMR2_INTR);
}


/*���������� ����������� ��������� (����������� ����������) 
���������� ������� ���� � ������ ���� � ��������� �����
 */
static void M_Motor_is_worked(const rom IOport_motor* motor_pins)
{
	*motor_pins->portReg_prim_half_bridge |= 1 << (motor_pins->pin_num_prim_half_bridge);	
	*motor_pins->portReg_sec_half_bridge |= 1 << (motor_pins->pin_num_sec_half_bridge);
}


/* 
���������� ���������
���������� 2 ������� ����� � ������ �����
����������:
0 -  ���� �� ������ ����� ���������� ���������
1 -  ���� ������ ����� ���������� ���������
*/
static BOOL M_Motor_is_brake(const rom IOport_motor* motor_pins, uint8_t which_ls, uint8_t num)
{
	static uint8_t step_brake = ROTATE_REVERSE;
	
	switch(step_brake)
	{
		case ROTATE_REVERSE:
			if (which_ls == AGITATOR_LS)
			{
				step_brake = BRAKE_HIGH_SW;	
				break;
			}
			M_Motor_is_worked(which_ls ==  START_LS ? &motor_pins_forward[num]  :  &motor_pins_backward[num]);
			if(time_M_Motor. time_rotate_motor_in_reverse++ ==  TIME_ROTATE_MOTOR_IN_REVERSE)
			{
				time_M_Motor. time_rotate_motor_in_reverse = 0;
				step_brake = BRAKE_HIGH_SW;
				M_Motor_is_stopped(which_ls ==  START_LS ? &motor_pins_forward[num]  :  &motor_pins_backward[num]);
			}
		break;
		case BRAKE_HIGH_SW:
			M_Motor_is_worked(motor_pins);
			if(time_M_Motor.time_brake_motor++ == TIME_BRAKE_MOTOR_CONST)
			{	
				time_M_Motor.time_brake_motor = 0;
				step_brake = ROTATE_REVERSE;
				return TRUE;
			}
	 	break;
	}
	return FALSE;
}
 

	
/*
���������� ���������� ��������� 
����������� � ��������� ����� ������� � ������ ����
*/
static void M_Motor_is_stopped(const rom IOport_motor* motor_pins)
{
	*motor_pins->portReg_prim_half_bridge &= ~(1 << (motor_pins->pin_num_prim_half_bridge));	
	*motor_pins->portReg_sec_half_bridge &= ~(1 << (motor_pins->pin_num_sec_half_bridge));
}


/* ��� ���������� ����������/����������� �/�2, ������� ����������� ����������� ��� ������� ��������� */
static void M_Motor_Timer2_change(const uint8_t value_timer_ctrl, const uint8_t en_intr)
{
	T2CON = value_timer_ctrl;
	PIE1 =  en_intr;
}

/* ���������� �������� ������� ������������� ��������� ����� �� min_PWM_accel �� 100%
�� ��������� ������� ������� � �������� ��������� ������������ ����
 ����������� ���������� "��������" ���� quantity_steps_accel
 */
static void M_Motor_accel(uint8_t index)
{
	static uint8_t quantity_steps_accel;
	static uint16_t delta_t_accel;
	uint16_t temp;
	
	switch(accel_state)
	{
		case CALC_PARAMS: //���������� ���������� ��� �������� ������� ����� �� ������������ ����������
			//�������� �� ���� �������� ����������� ������������ ���� � ���������
			temp = M_Mngm_Get_parameters_buffer()->menu_parameters.Motor[index].min_PWM_accel;	
			if(temp == MAX_PWM_DUTY_PERCENT)  		//���� ������������ ���, ������ ������ �� �����
			{
				accel_state	= MOTOR_IS_ACCELERATED;
				break;
			}
			else
			{
				//������� �� 4 �������, �� ���� ��� ����� ���� - 25 �����
				//��������� �������� ������������ ���� � ������ ������� ��� ���������� (�� 7 �� 25)
				cnt_duty = temp >> 2;			 	
				quantity_steps_accel = (100 - temp) >> 2; 	//��������� ���������� ����� ���������� ����
				
				//�������� �������� ������� ������ ������� ���������
				temp = M_Mngm_Get_parameters_buffer()->menu_parameters.Motor[index].time_accel; 
				
				//�������� ���������� ����� ���������� ����
				if(!quantity_steps_accel)			//��� ���������� ��������� ������� �� ����
					delta_t_accel = temp * 10;		//��������� � �������� ������� � ��
				else
					delta_t_accel = (temp * 10) / quantity_steps_accel;
				accel_state++; 	//������� � ������� 
				saved_cnt_duty = cnt_duty;
				M_Motor_Timer2_change(TIMER2_INIT_VALUE, ENABLE_TMR2_INTR);
			}
			break;
		case ACCELERATION:	//���������� �������� �������
			if(quantity_steps_accel  > 0U)
			{
				//������ ������� ���������� 
				if(time_M_Motor.time_step_accel++ < delta_t_accel)
					break;		
				else //���� �������� ������� ������� ���������� �������, ���������� ��������� ������� ���� 
				{
					time_M_Motor.time_step_accel = 0;
					quantity_steps_accel--;
					cnt_duty++;
				}
			}
			else //������� � ���������� ��������� �������� ���������
			{
				M_Motor_Timer2_change(TIMER2_OFF_VALUE, DISABLE_TMR2_INTR); //�� ��������� ������� ��������� ������ 2
				accel_state++;   //MOTOR_IS_ACCELERATED
			}
			break;
			
	}
}

/* ���������� � ���������� �� �/�2 ������������ ��� �������� �������� 500 �� */
void M_Motor_software_PWM_interrrupt(const rom IOport_motor* motor_pins)
{
	if(M_LI_Get_Limit_Switches()->ls_hopper_cover_state)
	{
		*motor_pins->portReg_sec_half_bridge |= 1 <<( motor_pins->pin_num_sec_half_bridge); 	//�������� ������ ����. ������� �� "�����" (� ��������� �����)
		if(M_Motor_PWM_period++ < PWM_PERIOD) //���� ������ ���� ��� �� ������
		{
			if(!saved_cnt_duty) //��������� ���, ���� ������������ ��������
				*motor_pins->portReg_prim_half_bridge &= ~(1 << (motor_pins->pin_num_prim_half_bridge));
			else				//�������� ��� � ���������������� �������� ������������
			{
				saved_cnt_duty--; 
				*motor_pins->portReg_prim_half_bridge |= 1 << (motor_pins->pin_num_prim_half_bridge);
			}
		}	
		else //������ ���� �������, ������������ �������� ������������ � �������� ������� ������� �������
		{
			saved_cnt_duty = cnt_duty;  
			M_Motor_PWM_period = 0;
		}
	}	
	else
	{
		*motor_pins->portReg_prim_half_bridge &= ~(1 << (motor_pins->pin_num_prim_half_bridge));	
		*motor_pins->portReg_sec_half_bridge &= ~(1 << (motor_pins->pin_num_sec_half_bridge));
	}

}
