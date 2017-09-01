# Brook4-XC8

Brook4-XC8 is a small XC8 library for development with 8-bit PIC MCUs.

# LCD driver

## Circuit

![LCD driver circuit](https://raw.githubusercontent.com/brook-dev/brook4xc8/master/examples/brook4xc8-lcd.X/circuit.png)

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
    for (;;); /* main loop. */
}
```

## Notice

(it is under development, however, we are working hardly to release new features)
