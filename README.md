# Brook4-XC8

Brook4-XC8 is a small XC8 library for development with 8-bit PIC MCUs.

# LCD driver

## Circuit

![LCD driver circuit](https://raw.githubusercontent.com/brook-dev/brook4xc8/master/examples/brook4xc8-lcd.X/schematic.png)

## Code

```c
#include "b4x_lcd.h"

B4X_LCD_SET_RS(PORTB, 0); /* Set LCD RS port. */
B4X_LCD_SET_E(PORTB, 1); /* Set LCD E port. */
B4X_LCD_SET_D4(PORTB, 2); /* Set LCD D4 port. */
B4X_LCD_SET_D5(PORTB, 3); /* Set LCD D5 port. */
B4X_LCD_SET_D6(PORTB, 4); /* Set LCD D6 port. */
B4X_LCD_SET_D7(PORTB, 5); /* Set LCD D7 port. */

void main() {
    CMCON = 0x07; /* Disable comparator. */
    TRISB = 0xc0; /* RB<0:5> as output. */
    b4x_lcd_init(); /* Initialize LCD. */
    b4x_lcd_write(0, 0, "HELLO WORLD!"); /* Writes "HELLO WORLD!" on the LCD. */
    for (;;); /* Main loop. */
}
```

# Switch handling

## Circuit

![LCD driver circuit](https://raw.githubusercontent.com/brook-dev/brook4xc8/master/examples/brook4xc8-switch.X/schematic.png)

## Code

```c
#include "b4x_switch.h"

#define SW1 RB0 /* Set SW1 pin. */
#define LED_GREEN RB1 /* Set green LED pin. */
#define SW2 RB2 /* Set SW2 pin. */
#define LED_RED RB3 /* Set red LED pin. */

void main() {
    CMCON = 0x07; /* Disable comparator. */
    TRISB = 0b11110101; /* Switches: RB<2:0>; LEDs: RB<3:1>. */
    LED_GREEN = 0; /* Turn off green LED. */
    LED_RED = 0; /* Turn off red LED. */
    /* Main loop. */
    for (;;) {
        /* On/off green LED. */
        B4X_SW_CLICK(SW1) {
            B4X_SW_DEBOUNCE(SW1);
            LED_GREEN = !LED_GREEN;
        }
        /* On/off red LED. */
        B4X_SW_nCLICK(SW2) {
            B4X_SW_DEBOUNCE(SW2);
            B4X_SW_TOGGLE(LED_RED);
        }
    }
}
```

## Notice

**(it is under development, however, we are working hardly to release new features :wink:)**
