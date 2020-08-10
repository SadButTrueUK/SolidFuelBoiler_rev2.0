#ifndef _MODULE_CLOCK_H_
#define _MODULE_CLOCK_H_

#include "System\stdint.h"

#define T3_16BIT_RW     		0b11111111 // 16-bit mode
#define T3_PS_1_8       		0b11111111 // 1:8 prescale value
#define T3_SYNC_EXT_OFF		0b11111111 // Do not synchronize external clock input
#define T3_SOURCE_INT   		0b11111101 // Internal clock source
#define HOUR_OVERFLOW		3600U 	   // количество с в 1 часе
#define SECOND_OVERFLOW 	1000U	   // количество  мс в 1 секунде (системный тик)
#define TIME_FINISHED   		1
#define TIME_IN_PROCESS		0


void OpenTimer3(uint8_t config);
//uint16_t* M_Clock_Get_Addr_System_Time_1s(void);
//uint16_t* M_Clock_Get_Addr_System_Time_1ms(void);
//void M_Clock_Run(uint16_t* time_in, const uint16_t limit_overflow);
//BOOL M_Clock_Time_Event(BOOL* time_init_start, uint16_t* time_init,  uint16_t system_time, const uint16_t time_value, 
//							const uint16_t limit_overflow);
//uint16_t M_Clock_Get_System_Time_1s(void);
//uint16_t M_Clock_Get_System_Time_1ms(void);
//
//
#endif