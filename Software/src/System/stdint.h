/**
* \file
* \brief  Переопределение типов переменных.
*
*/
#ifndef STDINT_H_
#define STDINT_H_


typedef	signed char			 int8_t;
typedef	unsigned char		 uint8_t;
typedef	int		           	 int16_t;
typedef	unsigned int         uint16_t;
typedef	long			     int32_t;
typedef	unsigned long		 uint32_t;


typedef enum _BOOL { FALSE = 0, TRUE }   BOOL;
typedef enum _ON_OFF { OFF = 0, ON }     ON_OFF;
typedef enum _PORT_STATE { OUT = 0, IN } PORT_STATE;

#endif
