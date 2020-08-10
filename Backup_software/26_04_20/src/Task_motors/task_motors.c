#include "OSA.h"
#include "task_motors.h"
#include "module_motor.h"
#include <p18cxxx.h>

void Task_Motors(void)
{
	for (;;) 
	{ 
		
		M_Motor_Run();
		ClrWdt();
        OS_Delay(TIMEOUT_TASK_MOTORS);
	}
}