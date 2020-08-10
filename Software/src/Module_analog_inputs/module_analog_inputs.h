#ifndef _MODULE_ANALOG_INPUTS_H_
#define _MODULE_ANALOG_INPUTS_H_

#include "stdint.h"

#define BREAK_SENSOR_VALUE                      250U
#define SHORT_CIRCUIT_SENSOR_VALUE              251U
#define SHORT_CIRCUIT_SENSOR_THRESHOLD          10U
#define BREAK_SENSOR_THRESHOLD                  980U
#define TABLE_SORTED_UP                         0  		//для таблицы отсортированной по возрастанию
#define TABLE_SORTED_DOWN                       1		//для таблицы отсортированной по убыванию
#define CHN_T_GAS                               0U	      		
#define CHN_T_WATER                             1U		
#define CHN_I_SUPPLY_12V                        2U
#define MAX_TEMPER_GAS_SENSOR_FOR_CLEAN_CHIMNEY	5U  //50 градусов

//Объявление структур
typedef struct 
{
	uint16_t sum_discr;  	//сумма дискрет АЦП измеряемого канала
	uint8_t  quantity;  	//количество измерений
	uint16_t data_value; 	//измеренные и усреднённые данные
	uint8_t  param;         //значение температуры или тока
}ADC_Data;


uint16_t 	   M_AI_ReadADC(void);
uint8_t 	   M_AI_Search(uint16_t value, const rom uint16_t* table, const uint8_t length, uint8_t sort_direction);
void           M_AI_ctor( void );
void 		   M_AI_SetChanADC(uint8_t channel);
void 		   M_AI_ConvertADC(void);
void 		   M_AI_Run (void);
void 		   M_AI_Processing_ADC (uint8_t index);
ADC_Data*      M_AI_Get_ADC_Data(uint8_t index);

#endif