
/************************************************************************
*
*   Emulating Data EEPROM for PIC18 Microcontrollers that support
*           the ability to self program a single location
*                (two bytes) of program memory
*
* This routine is an example of a write and read operation using emulated
* Data EEPROM algorithm. Add the variable "value" to the MPLAB IDE Watch
* Window using an emulator. The expected value is 25 after the read
* function executes. Place a breakpoint on the Nop(); in main to see
* value = 25.
* The configuration bit settings match those of the HPC Explorer
* Development Board. Compatable settings are selected at compile time
* based on the device selected in MPLAB IDE.
*************************************************************************
* FileName:     main.c
* FileName:     DEE Emulation 8-bit.c
* Dependencies: NoFilDEE.asm
                DEE Emulation 8-bit.h
                NoFilDEE.inc
* Compiler:     MPLAB C18, v3.02 or higher
* Company:      Microchip Technology, Inc.
*
* Software License Agreement
*
* Copyright © 2007 Microchip Technology Inc. All rights reserved.
*
* Microchip licenses to you the right to use, modify, copy and distribute
* Software only when embedded on a Microchip microcontroller or digital
* signal controller, which is integrated into your product or third party
* product (pursuant to the sublicense terms in the accompanying license
* agreement).
*
* You should refer to the license agreement accompanying this Software for
* additional information regarding your rights and obligations.
*
* SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY
* KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY
* WARRANTY OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A
* PARTICULAR PURPOSE. IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE
* LIABLE OR OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY,
* CONTRIBUTION, BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY
* DIRECT OR INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY
* INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST
* PROFITS OR LOST DATA, COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY,
* SERVICES, OR ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO
* ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*
* Author                           Date                     Comment
*************************************************************************
* S. Cowden                     2007/05/24      Version 1.0.0 - Initial Release
* Pradeep Budagutta       2007/05/24      Version 1.1.1 - Added test for above 255 addresses
************************************************************************/

#include <p18cxxx.h>
#include "DEE Emulation 8-bit\DEE Emulation 8-bit.h"

//// Set up the Configuration Regs
#if defined (__18F87J11)
    #pragma config WDTEN = OFF
    #pragma config FOSC = HS 
    #pragma config MODE = MM
    #pragma config XINST = OFF
#else
    #error Please specify configuration bits for the selected device.
#endif
	

void main(void)
{
    unsigned char value;
    unsigned char DEEdata = 0x25;
    unsigned int  DEEaddr = 0x04;

    DataEEInit();
    dataEEFlags.val = 0;

    DataEEWrite(DEEdata,DEEaddr);
    value = DataEERead(DEEaddr);
    Nop();

    DataEEWrite(2*DEEdata,254);
    value = DataEERead(DEEaddr);
    Nop();

    DataEEWrite(3*DEEdata,254 + DEEaddr);
    value = DataEERead(DEEaddr);
    Nop();

    return;
}
