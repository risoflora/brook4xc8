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

#ifndef B4X_SWITCH_H
#define	B4X_SWITCH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "b4x_types.h"

/**
 * Maps switch clicking.
 * @param p Port bit.
 */
#ifndef B4X_SW_CLICK
#define B4X_SW_CLICK(p) \
    static B4X_VBIT B4X_SW_##p##_CLICKED; \
    if (!(p)) \
        B4X_SW_##p##_CLICKED = 0; \
    if (((p) && !B4X_SW_##p##_CLICKED))
#endif

/**
 * Maps switch clicking in pull-up style.
 * @param p Port bit.
 */
#ifndef B4X_SW_nCLICK
#define B4X_SW_nCLICK(p) \
    static B4X_VBIT B4X_SW_##p##_CLICKED; \
    if ((p)) \
        B4X_SW_##p##_CLICKED = 0; \
    if (((!p) && !B4X_SW_##p##_CLICKED))
#endif

/**
 * Maps switch long clicking.
 * @param p Port bit.
 */
#ifndef B4X_SW_LONG_CLICK
#define B4X_SW_LONG_CLICK(p) \
    static B4X_VBIT B4X_SW_##p##_CLICKED; \
    if (!(p)) \
        B4X_SW_##p##_CLICKED = 0; \
    if (((p) && !B4X_SW_##p##_CLICKED)) \
        for (unsigned char i = 0; i < 10 && (p); i++) \
            if (i != 9) \
                __delay_ms(100); \
            else
#endif

/**
 * Maps switch long clicking in pull-up style.
 * @param p Port bit.
 */
#ifndef B4X_SW_LONG_nCLICK
#define B4X_SW_LONG_nCLICK(p) \
    static B4X_VBIT B4X_SW_##p##_CLICKED; \
    if ((p)) \
        B4X_SW_##p##_CLICKED = 0; \
    if (((!p) && !B4X_SW_##p##_CLICKED)) \
        for (unsigned char i = 0; i < 10 && (!p); i++) \
            if (i != 9) \
                __delay_ms(100); \
            else
#endif

/**
 * Debounce time (in ms).
 */
#ifndef B4X_SW_DEBOUNCE_TIME
#define B4X_SW_DEBOUNCE_TIME 250
#endif

/**
 * Avoid switch bouncing on #B4X_SW_CLICK or #B4X_SW_nCLICK calls.
 * @param p Port bit.
 */
#ifndef B4X_SW_DEBOUNCE
#define B4X_SW_DEBOUNCE(p) do { \
    B4X_SW_##p##_CLICKED = 1; \
    __delay_ms(B4X_SW_DEBOUNCE_TIME); \
} while (0)
#endif

/**
 * Toggles a port bit.
 * @param p Port bit (or any integer variable).
 */
#ifndef B4X_SW_TOGGLE
#define B4X_SW_TOGGLE(p) (p) = (!p)
#endif

#ifdef __cplusplus
}
#endif

#endif