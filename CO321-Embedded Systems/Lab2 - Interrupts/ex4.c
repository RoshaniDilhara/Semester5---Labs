#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BLINK_DELAY 1000

int count=-1;

int main() {

DDRB = 0xff;

//INT0
DDRD &= ~(1<<2);
DDRD &= ~(1<<3);

EICRA |= (1<<ISC01);
EICRA &= ~(1<<ISC00);

sei();

EIMSK |= (1<<INT0);

//INT1
DDRD &= ~(1<<3);

EICRA |= (1<<ISC11);
EICRA &= ~(1<<ISC10);

sei();

EIMSK |= (1<<INT1);

 // PORTB= 0b00000000;

while (1) {
  /* code */
}

  return 0;
}

ISR(INT0_vect){


	_delay_ms(BLINK_DELAY);
	PORTB =PORTB <<1;

}

ISR(INT1_vect){


	_delay_ms(BLINK_DELAY);
	PORTB =PORTB <<1;
	PORTB |= (1<<0);

}
