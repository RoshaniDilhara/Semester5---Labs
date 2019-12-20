#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 1000

int main() {

  DDRD &= ~(1<<2); //PD2 (INT 0) is input // DDRD &= ~(1<<2)
  DDRB |= (1<<0); //PB0 is output // DDRB |= (1<<0)

  sei(); // enable global interrupt

  EIMSK |= (1<<INT0); //enable external interrupt for int0

  //set for rising edge detection
  EICRA |= (1<<ISC01);
  EICRA |= (1<<ISC00);

  while (1) {
  }

return 0;
}

ISR(INT0_vect){

  PORTB &= ~(1<<0);
  _delay_ms(BLINK_DELAY_MS);
  PORTB |= (1<<0);

}


// #include <avr/io.h>
// #include <avr/interrupt.h>
// #include <util/delay.h>
//
// #define BLINK_DELAY_MS 1000
//
// int main(){
//
//     DDRD &= ~(1<<2); //PD2 (INT0) is input
//     DDRB |= ~(1<<0); //PB0 is output
//
//     EICRA |= (1<<ISC01); //set for rising edge detection
//     EICRA |= (1<<ISC00); //set for rising edge detection
//
//     sei(); //enable global interrupts
//
//     EIMSK |= (1<<INT0); //enable external interrupt for INT0
//
//     while (1) {
//
//     }
// return 0;
// }
//
// ISR(INT0_vect){
//   PORTB &= ~(1<<0);
//   _delay_ms(BLINK_DELAY_MS);
//   PORTB |= (1<<0);
// }
