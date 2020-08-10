#include <p18f87j50.h>
#include <delays.h>
#include "spi.h"
#include "logicAnalyzer.h"


#define STROBE_EN_PIN   LATDbits.LATD5
#define STROBE_EN_TRIS  TRISDbits.TRISD5


static void DebugTools_setStrobeSPI(void);

//*****************************************************************************
// Реализация интерфейсных функций
//*****************************************************************************

//*****************************************************************************
// Инициализация компонента DebugTools

void DebugTools_ctor(void) 
{
    SPI_init();
    STROBE_EN_TRIS = OUT;
    STROBE_EN_PIN = 1;
#ifndef ENABLE_SECOND_PUMP 
    DEBUG_PIN_1_GPIO = OFF;
    DEBUG_PIN_1_TRIS = OUT;
#endif
#ifndef ENABLE_TRISTATE_VALVE     
    DEBUG_PIN_2_GPIO = OFF; 
    DEBUG_PIN_2_TRIS = OUT; 
#endif    
}

//*****************************************************************************
// Реализация локальных функций
//*****************************************************************************

//*****************************************************************************
//Формирование строба

static void DebugTools_setStrobeSPI(void) 
{
    STROBE_EN_PIN = 1;
    Delay1TCY();
    STROBE_EN_PIN = 0;
}

//*****************************************************************************
// Передача по SPI слова данных

void DebugTools_trWordSPI(const uint16_t data)
{
    DebugTools_setStrobeSPI();
    HW_SPI_writeByte(data);
    Delay10TCYx(3);
}

//*****************************************************************************
// Передача по SPI массива данных data с размерностью size

void DebugTools_trBuffSPI(const uint16_t *data, const uint8_t size) 
{
    uint8_t count;

    DebugTools_setStrobeSPI();
    for (count = 0; count < size; count++) {
        HW_SPI_writeByte(data[ count ]);
        Delay10TCYx(3);
    }
}
