
#include "interrupts.h"
#include <p18cxxx.h>
#include "osa.h"
#include "module_motor.h"
#include "logicAnalyzer.h"
#include "main.h"

#ifdef ENABLE_INT2
    #define TRIS_INTR_NULL_SIN  TRISBbits.TRISB2
#endif

#pragma code InterruptVectorHigh = 0x08

static uint16_t cnt_zero_crossing = 0;
static BOOL is_zero_cross = FALSE;  				 //������� �������� ����� ���� �������� ����������
static BOOL  is_impulse_agitator_sensor = FALSE; 	 //������� ������� �������� ������� ����������

void InterruptHandlerHigh (void);
void InterruptVectorHigh (void);

void InterruptVectorHigh (void)
{
    _asm
        goto InterruptHandlerHigh //jump to interrupt routine
    _endasm
}


#pragma code
#pragma interrupt InterruptHandlerHigh

/*
���������� �/�0 ��� ������������ ���������� "����" 1��
���������� �/�3 50�� ��� ������������ ��������� ����� � ����� 1� 
���������� �� ������� ������ INT2 (������� ����� ���� �������� ���������� 220�)
���������� �/�2 215 ��� ��� ������������ ������������ ���� ������� ��������� 
*/
void InterruptHandlerHigh (void)
{
 	OS_EnterInt();
 	if (INTCONbits.TMR0IF)      //������ ���������� ���� 1 ��
    {                           //check for TMR0 overflow
    	//DEBUG_PIN_1_TOGGLE;
        TMR0L=0x48;
    	INTCONbits.TMR0IF = 0;  //clear interrupt flag
       	OS_Timer();
	}
    if(INTCON3bits.INT2IF && INTCON3bits.INT2IE) //���������� �� �������� ����� ���� �������� ���������� ������ 20 ��
	{
		INTCON3bits.INT2IF = 0;
		is_zero_cross = TRUE;
		cnt_zero_crossing++;
	}
	if(INTCON3bits.INT1IF && INTCON3bits.INT1IE) //���������� �� ������� ������ �� RB1 ��� ������ ������� ����������
	{
		is_impulse_agitator_sensor = TRUE;
		INTCON3bits.INT1IF = 0;
	}
	if(PIR1bits.TMR2IF && PIE1bits.TMR2IE) //������ ���������� 205 ��� (��� ������������ ���� ������� ���������)
	{
		PIR1bits.TMR2IF = 0;
		M_Motor_software_PWM_interrrupt(M_Motor_get_ptr_to_motor_pins());
	}	
	OS_LeaveInt();
}

void Intr_ctor( void )
{
    INTCON = 0x20;                 //disable global and enable TMR0 interrupt
	INTCON2 = 0x84;                //TMR0 high priority
#ifdef ENABLE_INT2
    INTCON3 = 0xD8;		//��������� ������� ���������� INT2 (��� �������������� ��������� ����� ���� 
#else                   //�������� ����������)� INT1 (��� ������ ������� ����������)
	INTCON3 = 0xC8;
#endif
    RCONbits.IPEN = 1;  //enable priority levels
	TMR0H = 0;          //clear timer
	TMR0L = 0;          //clear timer
	T0CON = 0xC5;
	INTCONbits.GIEH = 1; //enable interrupts
    IPR2 = 0x02;        //���������� ������� ��������� ���������� �� �/�3
	T2CON = 0;
	PIE1 = 0;
	PIE2 = 0;
    IPR1 = 0x02;                //���������� ������� ��������� ���������� �� �/�2
#ifdef ENABLE_INT2    
    TRIS_INTR_NULL_SIN = IN;    //���������� �� ���� ��� �������� ��������� INT2 (������� �������� ����� ���� 220�)
#endif
}

void Intr_set_cnt_zero_crossing(uint8_t value)
{
	cnt_zero_crossing = value;
}

uint16_t Intr_get_cnt_zero_crossing(void)
{
	return cnt_zero_crossing;
}

void Intr_set_is_zero_cross (BOOL value)
{
	is_zero_cross = value;
}

BOOL Intr_get_is_zero_cross(void)
{
	return is_zero_cross;
}

BOOL Intr_get_is_impulse_agitator_sensor(void)
{
	return is_impulse_agitator_sensor;
}

void Intr_set_is_impulse_agitator_sensor (BOOL value)
{
	is_impulse_agitator_sensor = value;
}




