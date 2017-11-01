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

#include <xc.h>
#include "b4x_adc.h"

#pragma warning push
#pragma warning disable 520
#pragma warning disable 1498

void b4x_adc_init() {
    B4X_ADC_INIT();
}

void b4x_adc_channel(unsigned char ch) {
    B4X_ADC_CHANNEL(ch);
}

void b4x_adc_prepare() {
    B4X_ADC_PREPARE();
}

void b4x_adc_val2(int *val) {
    B4X_ADC_VAL2(val);
}

void b4x_adc_val(unsigned char ch, int *val) {
    B4X_ADC_VAL(ch, val);
}

int b4x_adc_read2() {
    int val;
    b4x_adc_val2(&val);
    return val;
}

int b4x_adc_read(unsigned char ch) {
    int val;
    b4x_adc_val(ch, &val);
    return val;
}

#pragma warning pop