#include <avr/eeprom.h>
#include <avr/io.h>
#include <String.h>

unsigned char EEMEM addr;

int main(void){

    // usart_Init();
    //
    // // char ch;
    // unsigned int uiAddress;
    // // char str_message;
    //
    // // char ar3[]= "Roshani E/15/208\n";
    //
    // unsigned char ucData = usart_receive();
    //
    // // for(j = 0; j<strlen(str_message); j++){
    //   // eeprom_write_byte (j, str_message[j]);
    //   EEPROMwrite (uiAddress, ucData);
    // // }



    unsigned char Disp = 0;
    while (Disp+1) {
      Disp = Disp++;
      eeprom_write_byte (&addr, Disp);
      Disp = eeprom_read_byte(&addr);
      // printf("%c\n",Disp);
    }

}

void EEPROMwrite(unsigned int uiAddress, unsigned char ucData){

    /* Wait for completion of previous write */
    while(EECR & (1<<EEPE));
    /* Set up address and Data Registers */
    EEAR = uiAddress;
    EEDR = ucData;
    /* Write logical one to EEMPE */
    EECR |= (1<<EEMPE);
    /* Start eeprom write by setting EEPE */
    EECR |= (1<<EEPE);
}


unsigned char EEPROMread(unsigned int uiAddress){

    /* Wait for completion of previous write */
    while(EECR & (1<<EEPE));
    /* Set up address register */
    EEAR = uiAddress;
    /* Start eeprom read by writing EERE */
    EECR |= (1<<EERE);
    /* Return data from Data Register */
    return EEDR;
}


// void usart_Init(){
//     /*Set baud rate */
//     UBRR0 = 103;
//
//     /*Enable receiver and transmitter */
//     UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
//     /* Set frame format: 8data, 1stop bit and no parity */
//     UCSR0C &= ~(1<<USBS0) ; //1 stop bit
//     UCSR0C |= (1<<UCSZ00) | (1<<UCSZ01); // 8 bit
//     UCSR0C &= ~(1<<UPM01); //no parity
//     UCSR0C &= ~(1<<UPM00); //no parity
//
// }
//
// unsigned char usart_receive(){
//     /* Wait for data to be received */
//     while ( !(UCSR0A & (1<<RXC0)) );
//     /* Get and return received data from buffer */
//     return UDR0;
// }
