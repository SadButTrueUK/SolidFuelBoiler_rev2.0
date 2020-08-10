#ifndef _I2C_H_
#define _I2C_H_

#include "stdint.h"

// I2C Bus Control Definition
#define I2C_DATA_ACK      0U
#define I2C_DATA_NOACK    1U
#define I2C_WRITE_CMD     0U
#define I2C_READ_CMD      1U

#define I2C_START_CMD     0U
#define I2C_REP_START_CMD 1U
#define I2C_REQ_ACK       0U
#define I2C_REQ_NOACK     0U

//Microchip 24LC08B 8KBits I2C EEPROM address
#define MEMORY_24LC08B_ADDR  0xA0  

void    i2c_init( void ); 
void    i2c_idle( void );
void    i2c_start( uint8_t stype );
void    i2c_stop( void );
uint8_t i2c_slave_ack( void );
void    i2c_write( uint8_t data );
void    i2c_master_ack( uint8_t ack_type );
uint8_t i2c_read( void );

#endif