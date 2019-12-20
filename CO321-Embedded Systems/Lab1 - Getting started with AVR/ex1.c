#include<avr/io.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 20

int main(void){

DDRB = 0xff; //PORTB output

int i,j;

while (1) {

  for (i = 0; i <= 5; i++) {
    PORTB = PORTB | (1<<i); /* set pin 5 high to turn led on */
    _delay_ms(BLINK_DELAY_MS);
    PORTB = PORTB &~(1<<i); /* set pin 5 low to turn led off */
    _delay_ms(BLINK_DELAY_MS);
  }

  for (j = i-1; j >= 1; j--) {
    PORTB = PORTB | (1<<j);/* set pin 5 high to turn led on */
    _delay_ms(BLINK_DELAY_MS);
    PORTB = PORTB &~(1<<j); /* set pin 5 low to turn led off */
    _delay_ms(BLINK_DELAY_MS);

  }

}


}
