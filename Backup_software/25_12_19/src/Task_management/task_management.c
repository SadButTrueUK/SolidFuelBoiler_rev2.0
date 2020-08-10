#include "module_management.h"
#include "task_management.h"
#include "module_motor.h"
#include "OSA.h"
#include <p18cxxx.h>

void Task_Management(void)
{
	for (;;) 
	{ 
        M_Mngm_Run ();
		ClrWdt();
        OS_Delay(TIMEOUT_TASK_MANAGEMENT);
	}
}