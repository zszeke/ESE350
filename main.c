/*
 * Lab 2 ESE350.c
 *
 * Created: 1/28/2022 11:17:49 AM
 * Author : zszeke
 */ 
#define F_CPU 16000000UL
#define BAUD_RATE 9600
#define BAUD_PRESCALER (((F_CPU / (BAUD_RATE * 16UL))) - 1)

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "uart.h"
#include <string.h>

volatile int edge = 0;
volatile int edge2 = 65535;
volatile int width = 0;
volatile int overflow = 0;
volatile int overflow2 = 0;
volatile int isSpace = 0;

char String[100];
char alpha[100];

void Initialize() {
	DDRB &= ~(1<<DDB0); // set PB0 as input
	DDRB |= (1<<DDB1);
	DDRB |= (1<<DDB2);
	DDRB |= (1<<DDB5); // set PB5 as output
	PORTB |= (1<<PORTB0); // enable pull up on PB0
	
	//PORTB |= (1<<PORTB5); // set built-in led ON
	
	TCCR1B &= ~(1<<ICES1); // set 0 in ICES1 for recording falling edge
	TIFR1 |= (1<<ICF1); // clear interrupt flag
	TIMSK1 |= (1<<ICIE1); // set 1 in ICIE1 to enable IC interrupt
	TIMSK1 |= (1<<TOIE1); // set 1 in TOIE1 to enable overflow interrupt
	
	// enable clock 1(1024 prescalar)
	TCCR1A &= ~(1<<WGM10);
	TCCR1A &= ~(1<<WGM11);
	TCCR1B |= (1<<CS10);
	TCCR1B &= ~(1<<CS11);
	TCCR1B |= (1<<CS12);
	
	// enable timer 0 for space delay w/ 1024 prescalar, normal mode
	TCCR0B |= (1<<CS00);
	TCCR0B &= ~(1<<CS01);
	TCCR0B |= (1<<CS02);
	TCCR0B &= ~(1<<WGM00);
	TCCR0B &= ~(1<<WGM01);
	TCCR0B &= ~(1<<WGM02);
	
	// enable timer 0 overflow interrupt
	TIMSK0 |= (1<<TOIE0);
	
	sei();
}

int main(void) {
	UART_init(BAUD_PRESCALER);
	Initialize();	
    while (1) {
		int ledWidth = (TCNT1 - edge2) / 15.625 + overflow2 * 4194;
		if (ledWidth > 75) {
			PORTB &= ~(1<<PORTB1);
			PORTB &= ~(1<<PORTB2);
			overflow2 = 0;
		}
    }
}
ISR(TIMER1_OVF_vect) {
	overflow2++;
}

// count overflows
ISR(TIMER0_OVF_vect) {
	overflow++;
	if (overflow >= 610) {
		overflow = 0;
		if (isSpace == 1) {
			sprintf(String, " string: %s \n", alpha);
			UART_putstring(String);
			// check for what string we made
			if (strcmp(alpha, "dotdash") == 0) {
				sprintf(String, "char: A");
			} else if (strcmp(alpha, "dashdotdotdot") == 0) {
				sprintf(String, "char: B");
			} else if (strcmp(alpha, "dashdotdashdot") == 0) {
				sprintf(String, "char: C");
			} else if (strcmp(alpha, "dashdotdot") == 0) {
				sprintf(String, "char: D");
			}
			else if (strcmp(alpha, "dot") == 0) {
				sprintf(String, "char: E");
			}
			else if (strcmp(alpha, "dotdotdashdot") == 0) {
				sprintf(String, "char: F");
			}
			else if (strcmp(alpha, "dashdashdot") == 0) {
				sprintf(String, "char: G");
			}
			else if (strcmp(alpha, "dotdotdotdot") == 0) {
				sprintf(String, "char: H");
			}
			else if (strcmp(alpha, "dotdot") == 0) {
				sprintf(String, "char: I");
			}
			else if (strcmp(alpha, "dotdashdashdash") == 0) {
				sprintf(String, "char: J");
			}
			else if (strcmp(alpha, "dashdotdash") == 0) {
				sprintf(String, "char: K");
			}
			else if (strcmp(alpha, "dotdashdotdot") == 0) {
				sprintf(String, "char: L");
			}
			else if (strcmp(alpha, "dashdash") == 0) {
				sprintf(String, "char: M");
			}
			else if (strcmp(alpha, "dashdot") == 0) {
				sprintf(String, "char: N");
			}
			else if (strcmp(alpha, "dashdashdash") == 0) {
				sprintf(String, "char: O");
			}
			else if (strcmp(alpha, "dotdashdashdot") == 0) {
				sprintf(String, "char: P");
			}
			else if (strcmp(alpha, "dashdashdotdash") == 0) {
				sprintf(String, "char: Q");
			}
			else if (strcmp(alpha, "dotdashdot") == 0) {
				sprintf(String, "char: R");
			}
			else if (strcmp(alpha, "dotdotdot") == 0) {
				sprintf(String, "char: S");
			}
			else if (strcmp(alpha, "dash") == 0) {
				sprintf(String, "char: T");
			}
			else if (strcmp(alpha, "dotdotdash") == 0) {
				sprintf(String, "char: U");
			}
			else if (strcmp(alpha, "dotdotdotdash") == 0) {
				sprintf(String, "char: V");
			}
			else if (strcmp(alpha, "dotdashdash") == 0) {
				sprintf(String, "char: W");
			}
			else if (strcmp(alpha, "dashdotdotdash") == 0) {
				sprintf(String, "char: X");
			}
			else if (strcmp(alpha, "dashdotdashdash") == 0) {
				sprintf(String, "char: Y");
			}
			else if (strcmp(alpha, "dashdashdotdot") == 0) {
				sprintf(String, "char: Z");
			}
			else if (strcmp(alpha, "dotdashdashdashdash") == 0) {
				sprintf(String, "char: 1");
			}
			else if (strcmp(alpha, "dotdotdashdashdash") == 0) {
				sprintf(String, "char: 2");
			}
			else if (strcmp(alpha, "dotdotdotdashdash") == 0) {
				sprintf(String, "char: 3");
			}
			else if (strcmp(alpha, "dotdotdotdotdash") == 0) {
				sprintf(String, "char: 4");
			}
			else if (strcmp(alpha, "dotdotdotdotdot") == 0) {
				sprintf(String, "char: 5");
			}
			else if (strcmp(alpha, "dashdotdotdotdot") == 0) {
				sprintf(String, "char: 6");
			}
			else if (strcmp(alpha, "dashdashdotdotdot") == 0) {
				sprintf(String, "char: 7");
			}
			else if (strcmp(alpha, "dashdashdashdotdot") == 0) {
				sprintf(String, "char: 8");
			}
			else if (strcmp(alpha, "dashdashdashdashdot") == 0) {
				sprintf(String, "char: 9");
			}
			else if (strcmp(alpha, "dashdashdashdashdash") == 0) {
				sprintf(String, "char: 0");
			}
			UART_putstring(String);
			// reset current character array
			alpha[0] = '\0';
			isSpace = 0;
		}
	}
}

ISR(TIMER1_CAPT_vect) {;	
	// if the button is pressed turn on LED
	if (!(PINB & (1<<PINB0)) && !(TCCR1B & (1<<ICES1))) {
		// check to see if space should be printed
		PORTB |= (1<<PORTB5);
		TCCR1B |= (1<<ICES1);
		// capture time when button is pressed
		edge = ICR1;
	} else if (PINB & (1<<PINB0) && (TCCR1B & (1<<ICES1))) {
		PORTB &= ~(1<<PORTB5);
		TCCR1B &= ~(1<<ICES1);
		// capture time when button is unpressed
		width = (ICR1 - edge) / 15.625;
		if (width > 30 && width <= 200) {
			sprintf(String, "dot %d \n", width);
			UART_putstring(String);
			PORTB |= (1<<PORTB1);
			strcat(alpha, "dot");
		} else if (width > 200 && width <= 1000) {
			sprintf(String, "dash %d \n", width);
			UART_putstring(String);
			PORTB |= (1<<PORTB2);
			strcat(alpha, "dash");	
		}
		edge2 = ICR1;
		overflow = 0;
		isSpace = 1;
	}
}
