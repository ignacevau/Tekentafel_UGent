#include <avr/io.h>
#include <Bluetooth/Bluetooth.h>


unsigned char Bluetooth_Receive() {
    // Wait until there is data in the buffer
    while (!(UCSR1A & (1<<RXC1)));
    
    // Return data from the buffer
    return UDR1;
}

void FlushBuffer() {
    unsigned char dummy;
    while ( UCSR1A & (1<<RXC1) ) {
        dummy = UDR1;
    }
}