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


int main(void){

  usart_Init();

  char ar1[]= "Dinithi E/15/119\n";
  char ar2[]= "Dulanjali E/15/202\n";
  char ar3[]= "Roshani E/15/208\n";

    int i;

    for(i = 0; i<strlen(ar1); i++){
      usart_send(ar1[i]);
    }

    for(i = 0; i<strlen(ar2); i++){
      usart_send(ar2[i]);
    }

    for(i = 0; i<strlen(ar3); i++){
      usart_send(ar3[i]);
    }

}
