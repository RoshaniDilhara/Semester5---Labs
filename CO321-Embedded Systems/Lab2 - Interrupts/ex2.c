#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BLINK_DELAY 1000

int main(){

DDRD &= ~(1<<2); //PD2 input
DDRB |= (1<<0); //PB0 output

//enabling global interrupts
sei();

//enabling external interrupts
EIMSK |= (1<<INT0);

//falling edge
EICRA |= (1<<ISC01);
EICRA &= ~(1<<ISC00);

while (1) {
  /* code */
}
return 0;
}

ISR(INT0_vect){

PORTB ^= (1<<0);

}
