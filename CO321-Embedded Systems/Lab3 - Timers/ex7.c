#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// #define BLINK 1000

int count = 0;

int main(){

  DDRB |= ((1<<5) | (1<<4));

  sei();
  TIMSK0 = 0x01;
  TCCR0A = 0x00;
  TCCR0B = 0x05;
  TCNT0 = 243;

  sei();
  TIMSK1 = 0x01;
  TCCR1A = 0x00;
  TCCR1B = 0x04;
  TCNT1 = 34286;

  while (1) {
    /* code */
  }

}

ISR(TIMER0_OVF_vect){

count = count + 1;
if (count == 4) {
  PORTB = PORTB ^ (1<<5);
  TCNT0 = 243;
  count = 0;
}
}

ISR(TIMER1_OVF_vect){
	PORTB = PORTB ^ (1<<4);
	TCNT1 = 34286;
}
