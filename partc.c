/*
 * Lab 2 ESE350.c
 *
 * Created: 1/28/2022 11:17:49 AM
 * Author : zszeke
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <uart.h>

void Initialize() {
	DDRB &= ~(1<<DDB0); // set PB0 as input
	DDRB |= (1<<DDB5); // set PB5 as output
	PORTB |= (1<<PORTB0); // enable pull up on PB0
	
	//PORTB |= (1<<PORTB5); // set built-in led ON
	
	TCCR1B &= ~(1<<ICES1); // set 0 in ICES1 for recording falling edge
	TIFR1 |= (1<<ICF1); // clear interrupt flag
	TIMSK1 |= (1<<ICIE1); // set 1 in ICIE1 to enable IC interrupt
	
	// enable prescalar clock (CLK/256)
	TCCR1B &= ~(1<<CS10);
	TCCR1B &= ~(1<<CS11);
	TCCR1B |= (1<<CS12);
	
	sei();
}

int main(void) {
	Initialize();	
    while (1) {
    }
}

ISR(TIMER1_CAPT_vect) {
	// if the button is pressed turn on LED
	if (!(PINB & (1<<PINB0))) {
		PORTB |= (1<<PORTB5);
		TCCR1B |= (1<<ICES1);
	} else {
		PORTB &= ~(1<<PORTB5);
		TCCR1B &= ~(1<<ICES1);
	}
}
