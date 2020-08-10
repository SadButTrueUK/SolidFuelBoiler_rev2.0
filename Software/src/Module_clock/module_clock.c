#include <p18cxxx.h>
#include "Module_clock\module_clock.h"
#include "System\stdint.h"

uint16_t M_Clock_System_Time_1s = 0;
uint16_t M_Clock_System_Time_1ms = 0;

void OpenTimer3(uint8_t config)
{
 	T3CON = (0x36 & config);
    	TMR3H = 0;         				 //Clear timer3-related registers
	TMR3L = 0;
	PIR2bits.TMR3IF = OFF;
	PIE2bits.TMR3IE = ON;
 	T3CONbits.RD16 = ON;
	T3CONbits.TMR3ON = ON;   	// Turn on Timer3
}


uint16_t* M_Clock_Get_Addr_System_Time_1s(void)
{
	return &M_Clock_System_Time_1s;
} 

uint16_t* M_Clock_Get_Addr_System_Time_1ms(void)
{
	return &M_Clock_System_Time_1ms;
}

uint16_t M_Clock_Get_System_Time_1s(void)
{
	return M_Clock_System_Time_1s;
} 

uint16_t M_Clock_Get_System_Time_1ms(void)
{
	return M_Clock_System_Time_1ms;
}

/*
Функция счёта системного времени. Вызывается раз в 1 с в прерывании т/с3.
Время сбрасывается в 0 при достижении 1 часа
*/
void M_Clock_Run(uint16_t* time_in, const uint16_t limit_overflow)
{
	(*time_in)++;
	
	if(*time_in >= limit_overflow)
		*time_in = 0;
}


/*
Функция отсчёта временного интервала

Возвращает:
0 - отсчёт временного интервала не окончен
1 - отсчёт временного интервала окончен

Входные аргументы:
BOOL* time_init_start - указатель на флаг захвата времени
uint16_t* time_init - указатель на переменную, которая по флагу захвата времени присваивает значение системного времени
const uint16_t time_value - константа значения времени, до которого надо считать
uint16_t system_time - захватываемое системное время. Может захватываться из разных временных сеток 
							(как миллисекундной,так и секундной) 
const uint16_t limit_overflow - значение порога переполнения (величина, после которой системное время сбрасывается в ноль - 1000мс или 3600с)
*/

BOOL M_Clock_Time_Event(BOOL* time_init_start, uint16_t* time_init,  uint16_t system_time, const uint16_t time_value, 
							const uint16_t limit_overflow)
{
	uint16_t temp; 
	
	if (*time_init_start)
	{ 
		temp = system_time;			//получить текущее системное время системы
	
		if (temp >= *time_init) 
			temp = temp - *time_init;	//получение разницы между зафиксированным временем и текущим
		else 							//за время входа произошло переполнение таймера
			temp = temp + limit_overflow - *time_init;	//компенсируем возможное переполнение таймера
			
		if (temp >= time_value)
		{
			*time_init_start = OFF;
			return TIME_FINISHED;
		}	//отсчёт временного интервала окончен
		else 
			return TIME_IN_PROCESS; //отсчёт временного интервала не окончен
	}
	else
	{
		if (!time_value)  	//если в функцию передано время, равное нулю, значит ничего считать не нужно
			return TIME_FINISHED;
		*time_init = system_time;	 //записываем начальное время отсчета
		*time_init_start = ON; 		 //установить флаг начала отсчета времени
		return TIME_IN_PROCESS;        //отсчёт временного интервала не окончен
	}
}
