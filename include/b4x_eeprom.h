/*    _____   _____    _____   _____   _   __
 *   |  _  \ |  _  \  /  _  \ /  _  \ | | / /
 *   | |_) | | |_) |  | | | | | | | | | |/ /
 *   |  _ <  |  _ <   | | | | | | | | |   (
 *   | |_) | | | \ \  | |_| | | |_| | | |\ \
 *   |_____/ |_|  \_\ \_____/ \_____/ |_| \_\ 4-XC8.
 *
 *   –– a small XC8 library for development with 8-bit PIC MCUs.
 *
 * Copyright (c) 2017 Silvio Clecio <silvioprog@gmail.com>
 *
 * This file is part of Brook4-XC8.
 *
 * Brook4-XC8 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Brook4-XC8 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Brook4-XC8.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef B4X_EEPROM_H
#define	B4X_EEPROM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <xc.h>
#include "b4x_types.h"

/**
 * EEPROM size.
 */
#define B4X_EEPROM_SIZE _EEPROMSIZE

/**
 * Write char to the EEPROM memory.
 * @param addr Memory address.
 * @param val Char value.
 */
#define B4X_EEPROM_WRITE(addr, val) do { \
    EEPROM_WRITE((addr), (val)); \
    while (WR); \
} while (0)

/**
 * Read char from the EEPROM memory.
 * @param addr Memory address.
 * @param val Char value.
 */
#define B4X_EEPROM_READ(addr, val) do { \
    (val) = EEPROM_READ((addr)); \
    while (RD); \
} while (0)

#pragma warning push
#pragma warning disable 751

/**
 * Write int to the EEPROM memory (inline).
 * @param addr Memory address.
 * @param val Int value.
 */
#define B4X_EEPROM_WRITE_INT(addr, val) do { \
    eeprom_write((addr), (val) & 0xff); \
    eeprom_write((addr) + 1, ((val) >> 8 & 0xff)); \
    eeprom_write((addr) + 2, ((val) >> 16 & 0xff)); \
    eeprom_write((addr) + 3, ((val) >> 24 & 0xff)); \
} while (0)

#pragma warning pop

/**
 * Read int from the EEPROM memory (inline).
 * @param addr Memory address.
 * @param val Char value.
 */
#define B4X_EEPROM_READ_INT(addr, val) do { \
    val = eeprom_read((addr) + 3); \
    val <<= 8; \
    val += eeprom_read((addr) + 2); \
    val <<= 8; \
    val += eeprom_read((addr) + 1); \
    val <<= 8; \
    val += eeprom_read((addr)); \
} while (0)

/**
 * Write int to the EEPROM memory.
 * @param addr Memory address.
 * @param val Int value.
 */
B4X_EXTERN void b4x_eeprom_write_int(unsigned char addr, unsigned int val);

/**
 * Read int from the EEPROM memory.
 * @param addr Memory address.
 * @param val Char value.
 */
B4X_EXTERN void b4x_eeprom_read_int(unsigned char addr, unsigned int *val);

/* B4X_EEPROM_*_INT()/b4x_eeprom_*_int() was inspired by:
 * <https://electronics.stackexchange.com/questions/191414/mplabx-how-to-read-write-4-bytes-unsigned-integer-to-eeprom> */

#ifdef __cplusplus
}
#endif

#endif