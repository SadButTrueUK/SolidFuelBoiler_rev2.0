// MASTER

/** I N C L U D E S **********************************************************/
#include <p18f4550.h>
#include "SW_SPI.h"



#pragma config PLLDIV   = 5         // (20 MHz crystal on PICDEM FS USB board)
#pragma config CPUDIV   = OSC1_PLL2
#pragma config USBDIV   = 2         // Clock source from 96MHz PLL/2
#pragma config FOSC     = HSPLL_HS
#pragma config FCMEN    = OFF
#pragma config IESO     = OFF
#pragma config PWRT     = OFF
#pragma config BOR      = ON
#pragma config BORV     = 3
#pragma config VREGEN   = ON      //USB Voltage Regulator
#pragma config WDT      = OFF
#pragma config WDTPS    = 32768
#pragma config MCLRE    = ON
#pragma config LPT1OSC  = OFF
#pragma config PBADEN   = OFF
//      #pragma config CCP2MX   = ON
#pragma config STVREN   = ON
#pragma config LVP      = OFF
//      #pragma config ICPRT    = OFF       // Dedicated In-Circuit Debug/Programming
#pragma config XINST    = OFF       // Extended Instruction Set
#pragma config CP0      = OFF
#pragma config CP1      = OFF
//      #pragma config CP2      = OFF
//      #pragma config CP3      = OFF
#pragma config CPB      = OFF
//      #pragma config CPD      = OFF
#pragma config WRT0     = OFF
#pragma config WRT1     = OFF
//      #pragma config WRT2     = OFF
//      #pragma config WRT3     = OFF
#pragma config WRTB     = OFF       // Boot Block Write Protection
#pragma config WRTC     = OFF
//      #pragma config WRTD     = OFF
#pragma config EBTR0    = OFF
#pragma config EBTR1    = OFF
//      #pragma config EBTR2    = OFF
//      #pragma config EBTR3    = OFF
#pragma config EBTRB    = OFF


/** V E C T O R  R E M A P P I N G *******************************************/

//extern void _startup (void);        // See c018i.c in your C18 compiler dir
//#pragma code _RESET_INTERRUPT_VECTOR = 0x000800
//void _reset (void)
//{
//    _asm goto _startup _endasm
//}
//#pragma code

/** D E C L A R A T I O N S **************************************************/
#pragma code



/******************************************************************************
 * Function:        void main(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Main program entry point.
 *
 * Note:            None
 *****************************************************************************/
 
void Delay(void)
{
	int i, j;

	for (i=0; i < 100; i++) {
		for (j=0; j < 100; j++) {
		}
	}
} 
 
#define SPI_CS  PORTBbits.RB2 
int Data, shift;

void main(void)
{

	TRISD = 0x00;
	LATD = 0x00;

	// Set CS (Chip Select) pin (RA2) for the other PICDEM as output
//	TRISAbits.TRISA2 = 0; 


//	SPI_CS = 1; // ensure SPI device Chip Select is reset 

   // OpenSPI(SPI_FOSC_64, MODE_00, SMPMID);
//	SSPSTAT &= 0x3F;                // power on state 
// 	SSPCON1 = 0x00;                 // power on state
//	SSPSTATbits.CKE = 1;        // data transmitted on falling edge
    
	// Set CS pin (RB2), for the TC77 temperature chip on the PICDEM, as output
//	TRISBbits.TRISB2 = 0;
	// Deselect the TC77
//	PORTBbits.RB2 = 1; 
	//PORTBbits.RB5 = 0; //deselect the SW3

	//TRISAbits.TRISA2 = 0;
	//PORTAbits.RA2 = 0;
	//TRISBbits.TRISB1 = 0;       // define clock pin as output

//	TRISBbits.TRISB0 = 1;       // define SDI pin as input	
//    TRISCbits.TRISC7 = 0;       // define SDO pin as output


//	TRISBbits.TRISB1 = 0;       // define clock pin as output
//
//	TRISBbits.TRISB0 = 1;       // define SDI pin as input	
//    TRISCbits.TRISC7 = 0;       // define SDO pin as output
//	SSPCON1 |= SSPENB;
//	


	//configure software SPI
OpenSWSPI();
	while(1) {
		Delay();
		ClearCSSWSPI();		//Set CS low
		Data = WriteSWSPI(0x01);	//Read Data from the SPI
		SetCSSWSPI();		//Set CS high
//		SPI_CS = 0;
//		Data = ReadSPI();
//		SPI_CS = 1;
		PORTD = Data;		//Display SPI data on PORTD	
	}
}//end main



