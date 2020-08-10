#ifndef _INTERRUPTS_H_
#define _INTERRUPTS_H_

#include "stdint.h"

void	 Intr_set_cnt_zero_crossing (uint8_t value);
uint16_t Intr_get_cnt_zero_crossing (void);
void 	 Intr_set_is_zero_cross (BOOL value);
BOOL 	 Intr_get_is_zero_cross(void);
BOOL 	 Intr_get_is_impulse_agitator_sensor(void);
void 	 Intr_set_is_impulse_agitator_sensor (BOOL value);
void     Intr_ctor( void );

#endif