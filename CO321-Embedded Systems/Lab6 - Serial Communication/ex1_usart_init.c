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
