/* Программа для блока управления твердотопливным котлом с автоподачей топлива
Тип МК - PIC18F87J50
Частота выполнения команд - 12 Мгц (83 нс)
Тип ОС - кооперативная, PICOSA (версия 11.03.06)
Системный тик ОС - 1 мс 
Начальная версия ПО - 2.00
Автор - Кругликов Владислав	
Заказчик - Шумейко Роман
*/

#include <p18cxxx.h>
#include <delays.h>
#include "osa.h"
#include "main.h"
#include "task_logic_inputs.h"
#include "task_analog_inputs.h"
#include "task_outs.h"
#include "task_motors.h"
#include "module_analog_inputs.h"
#include "module_management.h"
#include "task_management.h"
#include "module_fan.h"
#include "module_indication.h"
#include "module_motor.h"
#include "module_sound.h"
#include "logicAnalyzer.h"
#include "eeprom.h"
#include "interrupts.h"
#include "module_logic_inputs.h"

//Конфигурационные биты МК
// CONFIG1L
#pragma config WDTEN = ON       // Watchdog Timer Enable bit (WDT enabled)
#pragma config PLLDIV = 2       // PLL Prescaler Selection bits (Prescale 2 (8 MHz oscillator input drives PLL directly))
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable bit (Reset on stack overflow/underflow enabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG1H
#pragma config CPUDIV = OSC1    // /* CPU System Clock Postscaler (No CPU system clock divide) */ CPU System Clock Divide by 2
#pragma config CP0 = OFF        // Code Protection bit (Program memory is not code-protected)

// CONFIG2L
#pragma config FOSC = HSPLL     // Oscillator Selection bits (HS oscillator, PLL enabled, HSPLL used by USB)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Two-Speed Start-up (Internal/External Oscillator Switchover) Control bit (Two-Speed Start-up disabled)

// CONFIG2H
#pragma config WDTPS = 256      // Watchdog Timer Postscaler Select bits (1:256)

// CONFIG3L
#pragma config EASHFT = OFF     // External Address Bus Shift Enable bit (Address shifting disabled, address on external bus reflects the PC value)
#pragma config MODE = MM        // External Memory Bus Configuration bits (Microcontroller mode - External bus disabled)
#pragma config BW = 16          // Data Bus Width Select bit (16-bit external bus mode)
#pragma config WAIT = OFF       // External Bus Wait Enable bit (Wait states on the external bus are disabled)

// CONFIG3H
#pragma config CCP2MX = DEFAULT // ECCP2 MUX bit (ECCP2/P2A is multiplexed with RC1)
#pragma config ECCPMX = DEFAULT // ECCPx MUX bit (ECCP1 outputs (P1B/P1C) are multiplexed with RE6 and RE5; ECCP3 outputs (P3B/P3C) are multiplexed with RE4 and RE3)
#pragma config PMPMX = DEFAULT  // PMP Pin Multiplex bit (PMP pins placed on EMB)
#pragma config MSSPMSK = MSK7   // MSSP Address Masking Mode Select bit (7-Bit Address Masking mode enable)



static void Init_PIC(void); //инициализация модулей программы


static void Init_PIC(void)
{
	OSCTUNEbits.PLLEN = 1;   //разрешить умножитель частоты 
    M_AI_ctor();
	M_Fan_ctor();
    M_Ind_ctor();
    M_Motor_ctor();
    M_Sound_ctor();
    DebugTools_ctor();
    M_LI_ctor();
    Delay10KTCYx(255); //задержка около 212 мс
#ifndef DEBUG_IN_SIMULATOR
    EEPROM_ctor();
#endif
    Intr_ctor();
}

void main (void)
{
	Init_PIC();									//инициализация контроллера
	OS_Init(); 									//инициализация ОСи
	OS_CreateTask(0, Task_Logic_Inputs);	 	//создание задачи опроса логических входов (кнопки, концевики, отработка кнопок в меню)
	OS_CreateTask(1, Task_Outs);          		//создание задачи управления логическими выходами (индикация, звук, вентилятор с алгоритмом фазового регулирования)		
	OS_CreateTask(1, Task_Management);          //создание задачи управления с высшим приоритетом 
    OS_CreateTask(0, Task_Analog_Inputs);       //создание задачи управления аналоговыми входами
	OS_CreateTask(0, Task_Motors);   			//создание задачи управления двигателями
	OS_Run();
}