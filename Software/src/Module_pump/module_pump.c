#include "module_pump.h"
#include "module_management.h"
#include <p18cxxx.h>

#define PUMP_TRIS TRISHbits.TRISH6
#define PUMP_PIN  LATHbits.LATH6

void M_Pump_ctor( void )
{
    PUMP_TRIS = OUT;
    PUMP_PIN = OFF;
}

void M_Pump_run( void )
{
   if( M_Mngm_get_burning_state( ) == MAINTENANCE_TEMPERATURE_CYCLE ) 
       PUMP_PIN = ON;
   else
       PUMP_PIN = OFF;
}

