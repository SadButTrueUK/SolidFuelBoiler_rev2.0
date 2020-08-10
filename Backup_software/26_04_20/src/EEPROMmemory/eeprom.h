#ifndef _EEPROM_H_
#define _EEPROM_H_

#include "module_management.h"

#define START_ADDR       0 

uint8_t DataEERead(uint16_t mem_addr);
void    DataEEWrite(uint16_t mem_addr,uint8_t data);
void    Read_buffer_EEPROM (const uint8_t start_addr, ParametersBuffer* parameters_buffer, const uint8_t size_buff);
void    EEPROM_ctor( void );


#endif