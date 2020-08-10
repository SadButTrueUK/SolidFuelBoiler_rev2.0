/*
 * Library: libcrc
 * File:    include/checksum.h
 * Author:  Lammert Bies
 *
 * This file is licensed under the MIT License as stated below
 *
 * Copyright (c) 1999-2018 Lammert Bies
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Description
 * -----------
 * The headerfile include/checksum.h contains the definitions and prototypes
 * for routines that can be used to calculate several kinds of checksums.
 */

//*****************************************************************************
// Команды препроцессора для предотвращения повторного включения содержимого файла
//*****************************************************************************
#ifndef CRC8_H
#define CRC8_H

//*****************************************************************************
// Подключаемые файлы
//*****************************************************************************
#include <stdint.h>

//*****************************************************************************
// Прототипы интерфейсных функций
//*****************************************************************************

//*****************************************************************************
/// \brief Вычисление контрольной суммы.
/// \param crc  - начальное значение CRC8;
/// \param data - указатель на массив данных;
/// \param len  - длина массива данных.
/// \return Значение контрольной суммы.
/// \note В качестве алгоритма вычисления контрольной суммы
/// используется CRC8, с начальным значением crc и полиномом \f$x^8 + x^7 + x^2 + 1\f$.
///
uint8_t crc8_update( uint8_t crc, const uint8_t *data, uint8_t len );

#endif 