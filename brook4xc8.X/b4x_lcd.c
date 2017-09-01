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

/* inspired by
 * <https://github.com/magkopian/pic-xc8-lcd-library>
 * <https://github.com/tgrijalva/arduino_character_lcd> */

#include <xc.h>
#include "b4x_macros.h"
#include "b4x_lcd.h"

static void _b4x_lcd_set_out(unsigned char data) {
    if (data & 1)
        B4X_LCD_D4 = 1;
    else
        B4X_LCD_D4 = 0;
    if (data & 2)
        B4X_LCD_D5 = 1;
    else
        B4X_LCD_D5 = 0;
    if (data & 4)
        B4X_LCD_D6 = 1;
    else
        B4X_LCD_D6 = 0;
    if (data & 8)
        B4X_LCD_D7 = 1;
    else
        B4X_LCD_D7 = 0;
}

static void _b4x_lcd_write(unsigned char c) {
    B4X_LCD_RS = 0;
    _b4x_lcd_set_out(c);
    B4X_LCD_E = 1;
    __delay_ms(4);
    B4X_LCD_E = 0;
}

void b4x_lcd_init() {
    __delay_ms(20);
    _b4x_lcd_write(0x03);
    __delay_ms(5);
    _b4x_lcd_write(0x03);
    __delay_ms(16);
    _b4x_lcd_write(0x03);
    _b4x_lcd_write(0x02);
    b4x_lcd_cmd(0x28);
    b4x_lcd_cmd(0x06);
    b4x_lcd_cmd(B4X_LCD_ON);
    b4x_lcd_cmd(B4X_LCD_CLEAR);
}

void b4x_lcd_cmd(unsigned char cmd) {
    _b4x_lcd_write((unsigned char) ((cmd & 0xf0) >> 4));
    _b4x_lcd_write((unsigned char) (cmd & 0x0f));
}

void b4x_lcd_pos(unsigned char x, unsigned char y) {
    switch (y) {
        case 0:
            b4x_lcd_cmd((unsigned char) (0x80 + x));
            break;
        case 1:
            b4x_lcd_cmd((unsigned char) (0xc0 + x));
            break;
        case 2:
            b4x_lcd_cmd((unsigned char) (0x94 + x));
            break;
        case 3:
            b4x_lcd_cmd((unsigned char) (0xd4 + x));
            break;
        default: b4x_lcd_cmd((unsigned char) (0x80 + x));
    }
}

void b4x_lcd_putc(char c) {
    B4X_LCD_RS = 1;
    _b4x_lcd_set_out((unsigned char) ((c & 0xf0) >> 4));
    B4X_LCD_E = 1;
    __delay_us(40);
    B4X_LCD_E = 0;
    _b4x_lcd_set_out((unsigned char) (c & 0x0f));
    B4X_LCD_E = 1;
    __delay_us(40);
    B4X_LCD_E = 0;
}

void b4x_lcd_puts(char *s) {
    for (unsigned int i = 0; s[i] != '\0'; ++i)
        b4x_lcd_putc(s[i]);
}

void b4x_lcd_putrs(const char *s) {
    for (unsigned int i = 0; s[i] != '\0'; ++i)
        b4x_lcd_putc(s[i]);
}

void b4x_lcd_write_chr(unsigned char x, unsigned char y, char c) {
    b4x_lcd_pos(x, y);
    b4x_lcd_putc(c);
}

void b4x_lcd_write_str(unsigned char x, unsigned char y, char *s) {
    b4x_lcd_pos(x, y);
    b4x_lcd_puts(s);
}

void b4x_lcd_write(unsigned char x, unsigned char y, const char *s) {
    b4x_lcd_pos(x, y);
    b4x_lcd_putrs(s);
}