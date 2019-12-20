#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BLINK_DELAY 1000

int main(){

  int count = 0;

  DDRB |= 0b00111111; //PORTB is output
  DDRD & ~(1<<7);

  while (1) {
    if(PIND & (1<<7)){
      count += 1;
      PORTB = count;
      if (count > 127) {
        count = 0;
      }
      _delay_ms(BLINK_DELAY);
    //  PORTB = 0x00;
    }
  }
return 0;
}
