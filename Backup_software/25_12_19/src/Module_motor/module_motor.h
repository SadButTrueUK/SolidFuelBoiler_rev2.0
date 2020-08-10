#ifndef _MODULE_MOTOR_H_
#define _MODULE_MOTOR_H_

#include "stdint.h"


#define	NO_MOVEMENT                             0U
#define	MOVEMENT_FORWARD                        1U
#define	MOVEMENT_BACKWARD                       2U
#define WAITING_MOVEMENT                        3U

#define SIZE_STRUCT_MOTORS											3U
#define CHECK_START_POSITION 										0U
#define STATE_MODULE_MOTOR_WAITING									1U
#define STATE_MODULE_MOTOR_FAILURE									2U
#define STATE_MODULE_MOTOR_WORKING									3U
#define STATE_MODULE_MOTOR_CLEAN_CHIMNEY							4U
#define STATE_MODULE_MOTOR_WAITING_FOR_MOVE_CLEAN_CHIMNEY			5U


//индексы массива состояний концевиков (по ложному срабатыванию)
#define INDEX_FALSE_STATE_LS_START_DISPENSER			0
#define INDEX_FALSE_STATE_LS_FINISH_DISPENSER			1
#define INDEX_FALSE_STATE_LS_START_SHATTER				2
#define INDEX_FALSE_STATE_LS_FINISH_SHATTER				3
#define INDEX_FALSE_STATE_LS_AFTER_FINISH_SHATTER		4


#define START_LS                1U 		 //тип концевика - начальный
#define FINISH_LS               2U		 //тип концевика - финишный
#define AFTER_FINISH_LS         3U		 //тип концевика - после финишного (только для заслонки в режиме чистки дымохода)
#define AGITATOR_LS             4U		 //тип концевика - датчик ворошителя 

#define TO_FORWARD_DISPENSER                    1U
#define TO_BACKWARD_DISPENSER                   2U
#define TIME_PAUSE_DISPENSER                    3U
#define TO_FORWARD_SHATTER                      4U
#define TO_BACKWARD_SHATTER                     5U
#define TIME_PAUSE_SHATTER                      6U

#define QUANTITY_FALSE_LS			7  //в версии 2.xx количество концевиков увеличилось на 2 штуки

typedef struct 
{
	volatile uint8_t* const portReg_prim_half_bridge; 	//ножка  ключа первого полумоста (как нижний так и верхний)
	const uint8_t           pin_num_prim_half_bridge; 	//номер пина верхнего ключа
	volatile uint8_t* const portReg_sec_half_bridge; 	//ножка  ключа второго полумоста (как нижний так и верхний)	
	const uint8_t           pin_num_sec_half_bridge;				//номер пина нижнего ключа
}IOport_motor;

typedef struct 
{
	BOOL is_failure;	//признак аварии 1 - есть, 0 - нет
	uint8_t type_ls;	//тип концевика (стартовый, финишный, датчик ворошителя, послефинишный)
}FailureMotor;

void 				M_Motor_software_PWM_interrrupt ( const rom IOport_motor* motor_pins );
const rom    		IOport_motor* M_Motor_get_ptr_to_motor_pins ( void );
void 				M_Motor_Run ( void );
FailureMotor* 		M_Motor_get_state_failure ( uint8_t index );
void 				M_Motor_set_work ( BOOL value );
void 				M_Motor_clear_struct_failure_motor(void);
void 				M_Motor_set_ctrl_shatter (uint8_t value);
uint8_t 			M_Motor_get_ctrl_shatter (void);
uint8_t 			M_Motor_get_direction(void);
void 				M_Motor_set_state (uint8_t value);
uint8_t				M_Motor_get_state(void);
BOOL* 				M_Motor_get_false_state_LS(void);
void 				M_Motor_clear_false_state_LS(const uint8_t size);
uint8_t 			M_Motor_get_prev_state(void);
void 				M_Motor_clear_parameters(void);
BOOL 				M_Motor_get_work(void);
void                M_Motor_ctor( void );


#endif