# MPLAB IDE generated this makefile for use with GNU make.
# Project: SW_SPI.mcp
# Date: Tue Feb 10 19:02:20 2009

AS = mpasmwin.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

SW_SPI.cof : main.o
	"C:\Program Files\Microchip\MPASM Suite\MPLink.exe" /l"C:\MCC18\lib" "..\..\LED\18f4550.lkr" "main.o" /u_CRUNTIME /u_DEBUG /u_DEBUGCODESTART=0x7dc0 /u_DEBUGCODELEN=0x240 /u_DEBUGDATASTART=0x3f4 /u_DEBUGDATALEN=0xc /z__MPLAB_BUILD=1 /z__MPLAB_DEBUG=1 /z__MPLAB_DEBUGGER_ICD2=1 /z__ICD2RAM=1 /o"SW_SPI.cof" /M"SW_SPI.map" /W

main.o : main.c SW_SPI.h main.c ../../../../../../MCC18/h/p18f4550.h
	$(CC) -p=18F4550 /i"C:\MCC18\h" "main.c" -fo="main.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

clean : 
	$(RM) "main.o" "SW_SPI.cof" "SW_SPI.hex"

