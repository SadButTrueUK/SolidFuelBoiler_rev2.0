#include "task_analog_inputs.h"
#include "module_analog_inputs.h"
#include "OSA.h"
#include <p18cxxx.h>

void Task_Analog_Inputs(void)
{
	for (;;) 
	{ 
			
		M_AI_Run();
		ClrWdt();
        OS_Delay(TIMEOUT_TASK_ANALOG_INPUTS);
	}
}