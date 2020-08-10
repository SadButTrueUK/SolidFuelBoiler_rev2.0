//Модуль драйвера шины SPI (программного и аппаратного)

#include <p18f87j50.h>
#include "spi.h"
#include <delays.h>

#define HW_SPI_SDO_PIN   LATDbits.LATD4    
#define HW_SPI_SDO_TRIS  TRISDbits.TRISD4
#define HW_SPI_SCK_PIN   LATDbits.LATD6
#define HW_SPI_SCK_TRIS  TRISDbits.TRISD6
#define SW_SPI_SDO_PIN   LATJbits.LATJ0
#define SW_SPI_SDO_TRIS  TRISJbits.TRISJ0
#define SW_SPI_SCK_PIN   LATDbits.LATD7
#define SW_SPI_SCK_TRIS  TRISDbits.TRISD7


void SPI_init( void )
{
    //Инициализация аппаратного модуля SPI2
	SSP2STAT = 0b11000000;
	SSP2CON1 = 0b00100000;
    HW_SPI_SDO_TRIS = OUT;
    HW_SPI_SCK_TRIS = OUT;
    
    //Инициализация программного модуля SPI2
    SW_SPI_SDO_PIN  = 0;
    SW_SPI_SDO_TRIS = OUT;
    SW_SPI_SCK_PIN  = 0;
    SW_SPI_SCK_TRIS = OUT;
}

//Запись байта данных по аппаратному SPI
void HW_SPI_writeByte( uint8_t data )
{
    uint8_t temp;  
  	
  	temp = SSP2BUF;           // Clears BF
	PIR1bits.SSPIF = 0;       // Clear interrupt flag
	SSP2BUF = data;           // write byte to SSPBUF register
	while(!PIR1bits.SSPIF);   // wait until bus cycle complete  
}

//Запись байта данных по программному SPI
void SW_SPI_writeByte( uint8_t data )
{
    int8_t i;
	
    for( i = 0; i < 8; i++ ) 
    {
		SW_SPI_SCK_PIN = 0;
        if ( data & 0x80 ) 
            SW_SPI_SDO_PIN = 1;
		else 
            SW_SPI_SDO_PIN = 0;
		SW_SPI_SCK_PIN = 1;
        data <<= 1;
    }
}


