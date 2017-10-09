/*
 * File:   main.c
 * Author: silvioprog
 *
 * Created on October 6, 2017, 6:24 PM
 */

/* PIC12F629A configuration bit settings. */
#pragma config FOSC = INTRCIO
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config MCLRE = OFF
#pragma config BOREN = OFF
#pragma config CP = OFF
#pragma config CPD = OFF

#include <xc.h>
#include <b4x_switch.h>
#include <b4x_eeprom.h>

#define LED GP0 /* Set GP0 as LED driver. */

volatile bit LED_STATUS; /* Handle LED status. */

void main() {
    CMCON = 0x07; /* Disable comparator. */
    TRISIO = 0x3e; /* Configure output pin. */
    for (;;) { /* Main loop. */
        B4X_SW_TOGGLE(LED_STATUS); /* Toggle LED status. */
        B4X_EEPROM_WRITE(3, (unsigned char) LED_STATUS); /* Write LED status to EEPROM. */
        B4X_EEPROM_READ(3, LED); /* Read LED status from EEPROM. */
        __delay_ms(500); /* Wait for 500 ms. */
    }
}