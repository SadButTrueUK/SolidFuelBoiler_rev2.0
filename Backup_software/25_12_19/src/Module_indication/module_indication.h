#ifndef _MODULE_INDICATION_H_
#define _MODULE_INDICATION_H_

#include "stdint.h"


#define NEED_BLINK                      1
#define NO_NEED_BLINK                   0

//«начени€ автомата состо€ний модул€ индикации
#define STATE_IND_INIT					0U
#define STATE_VIEW_NUM_PAGE_MENU		1U	
#define STATE_VIEW_PARAMETER_MENU		2U
#define STATE_VIEW_TEMPERATURE_REAL		3U
#define STATE_VIEW_TEMPERATURE_SETUP	4U
#define STATE_VIEW_PAUSE				5U
#define STATE_VIEW_CLEAN_CHIMNEY		6U
#define STATE_VIEW_SUPPLY_FUEL			7U
#define STATE_VIEW_FAILURE				8U
#define STATE_VIEW_SPEED_FAN_SETUP      9U


void 			M_Ind_Run(void);
void 			M_Ind_Set_state(uint8_t value);
uint8_t 		M_Ind_Get_state(void);
void 			M_Ind_Set_Previous_State(uint8_t state); 
uint8_t 		M_Ind_Get_Previous_State(void);
void 			M_Ind_Set_blink_mode(BOOL value);
void 			M_Ind_setTimeAutoExit( uint8_t value );
void            M_Ind_ctor(void);

#endif