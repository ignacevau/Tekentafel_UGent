#include <avr/io.h>
#include <avr/interrupt.h>
#include <Draw.h>

#define PERIODE 20.0f

typedef unsigned char bool;
static const bool False = 0;
static const bool True = 1;

/*
0: periode afwachten
1: eerste delay
2: tweede delay
*/
volatile int motor_state = 1;

float offset1 = +0.0f;
float offset2 = -0.11f;

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
            setOCR(PERIODE-((delay1+offset1)+(delay2+offset2)));
            motor_state = 1;

            // maken het weer mogelijk om de volgende hoek te berekenen(zie DRAW-functies)
            angle_berekend = 0;
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

            // pas OCR-register aan zodat de tijd tot volgende interrupt de lengte delay 1 bedraagt
            setOCR(delay2+offset2);
            motor_state = 0;
            break;
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
//circeltekende functie vanuit een middelpunt en beginpunt
void drawPartialCircle(float x1, float y1, bool wijzerszin, float sectie, float x0, float y0){
    float r = DISTANCE(x0, y0, x1, y1);
    // Zorg dat alle cirkels even snel getekend worden
    double iterations = (double)(50*r*sectie);
    double beginhoek = PI/2 - acos((x1-x0)/r);
    
    double i = 0; // teller in while-loop
    while( i < iterations) {
        if (!angle_berekend) {      // zolang de volledige periode van 20 ms nog niet om zijn (zie ISR) : wachten
            
            float t = (i*(2*PI) * sectie * (wijzerszin?-1:1))/iterations + beginhoek;
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


//circeltekende functie vanuit beginpunt en straal
void drawCircle(float x1, float y1, bool wijzerszin, float sectie, float r) {
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

// pt1 and pt3 are opposites
void drawRectangle(float x1, float y1, float x2, float y2, float x3, float y3) {
    float x4 = x1 + x3 - x2;
    float y4 = y1 + y3 - y2;

    drawLine(x1, y1, x2, y2);
    drawLine(x2, y2, x3, y3);
    drawLine(x3, y3, x4, y4);
    drawLine(x4, y4, x1, y1);
}

int main(void)
{
    // zet registers goed:
    SetRegisters();
    setOCR(PERIODE);

    // Go_to_Coords(10.0f, 2.0f);

    // drawCircle(4.0f, 6.0f, 5.0f, False, 1.0f);
    // drawBezier(1.0f, 1.0f, 0.0f, 10.0f, 10.0f, 10.0f);
    // drawBezier(10.0f, 10.0f, 8.0f, 8.0f, 5.0f, 5.0f);
    // drawLine(0.1f, 0.1f, 10.0f, 10.0f);

    // drawRectangle(2.0f, 10.0f, 2.0f, 2.0f, 10.0f, 2.0f);

    while (1)
    {
    //     //_delay_ms(1000);

    //     // drawLine(0.1f, 0.1f, 10.0f, 10.0f);
        
    //     // drawBezier(1.0f, 1.0f, 0.0f, 10.0f, 10.0f, 10.0f);

    //     _delay_ms(0.1);

        // drawPartialCircle(5.0f, 5.0f, True, 1.0f, 2.0f, 5.0f);
        // drawRectangle(2.0f, 10.0f, 2.0f, 2.0f, 10.0f, 2.0f);
        
        drawLine(2.0f, 2.0f, 10.0f, 2.0f);
        // draw_partial_Circle(10.0f,5.0f, True, 0.5f,8.0f,3.0f);
        drawLine(10.0f, 2.0f, 2.0f, 2.0f);
    }

    return 0;
}