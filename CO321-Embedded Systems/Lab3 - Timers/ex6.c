#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BLINK 1000

int count = 0;

int main(){

  DDRB |= (1<<5);

  sei();
  TIMSK0 = 0x01;
  TCCR0A = 0x00;
  TCCR0B = 0x05;
  TCNT0 = 231;

  while (1) {
    /* code */
  }

}

ISR(TIMER0_OVF_vect){

count = count + 1;
if (count == 7) {
  PORTB |= (1<<5);
  _delay_ms(BLINK);
  PORTB &= ~(1<<5);
  _delay_ms(BLINK);
  TCNT0 = 231;
  count = 0;
}


}
