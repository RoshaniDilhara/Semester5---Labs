#include <avr/io.h>
#include <String.h>

void usart_Init()
{
    /*Set baud rate */
    UBRR0 = 103;

    /*Enable receiver and transmitter */
    UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
    /* Set frame format: 8data, 1stop bit and no parity */
    UCSR0C &= ~(1<<USBS0) ; //1 stop bit
    UCSR0C |= (1<<UCSZ00) | (1<<UCSZ01); // 8 bit
    UCSR0C &= ~(1<<UPM01); //no parity
    UCSR0C &= ~(1<<UPM00); //no parity

}

void usart_send( unsigned char data )
{
    /* Wait for empty transmit buffer */
    while ( !( UCSR0A & (1<<UDRE0)) );
    /* Put data into buffer, sends the data */
    UDR0 = data;
}

unsigned char usart_receive( void )
{
    /* Wait for data to be received */
    while ( !(UCSR0A & (1<<RXC0)) );
    /* Get and return received data from buffer */
    return UDR0;
}


int main(){

  usart_Init();

  char ch;
  int j;
  char str_message;
  int key = 3;

  while (1) {

  str_message = usart_receive();

  // for(j = 0; str_message != '\0'; ++j){

    ch = str_message;

    if(ch >= 'a' && ch <= 'z'){
      ch = ch + key;
      if(ch > 'z'){
        ch = ch - 'z' + 'a' - 1;
      }
      str_message = ch;
    }

    else if(ch >= 'A' && ch <= 'Z'){
      ch = ch + key;
      if(ch > 'Z'){
        ch = ch - 'Z' + 'A' - 1;
      }

      str_message = ch;
    }

  usart_send(str_message);

//  }




}

}
