#include <avr/io.h>
#include <avr/interrupt.h>
#include <DwengoUtil.h>
#include <IK.h>


// Offset for delay 1
float offset1 = +0.0f;
// Offset for delay 2
float offset2 = -0.07f;

/**
 * @brief Describes the state of the interrupt-delay routine
 * 
 * @tparam 0: Wait for the end of the period
 * @tparam 1: Waiting for delay 1
 * @tparam 2: Waiting for delay 2
 * @tparam 3: Waiting for delay 3
 */
volatile int motor_state = 1;


// Timer1 Compare A interrupt
ISR(TIMER1_COMPA_vect) {
    switch(motor_state) {
        case 0:
            // Servo 3 low
            PORTF &= ~(1<<PF0);
            
            // Set OCR-register such that the period of 20 ms is waited out
            setOCR(PERIODE-((delay1+offset1)+(delay2+offset2) + delay3));
            motor_state = 1;

            // Mark end of the period
            period_started = 0;
            break;
        case 1:
            // Servo 1 high
            PORTC |= (1<<PC0);

            // Set OCR-register such that the time until the next interrupt is delay 1
            setOCR(delay1+offset1);
            motor_state = 2;
            break;
        case 2:
            // Servo 1 low
            PORTC &= ~(1<<PC0);

            // Servo 2 high
            PORTC |= (1<<PC1);

            // Set OCR-register such that the time until the next interrupt is delay 2
            setOCR(delay2+offset2);
            motor_state = 3;
            break;
        case 3:
            // Servo 2 low
            PORTC &= ~(1<<PC1);

            // Servo 3 high
            PORTF |= 1<<PF0;
            
            // Set OCR-register such that the time until the next interrupt is delay 3
            setOCR(delay3);
            motor_state = 0;
            break;
    }
}


void setRegisters() {
    SREG |= (1<<SREG_I); // Enable global interrupts

    // SERVOS
#pragma region SERVOS
    // Set servos 1 and 2 (control the drawing arm) to output
    DDRC |= (1<<PC0) | (1<<PC1);
    // Set servos to low (no pulse)
    PORTC &= ~(1<<PC0) & ~(1<<PC1);

    // Set servo 3 (controls the pencil) to output
    DDRF |= (1<<PF0);
    // Set servo 3 to low (no pulse)
    PORTF &= ~(1<<PF0);
#pragma endregion /SERVOS

    
#pragma region TIMER_INTERRUPT
    TIMSK1 |= (1<<OCIE1A);  // Use Output Compare A Match-interrupt

    // Set mode to CNC
    TCCR1A &= ~_BV(WGM10);
    TCCR1A &= ~_BV(WGM11);
    TCCR1B |= _BV(WGM12);
    TCCR1B &= ~_BV(WGM13);

    // Set prescaling to clk-0
    /*
    clock frequency is 16MHz
    scaling of 1 --> 16 MHz
    */
    TCCR1B &= ~_BV(CS12);
    TCCR1B &= ~_BV(CS10);
    TCCR1B |= _BV(CS11);
#pragma endregion /TIMER_INTERRUPT


#pragma region BLUETOOTH
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
#pragma endregion /BLUETOOTH
}

void setOCR(float delay) {
    OCR1A = (int)(2000.0f*delay);
}