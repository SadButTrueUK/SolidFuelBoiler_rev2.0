#ifndef _LOGICANALYZER_H_
#define _LOGICANALYZER_H_

#include "stdint.h"   
#include "boardModes.h"

#ifndef ENABLE_SECOND_PUMP 
    #define DEBUG_PIN_1_GPIO   LATHbits.LATH5 
    #define DEBUG_PIN_1_TRIS   TRISHbits.TRISH5
    #define DEBUG_PIN_1_SET(x) LATHbits.LATH5 = ( x ) 
    #define DEBUG_PIN_1_TOGGLE LATHbits.LATH5 = !LATHbits.LATH5
#endif
#ifndef ENABLE_TRISTATE_VALVE  
    #define DEBUG_PIN_2_GPIO   LATBbits.LATB3 
    #define DEBUG_PIN_2_TRIS   TRISBbits.TRISB3
    #define DEBUG_PIN_2_SET(x) LATBbits.LATB3 = ( x ) 
    #define DEBUG_PIN_2_TOGGLE LATBits.LATB3 = !LATBbits.LATB3 
#endif

void DebugTools_ctor( void );
void DebugTools_trWordSPI( const uint16_t data );
void DebugTools_trBuffSPI( const uint16_t *data, const uint8_t size );


#endif