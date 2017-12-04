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

#ifndef B4X_ADC_H
#define B4X_ADC_H

#include <xc.h>
#include "b4x_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Maximum ADC value.
 */
#define B4X_ADC_MAX 0x3ff

/**
 * Converts ADC value to Vref.
 * @param r Vref (e.g: 2.5).
 * @param v ADC value (e.g: B4X_ADC_dtovr(2.5, 1023) = 2.5).
 */
#define B4X_ADC_dtovr(r, v) (((r) / (B4X_ADC_MAX)) * (v))

/**
 * Converts ADC value to VDD.
 * @param v ADC value (e.g: B4X_ADC_dtov(1023) = 5.0).
 */
#define B4X_ADC_dtov(v) B4X_ADC_dtovr(5.0, (v))

/**
 * Delay time for ADC preparing.
 */
#ifndef B4X_ADC_VAL_DELAY_US
#define B4X_ADC_VAL_DELAY_US 20
#endif

/**
 * Initializes ADC module.
 */
#define B4X_ADC_INIT() do { \
    ADFM = 1; \
    ADON = 1; \
} while (0)

/**
 * Selects ADC channel.
 * @param ch ADC channel.
 */
#define B4X_ADC_CHANNEL(ch) do { \
    ADCON0bits.CHS = (ch); \
} while (0)

/**
 * Prepares ADC for reading.
 */
#define B4X_ADC_PREPARE() do { \
    __delay_us(B4X_ADC_VAL_DELAY_US); \
    GO_nDONE = 1; \
    while (GO_nDONE); \
} while (0)

/**
 * Get ADC value in place.
 * @param val Variable address for value getting.
 */
#define B4X_ADC_VAL2(val) do { \
    B4X_ADC_PREPARE(); \
    *(val) = (ADRESH << 8) | ADRESL; \
} while (0)

/**
 * Get ADC value by channel in place.
 * @param ch ADC channel.
 * @param val Variable address for value getting.
 */
#define B4X_ADC_VAL(ch, val) do { \
    B4X_ADC_CHANNEL((ch)); \
    B4X_ADC_VAL2((val)); \
} while (0)

/**
 * Initializes ADC module.
 */
B4X_EXTERN void b4x_adc_init();

/**
 * Selects ADC channel.
 * @param ch ADC channel.
 */
B4X_EXTERN void b4x_adc_channel(unsigned char ch);

/**
 * Prepares ADC for reading.
 */
B4X_EXTERN void b4x_adc_prepare();

/**
 * Get ADC value in place.
 * @param val Variable address for value getting.
 */
B4X_EXTERN void b4x_adc_val2(int *val);

/**
 * Get ADC value by channel in place.
 * @param ch ADC channel.
 * @param val Variable address for value getting.
 */
B4X_EXTERN void b4x_adc_val(unsigned char ch, int *val);

/**
 * Returns ADC value.
 */
B4X_EXTERN int b4x_adc_read2();

/**
 * Returns ADC value by channel.
 */
B4X_EXTERN int b4x_adc_read(unsigned char ch);

#ifdef __cplusplus
}
#endif

#endif