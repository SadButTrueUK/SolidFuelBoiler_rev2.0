#include "module_indication.h"
#include "module_fan.h"
#include "module_sound.h"
#include "OSA.h"
#include "task_outs.h"
#include <p18cxxx.h>

/*
������ ���������� ����������� ��������
�������� ��������� ���������� ����������, ������������, ������
*/


void Task_Outs(void)
{
	for (;;) 
	{ 
		
		M_Ind_Run();
		M_fan_run();
		M_Sound_run();
		ClrWdt();
        OS_Delay(TIMEOUT_TASK_OUTS);
	}
}