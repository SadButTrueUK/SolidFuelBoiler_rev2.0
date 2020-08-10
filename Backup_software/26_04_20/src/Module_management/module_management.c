#include "stdint.h"
#include "module_management.h"
#include "module_analog_inputs.h"
#include "module_indication.h"
#include "module_logic_inputs.h"
#include "module_motor.h"
#include "module_fan.h"
#include "menu.h"
#include <p18cxxx.h>
#include "main.h"
#include "eeprom.h"

#define TIMEOUT_TASK_MANAGEMENT	100


uint8_t M_Mngm_State = 0;
uint8_t M_Mngm_Code_Failure = 0;
uint8_t M_Mngm_Previous_State = 0;
uint8_t burning_state =  CALC_PARAMS_PERIOD;
uint16_t timeout_supply_fuel = 0;
uint16_t timeout_check_gas_sensor = 0;
uint8_t saved_temperature_water;
uint16_t timeout_change_temperature_water = 0;
ParametersBuffer M_Mngm_parameters_buffer;
BOOL M_Mngm_state_draught = IS_DRAUGHT;
uint16_t period_load_fuel;
uint16_t timeout;
uint8_t state_accel_fan = CALCULATE;
BOOL phase_cycle = PAUSE_IN_CYCLE;
uint8_t fan_param_offset = INDEX_ROTATIONAL_SPEED_FAN_MIN_INCREASE;
uint8_t* pFanLevel = 0;
uint8_t level;

uint8_t M_Mngm_get_fanParamOffset(void)
{
	return fan_param_offset;
} 

uint8_t* M_Mngm_get_pFanLevel(void)
{
	return pFanLevel;
}


BOOL M_Mngm_get_phase_cycle(void)
{
	return phase_cycle;
}


/*
Проверка изменения температуры воды по истечении заданного таймаута  TIMEOUT_CHECK_CHANGE_TEMPERATURE_WATER (пока 10 минут)
если температура уменьшилась - переход в состояние ожидания. Далее пользователь либо подкидывает топливо в бункер, либо уменьшает 
в меню период загрузок топлива
Возвращает 
1 - если температура уменьшилась
0 - если не уменьшилась и ли увеличилась
*/
BOOL M_Mngm_check_change_temperature_water(void)
{
	if(burning_state == INCREASE_TEMPERATURE || burning_state == MAINTENANCE_TEMPERATURE_INCR)
	{
		if(M_Motor_get_state() == STATE_MODULE_MOTOR_WAITING)	//при работе алгоритма засыпки timeout_change_temperature_water считается после окончания засыпки	
		{
			if(timeout_change_temperature_water++ >= TIMEOUT_CHECK_CHANGE_TEMPERATURE_WATER )
			{
				timeout_change_temperature_water = 0;	
				if(M_AI_Get_ADC_Data(CHN_T_WATER)->param < saved_temperature_water)  //если температура уменьшилась
				{
					return TEMPERATURE_DECREASED;
				}
				else
				{
					 //если температура выросла или не изменилась, перезаписать её новое значение
					saved_temperature_water = M_AI_Get_ADC_Data(CHN_T_WATER)->param; 
					return TEMPERATURE_INCREASED_OR_EQUAL;
				}
			}
			else
			{
				return TEMPERATURE_INCREASED_OR_EQUAL;
			}
		}
		else
		{
			return TEMPERATURE_INCREASED_OR_EQUAL;	
		}
	}
	else
	{
		timeout_change_temperature_water = 0;
		return TEMPERATURE_INCREASED_OR_EQUAL;
	}
}

void M_Mngm_set_saved_temperature_water(uint8_t value)
{
	saved_temperature_water = value;	
}


void M_Mngm_clear_timeouts(void)
{
	timeout_supply_fuel = timeout_check_gas_sensor = /*burning_state = */timeout_change_temperature_water = timeout = 0;
}

uint8_t M_Mngm_get_burning_state(void)
{
	return burning_state;
}

void M_Mngm_set_burning_state(uint8_t value)
{
	burning_state = value;
}


ParametersBuffer* M_Mngm_Get_parameters_buffer(void)
{
	return &M_Mngm_parameters_buffer;
}

void M_Mngm_Set_state(uint8_t value)
{
	M_Mngm_State = value;
}

uint8_t M_Mngm_Get_previous_state(void)
{
	return M_Mngm_Previous_State;
}

uint8_t M_Mngm_Get_state(void)
{
	return M_Mngm_State;
}

uint8_t M_Mngm_Get_Code_Failure(void)
{
	return M_Mngm_Code_Failure;
}

void M_Mngm_Set_Code_Failure(uint8_t value)
{
	M_Mngm_Code_Failure = value;	
}

void M_Mngm_Set_state_draught(BOOL value)
{
	M_Mngm_state_draught = value;
}


/* 
Функция проверки аварии тяги (по критерию: через 10 минут после начала процесса горения 
температура исходящего газа менее 60 градусов) 
*/
void  M_Mngm_check_draught_failure(void)
{
	 if(M_Motor_get_state() == STATE_MODULE_MOTOR_WAITING)
	{
		if(timeout_check_gas_sensor++ == TIMEOUT_CHECK_FAILURE_DRAUGHT)
		{
			timeout_check_gas_sensor = 0;	
			if(M_AI_Get_ADC_Data(CHN_T_GAS)->param < LOW_THRESHOLD_IN_BURNING_TEMPER_GAS)
			{
				M_Mngm_state_draught = NO_DRAUGHT;
				M_fan_set_ctrl_fan(OFF);
			}
		}
	}
}


/*
Функция проверки аварии
Возвращает код аварии (0 - её отсутствие)
*/

uint8_t M_Mngm_Check_Failure(void)
{
	if(M_Mngm_parameters_buffer.menu_parameters.code_failure == NO_FAILURE)
	{
		
		if(M_Mngm_state_draught == NO_DRAUGHT)		//авария тяги в дымоход
		{	
			return CODE_FAILURE_DRAUGHT; 	
		}
		if((M_AI_Get_ADC_Data(CHN_T_GAS)->param) == BREAK_SENSOR_VALUE) 				//обрыв датчика температуры газа
		{
			return CODE_FAILURE_BREAK_T_GAS_SENSOR;		
		}	
		 if((M_AI_Get_ADC_Data(CHN_T_GAS)->param) == SHORT_CIRCUIT_SENSOR_VALUE) 	//КЗ датчика температуры газа
		{
			return  CODE_FAILURE_SHORT_CIRCUIT_T_GAS_SENSOR;	
		}
		if((M_AI_Get_ADC_Data(CHN_T_WATER)->param) == BREAK_SENSOR_VALUE) 			//обрыв датчика температуры воды
		{
			return CODE_FAILURE_BREAK_T_WATER_SENSOR;		
		}	
		if((M_AI_Get_ADC_Data(CHN_T_WATER)->param) == SHORT_CIRCUIT_SENSOR_VALUE) 	//КЗ датчика температуры воды
		{
			return CODE_FAILURE_SHORT_CIRCUIT_T_WATER_SENSOR;
		} 
		if(M_Motor_get_state_failure(INDEX_OF_AGITATOR)->is_failure)									//авария датчика ворошителя
		{
			if(M_Motor_get_state_failure(INDEX_OF_AGITATOR)->type_ls == AGITATOR_LS)	
				return CODE_FAILURE_MOTOR_LS_AGITATOR;
		}
		if(M_Motor_get_state_failure(INDEX_OF_DISPENSER)->is_failure)
		{
			if(M_Motor_get_state_failure(INDEX_OF_DISPENSER)->type_ls == START_LS)				//авария стартового концевика дозатора	
				return CODE_FAILURE_MOTOR_LS_DISPENSER_START;
			if( M_Motor_get_state_failure( INDEX_OF_DISPENSER )->type_ls == FINISH_LS )				//авария финишного концевика дозатора
				return CODE_FAILURE_MOTOR_LS_DISPENSER_FINISH;	
		}
		if(M_Motor_get_state_failure( INDEX_OF_SHATTER )->is_failure)
		{
			if( M_Motor_get_state_failure(INDEX_OF_SHATTER)->type_ls == START_LS )				//авария стартового концевика заслонки
				return CODE_FAILURE_MOTOR_LS_SHATTER_START;
			 if( M_Motor_get_state_failure(INDEX_OF_SHATTER)->type_ls == FINISH_LS )			//авария финишного концевика заслонки		
				return CODE_FAILURE_MOTOR_LS_SHATTER_FINISH;	
			 if( M_Motor_get_state_failure(INDEX_OF_SHATTER)->type_ls == AFTER_FINISH_LS ) 	//авария "после"финишного концевика заслонки
				return CODE_FAILURE_MOTOR_LS_AFTER_SHATTER_FINISH;	
		}
		if (*(M_Motor_get_false_state_LS() + INDEX_FALSE_STATE_LS_START_DISPENSER))		//авария "Ложное состояние стартового концевика дозатора"
			return CODE_FAILURE_MOTOR_LS_DISPENSER_START_FALSE_ON;
		if (*(M_Motor_get_false_state_LS() + INDEX_FALSE_STATE_LS_FINISH_DISPENSER))		//авария "Ложное состояние финишного концевика дозатора"
			return CODE_FAILURE_MOTOR_LS_DISPENSER_FINISH_FALSE_ON;	
		if (*(M_Motor_get_false_state_LS() + INDEX_FALSE_STATE_LS_START_SHATTER))			//авария "Ложное состояние стартового концевика заслонки"	
			return  CODE_FAILURE_MOTOR_LS_SHATTER_START_FALSE_ON;
		if (*(M_Motor_get_false_state_LS() +  INDEX_FALSE_STATE_LS_FINISH_SHATTER))			//авария "Ложное состояние финишного концевика заслонки"	
			return CODE_FAILURE_MOTOR_LS_SHATTER_FINISH_FALSE_ON;
		if (*(M_Motor_get_false_state_LS() + INDEX_FALSE_STATE_LS_AFTER_FINISH_SHATTER))	//авария "Ложное состояние послефинишного концевика заслонки"	
			return CODE_FAILURE_MOTOR_LS_AFTER_SHATTER_FINISH_FALSE_ON;
		if (M_LI_Get_Limit_Switches()->overheat)
            return CODE_FAILURE_OVERHEAT;           //авария датчика перегрева
        #ifndef NO_220V_CONTROL  //если на плату заведено 220В
			if(!M_fan_get_is_220V())																		//авария "Отсутствие 220В" (по синхроимпульсам)
				return CODE_FAILURE_NO_220V;
		#endif	
		M_Menu_write_changed_param(INDEX_OF_CODE_FAILURE, DataEERead (INDEX_OF_CODE_FAILURE), NO_FAILURE);
			return NO_FAILURE; 
	}
	else
	{
		return M_Mngm_parameters_buffer.menu_parameters.code_failure;
	}
}

/* Автомат состояний модуля управленяи */
void M_Mngm_Run (void)
{
	if(M_Ind_Get_state() == STATE_IND_INIT)
		return;
			
	if(M_Mngm_State != STATE_PAUSE)  M_Mngm_Code_Failure = M_Mngm_Check_Failure();  //проверка аварий везде кроме режима "Пауза"

		switch(M_Mngm_State)
		{
			case STATE_WAITING :				//ожидание
				M_Mngm_Previous_State = STATE_WAITING;
				M_Mngm_waiting();					
			break;
			case STATE_FUEL_SUPPLY :			//загрузка топлива
				M_Mngm_fuel_supply();
			break;
			case STATE_BURNING :				//горение и поддержание температуры воды
				M_Mngm_Previous_State = STATE_BURNING;
				M_Mngm_burning();
			break;
			case STATE_PAUSE :				//пауза
				M_Mngm_pause();
			break;
			case STATE_CLEAN_CHIMNEY :		//очистка дымохода
				M_Mngm_Previous_State = STATE_CLEAN_CHIMNEY;
				M_Mngm_clean_chimney();
			break;
			case STATE_FAILURE :				//авария
				M_Mngm_failure();
			break;
		}
}

/*
Проверка необходимости перехода в режим "Пауза"
Если концевик отпущен - перейти в "Паузу"
*/
void M_Mngm_need_to_pause(const uint8_t prev_state)
{
	if(!(M_LI_Get_Limit_Switches()->ls_hopper_cover_state)) //если открыта дверь бункера, перейти в состояние паузы
	{
		M_Ind_Set_Previous_State(M_Ind_Get_state());
		M_Ind_Set_state(STATE_VIEW_PAUSE);	
		M_Mngm_Previous_State = prev_state;
		M_Mngm_State = STATE_PAUSE; 
	}	
	 
}

void M_Mngm_waiting(void)
{
	pFanLevel = &M_Mngm_parameters_buffer.menu_parameters.rotational_speed_fan;
	fan_param_offset = INDEX_ROTATIONAL_SPEED_FAN_MIN_INCREASE;
	M_Mngm_need_to_pause(STATE_WAITING);	//Проверка необходимости перехода в режим "Пауза"
	if (M_Mngm_Code_Failure  != NO_FAILURE)
	{	
		M_Mngm_State = STATE_FAILURE;
		DataEEWrite (M_Mngm_Code_Failure, INDEX_OF_CODE_FAILURE );
	}
	else
	{
		//если нажата кнопка Start\Menu\Stop - переход в состояние Burning
	}
}


void M_Mngm_fuel_supply(void)
{
	M_Mngm_need_to_pause(STATE_FUEL_SUPPLY);	//Проверка необходимости перехода в режим "Пауза"
	M_fan_set_ctrl_fan(OFF);
	if (M_Mngm_Code_Failure  != NO_FAILURE)
	{
		M_Mngm_Previous_State = STATE_FUEL_SUPPLY;
		M_Mngm_State = STATE_FAILURE;
		DataEEWrite (M_Mngm_Code_Failure, INDEX_OF_CODE_FAILURE );
		//M_fan_set_ctrl_fan(OFF);
	}
	else
	{
		if(M_Motor_get_state() == STATE_MODULE_MOTOR_WAITING && (M_Mngm_Previous_State == STATE_BURNING || 
			(M_Mngm_Previous_State == STATE_FUEL_SUPPLY && !Menu_get_manual_supply()))) //если отсутствует признак работы двигателя
		{
			M_Mngm_State = STATE_BURNING;	
			M_Ind_Set_state(STATE_VIEW_TEMPERATURE_REAL);
		}
	}
}


/* Реализация алгоритма горения с поддержианием температуры */
void M_Mngm_burning(void)
{
	uint16_t temp;
	
	M_Mngm_need_to_pause(STATE_BURNING);	//Проверка необходимости перехода в режим "Пауза"
	if (M_Mngm_Code_Failure  != NO_FAILURE)
	{
		M_Mngm_clear_timeouts();
		M_Mngm_State = STATE_FAILURE;
		DataEEWrite (M_Mngm_Code_Failure, INDEX_OF_CODE_FAILURE );
		M_fan_set_ctrl_fan(OFF);
	}
	else
	{
		// проверка увеличения температуры воды по истечении заданного таймаута
		if(M_Mngm_check_change_temperature_water())
		{
			M_fan_set_ctrl_fan(OFF);			//выключить алгоритм работы вентилятора
			M_Mngm_State = STATE_WAITING;	//перейти в режим ожидания при невозможности поддержания температуры
			burning_state =  CALC_PARAMS_PERIOD;
			M_Mngm_clear_timeouts();
		}	
		else
		{
			#ifdef NO_CONTROL_DRAUGHT
				M_Mngm_state_draught = IS_DRAUGHT;
			#else
				M_Mngm_check_draught_failure(); 	//проверка тяги в дымоход, если отсутствует - переход в состояние аварии
			#endif	
			if(M_Mngm_state_draught == IS_DRAUGHT)
			{	
				switch(burning_state)
				{
					case CALC_PARAMS_PERIOD:
						period_load_fuel = (uint16_t)M_Mngm_parameters_buffer.menu_parameters.period_load_fuel_in_heat
						[M_Mngm_parameters_buffer.menu_parameters.fuel_type] *1000; //вычисление периода загрузок топлива в горении
						burning_state = START_BURNING; 
					break;  
					
					case START_BURNING: 	//начальный этап горения (разгон вентилятора)
						if(M_AI_Get_ADC_Data(CHN_T_WATER)->param < M_Mngm_parameters_buffer.menu_parameters.temper_setup - 
							M_Mngm_parameters_buffer.menu_parameters.Fan.delta_temper_for_econom_mode[M_Mngm_parameters_buffer.menu_parameters.fuel_type])
						{
							if(M_Mngm_accel_fan()) //если вентилятор разогнан
							{
								burning_state = INCREASE_TEMPERATURE;
								saved_temperature_water = M_AI_Get_ADC_Data(CHN_T_WATER)->param;
								M_Mngm_clear_accel_fan();
							}
						}
						else
						{
							burning_state = ECONOM_MODE;	
							M_Mngm_clear_accel_fan();
							pFanLevel = &M_Mngm_parameters_buffer.menu_parameters.Fan.level_fan_in_econom_mode[M_Mngm_parameters_buffer.menu_parameters.fuel_type];
							fan_param_offset = INDEX_ROTATIONAL_SPEED_FAN_MIN_ECONOM + M_Mngm_parameters_buffer.menu_parameters.fuel_type * 2;
							M_fan_set_level_fan(*pFanLevel);
							M_fan_set_ctrl_fan(ON);			//включить алгоритм работы вентилятора
						}
					break;
					
					case INCREASE_TEMPERATURE:  //работа на максимальных оборотах вентилятора до перехода в эконом режим, периодическая загрузка топлива
						if(M_AI_Get_ADC_Data(CHN_T_WATER)->param < M_Mngm_parameters_buffer.menu_parameters.temper_setup - 
							M_Mngm_parameters_buffer.menu_parameters.Fan.delta_temper_for_econom_mode[M_Mngm_parameters_buffer.menu_parameters.fuel_type])
						{
							M_fan_set_ctrl_fan(ON);			//включить алгоритм работы вентилятора
							if(timeout_supply_fuel++ >= period_load_fuel)			
							{
								timeout_supply_fuel = 0;
								M_Mngm_State = STATE_FUEL_SUPPLY;
								M_Motor_set_work(ON); 		//включить алгоритм засыпки топлива
							}
						}
						else
						{
							burning_state = ECONOM_MODE;
							M_Ind_Set_state(STATE_VIEW_TEMPERATURE_REAL);
							timeout_supply_fuel = 0;
							pFanLevel = &M_Mngm_parameters_buffer.menu_parameters.Fan.level_fan_in_econom_mode[M_Mngm_parameters_buffer.menu_parameters.fuel_type]; 
							fan_param_offset = INDEX_ROTATIONAL_SPEED_FAN_MIN_ECONOM + M_Mngm_parameters_buffer.menu_parameters.fuel_type * 2;
							M_fan_set_level_fan(*pFanLevel);
						}
					break;
					case ECONOM_MODE:
						if(M_AI_Get_ADC_Data(CHN_T_WATER)->param >= M_Mngm_parameters_buffer.menu_parameters.temper_setup)
						{
							burning_state = MAINTENANCE_TEMPERATURE_CYCLE;	
							pFanLevel = &M_Mngm_parameters_buffer.menu_parameters.Fan.level_fan_in_smoldering[M_Mngm_parameters_buffer.menu_parameters.fuel_type];
							M_fan_set_ctrl_fan(OFF);
						}
						else if(M_AI_Get_ADC_Data(CHN_T_WATER)->param < M_Mngm_parameters_buffer.menu_parameters.temper_setup - 
							M_Mngm_parameters_buffer.menu_parameters.Fan.delta_temper_for_econom_mode[M_Mngm_parameters_buffer.menu_parameters.fuel_type])
						{
							burning_state = INCREASE_TEMPERATURE;
							timeout_supply_fuel = period_load_fuel;
							pFanLevel = &M_Mngm_parameters_buffer.menu_parameters.rotational_speed_fan;
							fan_param_offset = INDEX_ROTATIONAL_SPEED_FAN_MIN_INCREASE;
							M_fan_set_level_fan(*pFanLevel);
						}	
						
					break;
					case MAINTENANCE_TEMPERATURE_CYCLE:		//продувка топлива
						if(M_Mngm_cyclic_mode())
						{	
							burning_state = MAINTENANCE_TEMPERATURE_INCR;
							saved_temperature_water = M_AI_Get_ADC_Data(CHN_T_WATER)->param;
						}
					break;
					
					case MAINTENANCE_TEMPERATURE_INCR:  	//добор температуры после продувки
						if(M_AI_Get_ADC_Data(CHN_T_WATER)->param >= M_Mngm_parameters_buffer.menu_parameters.temper_setup)
						{
							burning_state = MAINTENANCE_TEMPERATURE_CYCLE;
							timeout_supply_fuel = 0;
							M_fan_set_ctrl_fan(OFF);
						}
						else
						{
							M_fan_set_ctrl_fan(ON);			//включить алгоритм работы вентилятора
							pFanLevel = &M_Mngm_parameters_buffer.menu_parameters.Fan.level_fan_in_smoldering[M_Mngm_parameters_buffer.menu_parameters.fuel_type];
							M_fan_set_level_fan(*pFanLevel);
							if(timeout_supply_fuel++ >= period_load_fuel)			
							{
								timeout_supply_fuel = 0;
								M_Mngm_State = STATE_FUEL_SUPPLY;
								M_Motor_set_work(ON); 		//включить алгоритм засыпки топлива
							}
						}
					break;
				}
			}
			else
			{
				
			}
		}
	}
}

/* Режим "Пауза" */
void M_Mngm_pause(void)
{
	if(M_LI_Get_Limit_Switches()->ls_hopper_cover_state) //если закрыта дверь бункера, выйти из состояния паузы
	{
		M_Mngm_State = M_Mngm_Previous_State;
		M_Ind_Set_state(M_Ind_Get_Previous_State());	
	}		
	if (M_Mngm_Code_Failure  != NO_FAILURE)
	{
		M_Mngm_State = STATE_FAILURE;
		DataEEWrite (M_Mngm_Code_Failure, INDEX_OF_CODE_FAILURE );
	}
	else
	{
	
	}
}

/*Режим "Очистка дымохода" */
void M_Mngm_clean_chimney(void)
{
	M_Mngm_need_to_pause(STATE_CLEAN_CHIMNEY);	//Проверка необходимости перехода в режим "Пауза"
	if (M_Mngm_Code_Failure  != NO_FAILURE)
	{
		M_Mngm_State = STATE_FAILURE;
		DataEEWrite (M_Mngm_Code_Failure, INDEX_OF_CODE_FAILURE );
	}
	else
	{
	
	}
}


void M_Mngm_failure(void)
{
	if (M_Mngm_Code_Failure  == NO_FAILURE)
	{
		M_Mngm_State = M_Mngm_Previous_State;
	}
	else
	{
		
	}
}

/*
Cброс переменных разгона вентилятора
*/
void M_Mngm_clear_accel_fan(void)
{
	state_accel_fan = CALCULATE;
	timeout = 0;
}

/*
Cброс переменных циклического режима
*/
void M_Mngm_clear_cyclic_mode(void)
{
	phase_cycle = PAUSE_IN_CYCLE;;
	timeout = 0;
}


/* 
Функция разгона вентилятора от миимального до максимального уровня при начальном разгорании котла
*/
BOOL M_Mngm_accel_fan(void)
{
	uint8_t  num_steps;
	static uint16_t time_step; 
	//static uint8_t level;
		
	switch (state_accel_fan)
	{
		case CALCULATE:		//состояние вычисления параметров
			num_steps = (M_Mngm_parameters_buffer.menu_parameters.Fan.max_turn_percent - 
						M_Mngm_parameters_buffer.menu_parameters.Fan.min_turn_percent) + 1; 	//получаем количество шагов разгона
			//получаем шаг времени для одного уровня вращения вентилятора
			time_step = (uint16_t)M_Mngm_parameters_buffer.menu_parameters.Fan.time_accel_fan
						[M_Mngm_parameters_buffer.menu_parameters.fuel_type] * 100 / num_steps; 	
			pFanLevel = &M_Mngm_parameters_buffer.menu_parameters.Fan.min_turn_percent;
			level = *pFanLevel;
			M_fan_set_level_fan(level);				
			M_fan_set_ctrl_fan(ON);
			state_accel_fan++;	//переход к следующему состоянию автомата
			break;
		case ROTATE:  //состояние вращения при разгоне
			if(timeout++ == time_step)
			{
				timeout = 0;	
				if(level++ == M_Mngm_parameters_buffer.menu_parameters.Fan.max_turn_percent)
				{	
					state_accel_fan = CALCULATE;
					pFanLevel = &M_Mngm_parameters_buffer.menu_parameters.rotational_speed_fan;
					M_fan_set_level_fan(*pFanLevel);	
					fan_param_offset = INDEX_ROTATIONAL_SPEED_FAN_MIN_INCREASE;
					return  FAN_IS_ACCEL; 
				}
				else
				{
					pFanLevel = &level;
					M_fan_set_level_fan(level);	
				}
			}	
			break;
	}
	return FAN_NOT_ACCEL;
}



/*
Функция работы вентилятора в циклическом режиме работа-пауза в режиме тления топлива алгоритма горения
Возвращает 1 - если температура упала и нужно возвращаться в режим загрузки топлива для увеличения температуры
0 - продолжаем оставаться в этом режиме
*/
BOOL M_Mngm_cyclic_mode(void)
{
	if(M_AI_Get_ADC_Data(CHN_T_WATER)->param <= M_Mngm_parameters_buffer.menu_parameters.temper_setup - 
	M_Mngm_parameters_buffer.menu_parameters.Fan.delta_from_cycle_to_heat[M_Mngm_parameters_buffer.menu_parameters.fuel_type])
	{
		phase_cycle = PAUSE_IN_CYCLE;
		timeout_supply_fuel = period_load_fuel; //переход в другой режим начнётся с подкидывания топлива
		timeout = 0;
		return TRUE; //температура упала до значения не более установленной минус 2oC 
	}
	else
	{
		switch (phase_cycle)
		{
			case PAUSE_IN_CYCLE: //отсчёт времени паузы вентилятора в подрежиме тления топлива	
				if( timeout++ == ( uint16_t ) M_Mngm_parameters_buffer.menu_parameters.Fan.time_pause_in_cycle
										[ M_Mngm_parameters_buffer.menu_parameters.fuel_type ]*1000)
				{
					timeout = 0;
					phase_cycle = WORK_IN_CYCLE;
					M_fan_set_ctrl_fan(ON);
					pFanLevel = &M_Mngm_parameters_buffer.menu_parameters.Fan.level_fan_in_smoldering
										[M_Mngm_parameters_buffer.menu_parameters.fuel_type];
					M_fan_set_level_fan(*pFanLevel);
					fan_param_offset = INDEX_ROTATIONAL_SPEED_FAN_MIN_SMOLDERING + M_Mngm_parameters_buffer.menu_parameters.fuel_type * 2;
				}
			break;
			case WORK_IN_CYCLE:	//отсчёт времени работы вентилятора в подрежиме тления топлива
				if( timeout++ == ( uint16_t ) M_Mngm_parameters_buffer.menu_parameters.Fan.time_work_in_cycle
										[ M_Mngm_parameters_buffer.menu_parameters.fuel_type ]*10 )
				{
					timeout = 0;
					phase_cycle = PAUSE_IN_CYCLE;
					M_fan_set_ctrl_fan(OFF);
				}	
			break;
		}
		return FALSE;
	}
}
