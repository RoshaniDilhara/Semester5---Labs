#include <avr/io.h>

int main(){

    DDRD |= (1<<6);

    TCCR0A = 131;
    TCCR0B = 3;
    TCNT0 = 0;
    OCR0A = 127;

    while(1){

    }
return 0;

}
