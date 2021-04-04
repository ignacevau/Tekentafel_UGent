#ifndef _Bluetooth_
#define _Bluetooth_

#include <avr/io.h>

unsigned char Bluetooth_Receive() {
    // Wacht tot er data is
    while (!(UCSR1A & (1<<RXC1)));
    
    // Return data uit buffer
    return UDR1;
}

// Maak de data buffer leeg -> verwijdert ongelezen data!
void FlushBuffer() {
    unsigned char dummy;
    while ( UCSR1A & (1<<RXC1) ) {
        dummy = UDR1;
    }
}
#endif