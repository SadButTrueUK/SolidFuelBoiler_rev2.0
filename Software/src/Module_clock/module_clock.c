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
������� ����� ���������� �������. ���������� ��� � 1 � � ���������� �/�3.
����� ������������ � 0 ��� ���������� 1 ����
*/
void M_Clock_Run(uint16_t* time_in, const uint16_t limit_overflow)
{
	(*time_in)++;
	
	if(*time_in >= limit_overflow)
		*time_in = 0;
}


/*
������� ������� ���������� ���������

����������:
0 - ������ ���������� ��������� �� �������
1 - ������ ���������� ��������� �������

������� ���������:
BOOL* time_init_start - ��������� �� ���� ������� �������
uint16_t* time_init - ��������� �� ����������, ������� �� ����� ������� ������� ����������� �������� ���������� �������
const uint16_t time_value - ��������� �������� �������, �� �������� ���� �������
uint16_t system_time - ������������� ��������� �����. ����� ������������� �� ������ ��������� ����� 
							(��� ��������������,��� � ���������) 
const uint16_t limit_overflow - �������� ������ ������������ (��������, ����� ������� ��������� ����� ������������ � ���� - 1000�� ��� 3600�)
*/

BOOL M_Clock_Time_Event(BOOL* time_init_start, uint16_t* time_init,  uint16_t system_time, const uint16_t time_value, 
							const uint16_t limit_overflow)
{
	uint16_t temp; 
	
	if (*time_init_start)
	{ 
		temp = system_time;			//�������� ������� ��������� ����� �������
	
		if (temp >= *time_init) 
			temp = temp - *time_init;	//��������� ������� ����� ��������������� �������� � �������
		else 							//�� ����� ����� ��������� ������������ �������
			temp = temp + limit_overflow - *time_init;	//������������ ��������� ������������ �������
			
		if (temp >= time_value)
		{
			*time_init_start = OFF;
			return TIME_FINISHED;
		}	//������ ���������� ��������� �������
		else 
			return TIME_IN_PROCESS; //������ ���������� ��������� �� �������
	}
	else
	{
		if (!time_value)  	//���� � ������� �������� �����, ������ ����, ������ ������ ������� �� �����
			return TIME_FINISHED;
		*time_init = system_time;	 //���������� ��������� ����� �������
		*time_init_start = ON; 		 //���������� ���� ������ ������� �������
		return TIME_IN_PROCESS;        //������ ���������� ��������� �� �������
	}
}
