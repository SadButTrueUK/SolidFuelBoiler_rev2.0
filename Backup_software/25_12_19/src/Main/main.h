#ifndef _MAIN_H_
#define _MAIN_H_

/* Директивы компилятора для использования в отладочных режимах 
DEBUG_MODE - отладка с отключенным сторожевым таймером
NO_SENSOR_GAS - отладка с отключенным датчиком исходящих газов
NO_220V_SUPPLY - отладка без подачи 220В на плату управления
NO_CONTROL_DRAUGHT - отключен контроль тяги по датчику исходящих газов
*/

//#define DEBUG_MODE
#define NO_SENSOR_GAS
#define NO_220V_CONTROL
#define NO_CONTROL_DRAUGHT
#define NO_CONTROL_FALSE_STATE_LS

//#define DEBUG_IN_SIMULATOR
#define ENABLE_INT2

#endif