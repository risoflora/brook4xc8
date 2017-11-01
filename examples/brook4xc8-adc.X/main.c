/*
 * File:   main.c
 * Author: silvioprog
 *
 * Created on September 13, 2017, 2:55 AM
 */

/* PIC16F676 configuration bit settings. */
#pragma config FOSC = INTRCIO
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config MCLRE = OFF
#pragma config BOREN = OFF
#pragma config CP = OFF
#pragma config CPD = OFF

#include <xc.h>
#include <stdlib.h>
#include <b4x_lcd.h>
#include <b4x_adc.h>

B4X_LCD_SET_RS(PORTC, 0); /* Set LCD RS port. */
B4X_LCD_SET_E(PORTC, 1); /* Set LCD E port. */
B4X_LCD_SET_D4(PORTC, 2); /* Set LCD D4 port. */
B4X_LCD_SET_D5(PORTC, 3); /* Set LCD D5 port. */
B4X_LCD_SET_D6(PORTC, 4); /* Set LCD D6 port. */
B4X_LCD_SET_D7(PORTC, 5); /* Set LCD D7 port. */

int ADC_VAL, ADC_OLD_VAL; /* Variables to get ADC value and to avoid display blinking. */
char ADC_VAL_STR[4]; /* Variable to display ADC value as string. */

void main() {
    CMCON = 0x07; /* Disable comparator. */
    TRISA = 0xff; /* RA<7:0> as input. */
    TRISC = 0xc0; /* RC<5:0> as output. */
    ANSEL = 0x02; /* Enable AN 1. */
    b4x_adc_init(); /* Initialize ADC. */
    b4x_lcd_init(); /* Initialize LCD. */

    B4X_RUN() { /* Main loop. */
        /* Update display if new ADC value is different from the already read. */
        if ((ADC_VAL = b4x_adc_read(1)) != ADC_OLD_VAL) { /* Read ADC value from channel 1. */
            ADC_OLD_VAL = ADC_VAL; /* Hold new ADC value. */
            itoa(ADC_VAL_STR, ADC_VAL, 10); /* Convert ADC value to string. */
            b4x_lcd_write(0, 0, "VALUE: "); /* Print initial label. */
            b4x_lcd_erase(7, 0, sizeof (ADC_VAL_STR)); /* Erase previous printed ADC value. */
            b4x_lcd_write_str(7, 0, ADC_VAL_STR); /* Print new ADC value. */
        }
    }
}