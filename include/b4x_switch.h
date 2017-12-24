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
 * @param v Control variable.
 * @param p Port bit.
 */
#ifndef B4X_SW_CLICK2
#define B4X_SW_CLICK2(v, p) \
    if (!(p)) \
        (v) = 0; \
    if (((p) && !(v)))
#endif

/**
 * Maps switch clicking.
 * @param p Port bit.
 */
#ifndef B4X_SW_CLICK
#define B4X_SW_CLICK(p) \
    static B4X_VBIT B4X_SW_##p##_CLICKED; \
    B4X_SW_CLICK2(B4X_SW_##p##_CLICKED, (p))
#endif

/**
 * Maps switch clicking in pull-up style.
 * @param v Control variable.
 * @param p Port bit.
 */
#ifndef B4X_SW_nCLICK2
#define B4X_SW_nCLICK2(v, p) \
    if ((p)) \
        (v) = 0; \
    if ((!(p) && !(v)))
#endif

/**
 * Maps switch clicking in pull-up style.
 * @param p Port bit.
 */
#ifndef B4X_SW_nCLICK
#define B4X_SW_nCLICK(p) \
    static B4X_VBIT B4X_SW_##p##_CLICKED; \
    B4X_SW_nCLICK2(B4X_SW_##p##_CLICKED, (p))
#endif

/**
 * Maps switch long clicking.
 * @param v Control variable.
 * @param p Port bit.
 */
#ifndef B4X_SW_LONG_CLICK2
#define B4X_SW_LONG_CLICK2(v, p) \
    if (!(p)) \
        (v) = 0; \
    if (((p) && !(v))) \
        for (unsigned char i = 0; i < 10 && (p); i++) \
            if (i != 9) \
                __delay_ms(100); \
            else
#endif

/**
 * Maps switch long clicking.
 * @param p Port bit.
 */
#ifndef B4X_SW_LONG_CLICK
#define B4X_SW_LONG_CLICK(p) \
    static B4X_VBIT B4X_SW_##p##_CLICKED; \
    B4X_SW_LONG_CLICK2(B4X_SW_##p##_CLICKED, (p))
#endif

/**
 * Maps switch long clicking in pull-up style.
 * @param v Control variable.
 * @param p Port bit.
 */
#ifndef B4X_SW_LONG_nCLICK2
#define B4X_SW_LONG_nCLICK2(v, p) \
    if ((p)) \
        (v) = 0; \
    if ((!(p) && !(v))) \
        for (unsigned char i = 0; i < 10 && !(p); i++) \
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
    B4X_SW_LONG_nCLICK2(B4X_SW_##p##_CLICKED, (p))
#endif

/**
 * Debounce time (in ms).
 */
#ifndef B4X_SW_DEBOUNCE_TIME
#define B4X_SW_DEBOUNCE_TIME 250
#endif

/**
 * Avoids switch bouncing on #B4X_SW_CLICK2 or #B4X_SW_nCLICK2 calls.
 * @param p Port bit.
 */
#ifndef B4X_SW_DEBOUNCE2
#define B4X_SW_DEBOUNCE2(v, p) do { \
    (v) = 1; \
    __delay_ms(B4X_SW_DEBOUNCE_TIME); \
} while (0)
#endif

/**
 * Avoids switch bouncing on #B4X_SW_CLICK or #B4X_SW_nCLICK calls.
 * @param p Port bit.
 */
#ifndef B4X_SW_DEBOUNCE
#define B4X_SW_DEBOUNCE(p) do { \
    B4X_SW_##p##_CLICKED = 1; \
    __delay_ms(B4X_SW_DEBOUNCE_TIME); \
} while (0)
#endif

/**
 * Toggles a bit flag.
 * @param p Bit flag (or any integer flag).
 */
#ifndef B4X_SW_TOGGLE
#define B4X_SW_TOGGLE(f) (f) = !(f)
#endif

#ifdef __cplusplus
}
#endif

#endif