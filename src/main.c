#include <Shapes.h>
#include <DwengoUtil.h>
#include <avr/io.h>
#include <util/delay.h>

unsigned char USART_Receive(void) {
    /* Wait for data to be received */
    while ( !(UCSR1A & (1<<RXC1)) ) {

    }
    /* Get and return received data from buffer */
    return UDR1;
}

int main(void)
{
    // zet registers goed:
    setRegisters();
    setOCR(PERIODE);

    // BLUETOOTH
    // Asynchronous USART
    UCSR1C &= ~_BV(UMSEL11);
    UCSR1C &= ~_BV(UMSEL10);

    // Disable transfer rate doubling, only valid for asynchronous operation
    UCSR1A &= ~_BV(U2X1);

    // Set the baud rate to 57600 bps (default android bluetooth)
    /*
    UBRRn = f_osc / (2*baudrate) - 1
    UBBR1 = 16MHz / (2*57600) - 1 = 138
    */
    UBRR1H = (unsigned char)(138>>8);
    UBRR1L = (unsigned char)138;

    // Set frame format: data bits = 8
    UCSR1C |= _BV(UCSZ10);
    UCSR1C |= _BV(UCSZ11);
    UCSR1B &= ~_BV(UCSZ12);

    // Set frame format: parity bit disabled
    UCSR1C &= ~_BV(UPM11);
    UCSR1C &= ~_BV(UPM10);

    // Set frame format: stop bits = 1
    UCSR1C &= ~_BV(USBS1);

    // Enable data receiving
    UCSR1B |= _BV(RXEN1);

    unsigned char data = USART_Receive();
    if (data != 0x00) {
        PORTA |= data;
    }
    else {
        PORTA |= _BV(0);
    }

    while (1)
    {
        // drawPartialCircle(6.0f, 6.0f, True, 1.0f, 4.5f, 4.5f);
    }

    return 0;
}