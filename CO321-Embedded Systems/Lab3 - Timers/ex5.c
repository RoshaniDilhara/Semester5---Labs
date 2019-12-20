#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void delay_timer0(){

  TCNT0 = 131;

  TCCR0A =  0x00;
  TCCR0B = 0x04;

  while((TIFR0&0x01)==0);

  TCCR0A = 0x00;
  TCCR0B = 0x00;

  TIFR0 = 0x01;

}

int main() {

  int i,j,k;

  DDRB  = 0xff;

  TIMSK1 = 0x01;
  TCNT1 = 3036;

  sei();

  TCCR1A = 0x00; 	// normal mode
	TCCR1B = 0x04;  //normal mode and 1/256 prescaler

  while (1) {
      for (i = 0; i <=4 ; i++) {
        PORTB ^= (1<<i);
        for (k = 0; k < 250; k++) {
          delay_timer0();
        }
      }

      for (j = i-1; j > 0; j--) {
        PORTB ^= (1<<j);
        for (k = 0; k < 250; k++) {
          delay_timer0();
        }
      }
  }


  return 0;
}


ISR(TIMER1_OVF_vect){
	PORTB = PORTB ^ (1<<5);
	TCNT1 = 3036;	// Load timer/counter 1 register
}
