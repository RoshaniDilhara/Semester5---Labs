#include <avr/io.h>

int main(void){

DDRC &= (1<<1); // PC1 input (A1) - LDR connect
DDRD |= (1<<0); //PD0 Output

ADMUX |= (1<<REFS0);//select reference voltage(here, AVCC)
ADMUX |= (1<<MUX0); // ADC1 input channel
ADMUX |= (1<<ADLAR); // left justified
ADCSRA |= (1<<ADEN); //enable ADC1
ADCSRA = ADCSRA | (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);//<200kHz (125kHz)

while(1){

  ADCSRA |= (1<<ADSC); // start conversion

  while((ADCSRA & 0b00010000) == 0){} // wait till the conversion end

  ADCSRA |= (1<<ADIF); // clear the flag bit

    if(ADCH < 500){
      PORTD |= (1<<0);
    }else{
      PORTD &= ~(1<<0);
    }

}

}
