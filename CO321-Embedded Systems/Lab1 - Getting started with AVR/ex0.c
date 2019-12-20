#include<avr/io.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 1000

int main(void){

DDRB = 0xff; //PORTB output

int i,j;

while (1) {

  for (i = 0; i < 3; i++) {
    PORTB = PORTB | (1<<i); /* set pin 5 high to turn led on */
  }
  _delay_ms(BLINK_DELAY_MS);


for (i = 0; i < 3; i++) {
  PORTB = PORTB &~(1<<i); /* set low to turn led off */
}
_delay_ms(BLINK_DELAY_MS);




}


}
