#ifndef _SPI_H_
#define _SPI_H_

#include "stdint.h"

void HW_SPI_writeByte( uint8_t data );
void SW_SPI_writeByte( uint8_t data );
void SPI_init( void );

#endif