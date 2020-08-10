#ifndef _MODULE_FAN_H_
#define _MODULE_FAN_H_

#include "stdint.h"


#define CALCULATE           0
#define ROTATE              1
#define FAN_NOT_ACCEL       0
#define FAN_IS_ACCEL		1


BOOL    M_fan_check_220V( void );
BOOL    M_fan_get_is_220V( void );
void    M_fan_run( void );
void    M_Fan_work_fan( uint8_t level );
void    M_fan_set_ctrl_fan( BOOL value );
void	M_fan_set_level_fan( uint8_t value );
void 	M_fan_clear_timeouts( void );
BOOL    M_fan_get_ctrl_fan( void );
void    M_Fan_ctor( void );


#endif
