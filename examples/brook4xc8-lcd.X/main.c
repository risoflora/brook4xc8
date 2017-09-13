/*
 * File:   main.c
 * Author: silvioprog
 *
 * Created on August 31, 2017, 6:58 PM
 */

/* PIC16F628A configuration bit settings. */
#pragma config FOSC = INTOSCIO
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config MCLRE = OFF
#pragma config BOREN = OFF
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config CP = OFF

#include <xc.h>
#include <b4x_lcd.h>

B4X_LCD_SET_RS(PORTB, 0); /* Set LCD RS port. */
B4X_LCD_SET_E(PORTB, 1); /* Set LCD E port. */
B4X_LCD_SET_D4(PORTB, 2); /* Set LCD D4 port. */
B4X_LCD_SET_D5(PORTB, 3); /* Set LCD D5 port. */
B4X_LCD_SET_D6(PORTB, 4); /* Set LCD D6 port. */
B4X_LCD_SET_D7(PORTB, 5); /* Set LCD D7 port. */

void main() {
    CMCON = 0x07; /* Disable comparator. */
    TRISB = 0xc0; /* RB<5:0> as output. */
    b4x_lcd_init(); /* Initialize LCD. */
    b4x_lcd_write(0, 0, "HELLO WORLD!"); /* Writes "HELLO WORLD!" on the LCD. */
    for (;;); /* Main loop. */
}