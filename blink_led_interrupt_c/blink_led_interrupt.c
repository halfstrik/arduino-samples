#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define PRESCALER 10 /* 10 bits - 1024 */
#define CLOCK_RATE 15998976

#define COUNTER_VALUE (CLOCK_RATE >> PRESCALER) /* Routhly number of ticks in a second */

/* TIMER1 compare interrupt service routine
   fires when counter value matches OCR1A */
ISR(TIMER1_COMPA_vect) {
    PORTB ^= _BV(PORTB5);
}

int main (void) {
    /* Set to one the fifth bit of DDRB to one
    ** Set digital pin 13 to output mode */
    DDRB |= _BV(DDB5);

    OCR1A = COUNTER_VALUE;  /* The number of clock ticks to wait */
    TCCR1A = 0x00;
    TCCR1B = (1 << WGM12); /* CTC Mode - compare to OCR1A */
    TCCR1B = (1 << CS10) | (1 << CS12); /* Set prescaler to 1024 */
    TIMSK1 |= (1 << OCIE1A);

    sei(); /* Enable interrupts */

    while(1) {
        /* Do something useful */
    }

    return 0;
}
