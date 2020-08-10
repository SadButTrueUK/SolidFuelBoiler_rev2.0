//Модуль драйвера I2C

#include "i2c.h"
#include <p18cxxx.h>

void i2c_init(void) 
{
	// Initial PIC18F87О50 I2C bus Ports: RС4 - SDA and RС3 - SCL, Set as Input
	TRISCbits.TRISC4 = 1;
	TRISCbits.TRISC3 = 1;  

	// Initial the PIC18F14K22 MSSP Peripheral I2C Master Mode
	// I2C Master Clock Speed: 16000000 / ((4 * (SSPADD + 1)) = 16000000 / (4 * (39 + 1))
	SSP1STAT = 0x80;      // Slew Rate is disable for 100 kHz mode
	SSP1CON1 = 0x28;      // Enable SDA and SCL, I2C Master mode, clock = FOSC/(4 * (SSPADD + 1))
	SSP1CON2 = 0x00;      // Reset MSSP Control Register
	SSP1ADD = 39;         // Standard I2C Clock speed: 100 kHz  
	PIR1bits.SSP1IF=0;    // Clear MSSP Interrupt Flag
}

void i2c_idle(void)
{
	// Wait I2C Bus and Status Idle (i.e. ACKEN, RCEN, PEN, RSEN, SEN)
	while (( SSP1CON2 & 0x1F ) || ( SSP1STATbits.R_W));
}

void i2c_start(uint8_t stype)
{
	i2c_idle();                     // Ensure the I2C module is idle
	if (stype == I2C_START_CMD) 
	{
		SSP1CON2bits.SEN = 1;          // Start I2C Transmission
		while(SSP1CON2bits.SEN);
	} 
	else 
	{
		SSP1CON2bits.RSEN = 1;         // ReStart I2C Transmission
		while(SSP1CON2bits.RSEN);
	}
}

void i2c_stop(void)
{
	// Stop I2C Transmission
	SSP1CON2bits.PEN = 1;
	while(SSP1CON2bits.PEN);
}

uint8_t i2c_slave_ack(void)
{
	// Return: 1 = Acknowledge was not received from slave
	//         0 = Acknowledge was received from slave
	return(SSP1CON2bits.ACKSTAT);
}

void i2c_write(uint8_t data)
{
  // Send the Data to I2C Bus
  SSP1BUF = data;
  if (SSP1CON1bits.WCOL)         // Check for write collision
    return;  

  while(SSP1STATbits.BF);        // Wait until write cycle is complete
  i2c_idle();                   // Ensure the I2C module is idle
}

void i2c_master_ack(uint8_t ack_type)
{
  SSP1CON2bits.ACKDT = ack_type;   // 1 = Not Acknowledge, 0 = Acknowledge
  SSP1CON2bits.ACKEN = 1;          // Enable Acknowledge
  while (SSP1CON2bits.ACKEN == 1U);
}

uint8_t i2c_read(void)
{
  // Ensure the I2C module is idle
  i2c_idle();                         

  // Enable Receive Mode
  SSP1CON2bits.RCEN = 1;           // Enable master for 1 byte reception
  while(!SSP1STATbits.BF);         // Wait until buffer is full
  return SSP1BUF;
}