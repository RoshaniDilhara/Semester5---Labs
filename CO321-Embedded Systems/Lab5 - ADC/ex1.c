#include <avr/io.h>


int main() {

DDRC &= ~(1<<1); //input PC1
DDRD = 0xff; //portD all bits output

ADMUX |= (1<< MUX0) ;//selects the analog input channel ADC1 (0001)
ADCSRA |= (1<<ADEN); //enable ADC1
ADCSRA = ADCSRA | (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);//<200kHz
ADMUX |= (1<<REFS0);//select reference voltage(here, AVCC)
// ADCSRA = (1<<ADIF); //Wait for the conversion to be completed by polling
ADMUX |= (1<<ADLAR); //left justified

while(1){

  ADCSRA |= (1<<ADSC); //activate start conversation

  while((ADCSRA>>4)&0x01==0); //wait till ADIF(flag) = 1

    ADCSRA |= (1<<ADIF); //clear the flag bit(ADIF bit = 1)

    PORTD = ADCH; //display the ADCH register value of the input voltage
    // ADCSRA |= (1<<ADIF); //ADIF bit = 1


}


  return 0;
}
