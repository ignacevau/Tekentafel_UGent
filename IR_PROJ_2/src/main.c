#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <math.h>
#include <IK.h>

#define PERIODE 20.0f
#define DISTANCE(x1, y1, x2, y2) sqrt(((x2)-(x1))*((x2)-(x1)) + ((y2)-(y1))*((y2)-(y1)))

typedef unsigned char bool;
static const bool False = 0;
static const bool True = 1;

/*
0: periode afwachten
1: eerste delay
2: tweede delay
*/
volatile int motor_state = 1;
volatile int angle_berekend = 0;

float delay1 = 0.7f;
float delay2 = 0.7f;

void SetRegisters(){

    // DDRA |= 0xFF;  // Leds als output
    // PORTA = 0xFF;    // Leds uit

    DDRC |= (1<<PC0) | (1<<PC1);
    PORTC &= ~(1<<PC0) & ~(1<<PC1);

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
}

//deze functie zet het OCR-register op een bepaalde waarde in functie van de prescaling (zie setRegisters) en van de delays (zie ISR)
void setOCR(float delay) {
    OCR1A = (int)(2000.0f*delay);
}

// Timer1 Compare A interrupt
ISR(TIMER1_COMPA_vect) {
    switch(motor_state) {
        case 0:
            // motor 2 uit
            PORTC &= ~(1<<PC1);
            
            // pas OCR-register aan zodat de tijd tot volgende interrupt de 20 ms (periode) volmaakt
            setOCR(PERIODE-(delay1+delay2));
            motor_state = 1;

            // maken het weer mogelijk om de volgende hoek te berekenen(zie DRAW-functies)
            angle_berekend = 0;
            break;
        case 1:
            // motor 1 aan
            PORTC |= (1<<PC0);

            // pas OCR-register aan zodat de tijd tot volgende interrupt de lengte delay 1 bedraagt
            setOCR(delay1);
            motor_state = 2;
            break;
        case 2:
            // motor 1 uit
            PORTC &= ~(1<<PC0);

            // motor 2 aan
            PORTC |= (1<<PC1);

            // pas OCR-register aan zodat de tijd tot volgende interrupt de lengte delay 1 bedraagt
            setOCR(delay2);
            motor_state = 0;
            break;
    }
}



void drawLine(float x1, float y1, float x2, float y2) {
    /*
    alpha11 = hoek motor1, begincoordinaten(situatie 1)
    alpha12 = hoek motor1, eindcoordinaten (situatie 2)
    alpha21 = hoek motor2, begincoordinaten(situatie 1)
    alpha22 = hoek motor2, eindcoordinaten (situatie 2)
    */

    float alpha11 = getAlpha1FromCoords(x1, y1), alpha12 = getAlpha2FromCoords(x1, y1); 
    float alpha21 = getAlpha1FromCoords(x2, y2), alpha22 = getAlpha2FromCoords(x2, y2);
    

    double i = 0;
    double iterations = (double)(5*DISTANCE(x1, y1, x2, y2));
    while(i < iterations) {
        if (!angle_berekend) {
            double fac = i/iterations;
            delay1 = getDelayFromAngle(alpha11 + fac*(alpha21-alpha11));
            delay2 = getDelayFromAngle(alpha12 + fac*(alpha22-alpha12));

            angle_berekend = 1;

            i++;

            _delay_ms(0.1);
        }
    }
}

double estimateBezierLength(float x0, float y0, float x1, float y1, float x2, float y2, int precision) {
    double length = 0.0f;
    float x_old = x0;
    float y_old = y0;
    
    for(int i=0; i<precision; i++) {
        float t = (float)i/(float)precision;
        float x = SQUARE(1-t) * x0 + 2 * (1-t) * t * x1 + SQUARE(t) * x2;
        float y = SQUARE(1-t) * y0 + 2 * (1-t) * t * y1 + SQUARE(t) * y2;

        length += DISTANCE(x_old, y_old, x, y);
        x_old = x;
        y_old = y;
    }
    
    return length;
}

void drawBezier(float x0, float y0, float x1, float y1, float x2, float y2){
    if (!angle_berekend) {
        double i = 0;
        double length = estimateBezierLength(x0, y0, x1, y1, x2, y2, 10);
        double iterations = (double)(150*length);
        while (i < iterations) {
            float t = i*(1.0f/iterations);
            float x = SQUARE(1-t) * x0 + 2 * (1-t) * t * x1 + SQUARE(t) * x2;
            float y = SQUARE(1-t) * y0 + 2 * (1-t) * t * y1 + SQUARE(t) * y2;
            
            float alpha1 = getAlpha1FromCoords(x, y);
            float alpha2 = getAlpha2FromCoords(x, y);

            delay1 = getDelayFromAngle(alpha1);
            delay2 = getDelayFromAngle(alpha2);

            angle_berekend = 1;

            i++;

            _delay_ms(0.1);
        }
    }
}

void Go_to_Coords(float x, float y){
    if(!angle_berekend) {
        // bereken delays
        float alpha1 = getAlpha1FromCoords(x, y), alpha2 = getAlpha2FromCoords(x,y);
        delay1 = getDelayFromAngle(alpha1);
        delay2 = getDelayFromAngle(alpha2);

        angle_berekend = 1;
    }
}

void drawCircle(float r, float x1, float y1, bool wijzerszin, float sectie) {
    // Zorg dat alle cirkels even snel getekend worden
    double iterations = (double)(50*r*sectie);

    double i = 0; // teller in while-loop
    while( i < iterations) {
        if (!angle_berekend) {      // zolang de volledige periode van 20 ms nog niet om zijn (zie ISR) : wachten
            
            float t = (i*(2*PI) * sectie * (wijzerszin?-1:1))/iterations;
            float x = r * cos(t) + x1;
            float y = r * sin(t) + y1;
            
            float alpha1 = getAlpha1FromCoords(x, y);
            float alpha2 = getAlpha2FromCoords(x, y);
            
            //pas delays aan zodat het OCR register juist kan aangepast worden
            delay1 = getDelayFromAngle(alpha1);
            delay2 = getDelayFromAngle(alpha2);

            angle_berekend = 1;

            i++;

            _delay_ms(0.1);
        }
    }
}

int main(void)
{
    // zet registers goed:
    SetRegisters();
    setOCR(PERIODE);

    // drawCircle(4.0f, 6.0f, 5.0f, False, 1.0f);
    // drawBezier(1.0f, 1.0f, 0.0f, 10.0f, 10.0f, 10.0f);
    // drawBezier(10.0f, 10.0f, 8.0f, 8.0f, 5.0f, 5.0f);
    drawLine(0.1f, 0.1f, 10.0f, 10.0f);

    // while (1)
    // {
        
    //     // Go_to_Coords(0.0f, 0.0f);
    //     //_delay_ms(1000);

    //     // drawLine(0.1f, 0.1f, 10.0f, 10.0f);
        
    //     // drawBezier(1.0f, 1.0f, 0.0f, 10.0f, 10.0f, 10.0f);

    //     _delay_ms(0.1);
    // }

    return 0;
}