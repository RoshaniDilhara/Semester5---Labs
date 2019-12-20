#include <avr/io.h>
#include <util/delay.h>

//1 second time delay
void delay_timer1(){
	TCNT1 = 3036; //init value of the timer

	TCCR1A = 0x00;
	TCCR1B = 0x04; //normal mode and 1/256 prescaler

	while((TIFR1 & 0x01) == 0); //wait till timer 1 overflows and flag bit set

	TCCR1A = 0x00;
	TCCR1B = 0x00; //stops the clock

	TIFR1 = 0x01; //clear flag bit
}

int main(){

	OCR0A = 220; // duty cycle (86%)

	TCCR0A = (1<<WGM00) | (1<<WGM01); // Fast PWM (TOP = OxFF)

	TCCR0A |= (1 << COM0A1); // non-inverting mode Fast PWM

	DDRD |= (1<<6); //PD6 output

	while(1){

		//change the prescaler (8-Highest frequency,64,256,1024 / 2(7812.5),3,4,5(61))
		int n;
		for(n = 5;n > 1;n--){
			TCCR0B = n;
			delay_timer1();
		}
	}

	return 0;
}
