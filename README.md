# ATmega16 LED Blink (CodeVisionAVR)

Blinks an LED on pin **PA0** once per second (500 ms on, 500 ms off).

## Hardware

```
PA0 ----[ 330 ohm ]----|>|---- GND
                        LED
```

PA0 sources the LED current, so keep the resistor around 220-330 ohm.

## How the code works

- `#include <mega16.h>` brings in the ATmega16 register names
  (`DDRA`, `PORTA`, `PA0`, ...).
- `#include <delay.h>` provides `delay_ms()`.
- `DDRA |= (1 << PA0);` sets bit 0 of the data-direction register,
  making PA0 an output.
- `PORTA |= (1 << PA0);` writes a 1 to PA0, driving it high -> LED on.
- `PORTA &= ~(1 << PA0);` writes a 0 to PA0, driving it low -> LED off.
- The `while (1)` loop repeats this forever.

## Compile with CodeVisionAVR

1. `File > New > Project` and choose **ATmega16** as the chip.
2. When asked, say **No** to the CodeWizard, then add `main.c` to the project.
3. Set the clock: `Project > Configure > C Compiler > Clock = 8.000000 MHz`
   (must match the real clock, or `delay_ms()` will be wrong).
4. `Project > Build All` (or press `F7`) to produce `main.hex`.

## Flash

Use CodeVisionAVR's built-in programmer (`Tools > Chip Programmer`) with
your USBasp/ISP programmer, or with `avrdude`:

```sh
avrdude -c usbasp -p m16 -U flash:w:main.hex:i
```

Make sure the ATmega16 fuses match the 8 MHz clock.

## Note for avr-gcc users

`mega16.h` and `delay.h` belong to CodeVisionAVR; avr-gcc does not ship
them. With avr-gcc the same program looks like this:

```c
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRA |= (1 << PA0);
    while (1) {
        PORTA |= (1 << PA0);
        _delay_ms(500);
        PORTA &= ~(1 << PA0);
        _delay_ms(500);
    }
}
```
