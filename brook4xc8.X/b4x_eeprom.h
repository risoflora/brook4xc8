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
 * Write data to the EEPROM memory.
 * @param addr Memory address.
 * @param val Data value.
 */
#define B4X_EEPROM_WRITE(addr, val) do { \
    EEPROM_WRITE((addr), (val)); \
    while (WR); \
} while (0)

/**
 * Read data from the EEPROM memory.
 * @param addr Memory address.
 * @param val Data value.
 */
#define B4X_EEPROM_READ(addr, val) do { \
    (val) = EEPROM_READ((addr)); \
    while (RD); \
} while (0)

#ifdef __cplusplus
}
#endif

#endif