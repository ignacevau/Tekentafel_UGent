#ifndef _DW_UTILS_
#define _DW_UTILS_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <DwengoUtil.h>
#include <IK.h>



float offset1 = +0.0f;
float offset2 = -0.11f;

/*
0: periode afwachten
1: eerste delay
2: tweede delay
3: derde delay
*/
volatile int motor_state = 1;


// Timer1 Compare A interrupt
ISR(TIMER1_COMPA_vect) {
    switch(motor_state) {
        case 0:
            // Motor 3 uit
            PORTF &= ~(1<<PF0);
            
            // pas OCR-register aan zodat de tijd tot volgende interrupt de 20 ms (periode) volmaakt
            setOCR(PERIODE-((delay1+offset1)+(delay2+offset2) + delay3));
            motor_state = 1;

            // maken het weer mogelijk om de volgende hoek te berekenen(zie DRAW-functies)
            period_started = 0;
            break;
        case 1:
            // motor 1 aan
            PORTC |= (1<<PC0);

            // pas OCR-register aan zodat de tijd tot volgende interrupt de lengte delay 1 bedraagt
            setOCR(delay1+offset1);
            motor_state = 2;
            break;
        case 2:
            // motor 1 uit
            PORTC &= ~(1<<PC0);

            // motor 2 aan
            PORTC |= (1<<PC1);

            // pas OCR-register aan zodat de tijd tot volgende interrupt de lengte delay 2 bedraagt
            setOCR(delay2+offset2);
            motor_state = 3;
            break;
        case 3:
            // Motor 3 aan
            PORTF |= 1<<PF0;
            // motor 2 uit
            PORTC &= ~(1<<PC1);
            
            // pas OCR-register aan zodat de tijd tot volgende interrupt de lengte delay 3 bedraagt
            setOCR(delay3);
            motor_state = 0;
            break;
    }
}


void setRegisters() {

    DDRA |= 0xFF;  // Leds als output
    PORTA = 0x00;  // Leds uit
    // PORTA = 0xFF;    // Leds aan


    // Zet servo's 1 en 2 (motoren van tekenarm) op output
    DDRC |= (1<<PC0) | (1<<PC1);
    // Zet servo's uit (geen puls)
    PORTC &= ~(1<<PC0) & ~(1<<PC1);

    // Zet servo 3 (motor van stift) op output
    DDRF |= (1<<PF0);
    // Zet servo 3 uit (geen puls)
    PORTF &= ~(1<<PF0);


    SREG |= (1<<SREG_I); // Zet global interrupts aan
    
    // TIMER INTERRUPT
    TIMSK1 |= (1<<OCIE1A);  // Gebruik Output Compare A Match-interrupt

    // Zet mode op CNC
    TCCR1A &= ~_BV(WGM10); // WGM10 moet 0 zijn
    TCCR1A &= ~_BV(WGM11); // WGM11 moet 0 zijn
    TCCR1B |= _BV(WGM12);  // WGM12 moet 1 zijn
    TCCR1B &= ~_BV(WGM13); // WGM13 moet 0 zijn

    // Zet prescaling op clk
    /*
    clock frequency is 16MHz
    scaling of 1 --> 16 MHz
    */
    TCCR1B &= ~_BV(CS12);
    TCCR1B &= ~_BV(CS10);
    TCCR1B |= _BV(CS11);


    // BLUETOOTH
    // Asynchronous USART
    UCSR1C &= ~_BV(UMSEL11);
    UCSR1C &= ~_BV(UMSEL10);

    // Disable transfer rate doubling, only valid for asynchronous operation
    UCSR1A &= ~_BV(U2X1);

    // Set the baud rate to 9600 bps (only baud rate that works for android)
    /*
    UBRRn = f_osc / (16*baudrate) - 1
    UBBR1 = 16MHz / (16*9600) - 1 = 103
    */
    UBRR1H = (unsigned char)(103>>8);
    UBRR1L = (unsigned char)103;

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
}

// Deze functie zet het OCR-register op een bepaalde waarde in functie van de prescaling (zie setRegisters) en van de delays (zie ISR)
void setOCR(float delay) {
    OCR1A = (int)(2000.0f*delay);
}
#endif