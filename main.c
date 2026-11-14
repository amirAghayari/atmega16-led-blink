/*
 * main.c - Blink an LED on PA0 of an ATmega16
 *
 * Compiler: CodeVisionAVR (uses mega16.h and delay.h)
 *
 * The LED is connected between PA0 and GND through a resistor
 * (e.g. 330 ohm). PA0 high = LED on, PA0 low = LED off.
 *
 * Clock: 8 MHz. Set this in CodeVisionAVR under
 * Project > Configure > C Compiler > Clock = 8.000000 MHz,
 * or delay_ms() will produce the wrong timing.
 */

#include <mega16.h>   /* ATmega16 register definitions (DDRA, PORTA, ...) */
#include <delay.h>    /* delay_ms() and delay_us() */

void main(void)
{
    /* Configure PA0 as an output. A 1 in DDRA makes that pin an output. */
    DDRA |= (1 << PA0);

    while (1)
    {
        PORTA |= (1 << PA0);    /* Set PA0 high: LED ON  */
        delay_ms(500);          /* Wait 500 milliseconds  */

        PORTA &= ~(1 << PA0);   /* Set PA0 low:  LED OFF */
        delay_ms(500);          /* Wait 500 milliseconds  */
    }
}
