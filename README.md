# Brook4-XC8

Brook4-XC8 is a small XC8 library for development with 8-bit PIC MCUs.

# LCD driver

## Circuit

![LCD driver schematic](https://raw.githubusercontent.com/brook-dev/brook4xc8/master/examples/brook4xc8-lcd.X/schematic.png)

## Code

```c
#include <b4x_macros.h>
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
    B4X_RUN(); /* Main loop. */
}
```

# Switch handling

## Circuit

![Switch schematic](https://raw.githubusercontent.com/brook-dev/brook4xc8/master/examples/brook4xc8-switch.X/schematic.png)

## Code

```c
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
```
# ADC reading

## Circuit

![ADC schematic](https://raw.githubusercontent.com/brook-dev/brook4xc8/master/examples/brook4xc8-adc.X/schematic.png)

## Code

```c
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
```

# EEPROM writing/reading

## Circuit

![EEPROM schematic](https://raw.githubusercontent.com/brook-dev/brook4xc8/master/examples/brook4xc8-eeprom.X/schematic.gif)

## Code

```c
#include <b4x_macros.h>
#include <b4x_switch.h>
#include <b4x_eeprom.h>

#define LED GP0 /* Set GP0 as LED driver. */

volatile bit LED_STATUS; /* Handle LED status. */

void main() {
    CMCON = 0x07; /* Disable comparator. */
    TRISIO = 0x3e; /* Configure output pin. */

    B4X_RUN() { /* Main loop. */
        B4X_SW_TOGGLE(LED_STATUS); /* Toggle LED status. */
        B4X_EEPROM_WRITE(3, (unsigned char) LED_STATUS); /* Write LED status to EEPROM. */
        B4X_EEPROM_READ(3, LED); /* Read LED status from EEPROM. */
        __delay_ms(500); /* Wait for 500 ms. */
    }
}
```

## Notice

**(it is under development, however, we are working hardly to release new features :wink:)**
