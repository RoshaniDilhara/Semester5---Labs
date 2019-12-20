#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 1000

int count = 0;

int main() {

  DDRD &= ~(1<<2); //PD2 (INT 0) is input // DDRD &= ~(1<<2)
  DDRB = 0b00111111;

  //set for falling edge detection
  EICRA |= (1<<ISC01);
  EICRA &= ~(1<<ISC00);

  sei(); // enable global interrupt

  EIMSK |= (1<<INT0); //enable external interrupt for int0



  while (1) {
  }

return 0;
}

ISR(INT0_vect){
  count += 1;
  PORTB = count;

  if (count > 127) {
    count = 0;
  }
//  _delay_ms(BLINK_DELAY_MS);


}
