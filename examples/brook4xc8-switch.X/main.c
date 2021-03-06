/*
 * File:   main.c
 * Author: silvioprog
 *
 * Created on September 2, 2017, 1:32 AM
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
#include <b4x_macros.h>
#include <b4x_switch.h>

#define SW1 RB0 /* Set SW1 pin. */
#define LED_GREEN RB1 /* Set green LED pin. */
#define SW2 RB2 /* Set SW2 pin. */
#define LED_RED RB3 /* Set red LED pin. */
#define SW3 RB4 /* Set WS3 pin. */
#define LED_BLUE RB5 /* Set blue LED pin. */

void main() {
    CMCON = 0x07; /* Disable comparator. */
    TRISB = 0xd5; /* Switches: RB<2:0>; LEDs: RB<3:1>. */
    LED_GREEN = 0; /* Turn off green LED. */
    LED_RED = 0; /* Turn off red LED. */
    LED_BLUE = 0; /* Turn off blue LED. */

    B4X_RUN() { /* Main loop. */

        B4X_SW_CLICK(SW1) { /* On/off green LED. */
            B4X_SW_DEBOUNCE(SW1);
            LED_GREEN = !LED_GREEN;
        }

        B4X_SW_nCLICK(SW2) { /* On/off red LED. */
            B4X_SW_DEBOUNCE(SW2);
            B4X_SW_TOGGLE(LED_RED);
        }

        B4X_SW_LONG_CLICK(SW3) { /* On/off blue LED (using long click). */
            B4X_SW_DEBOUNCE(SW3);
            B4X_SW_TOGGLE(LED_BLUE);
        }
    }
}