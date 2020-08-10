#include "task_logic_inputs.h"
#include "module_logic_inputs.h"
#include "OSA.h"
#include <p18cxxx.h>

void Task_Logic_Inputs(void)
{
	for (;;) 
	{ 
		
		M_LI_Run();
		ClrWdt();
        OS_Delay(TIMEOUT_TASK_LOGIC_INPUTS);
	}
}