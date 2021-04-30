#ifndef _CIRCLE_HEADER_
#define _CIRCLE_HEADER_
#include <Draw.h>
#include <Shapes/Circle.h>
#include <util/delay.h>
#include <Game.h>


bool testCircle(float x1, float y1, bool clockwise, float section, float r, double iterations) {
    double i = 0; // Teller in while-loop
    while( i < iterations) {  
        float t = (i*(2*PI) * section * (clockwise?-1:1))/iterations;
        float x = r * cos(t) + x1;
        float y = r * sin(t) + y1;
        if (!testCoord(x, y)){
            return False;
        }
        i++;
        
    }
    return True;
}

bool testPartialCircle(float x1, float y1, bool clockwise, float section, float r, double iterations, double beginangle) {
    double i = 0; // Teller in while-loop
    while( i < iterations) { 
        float t = (i*(2*PI) * section * (clockwise?-1:1))/iterations + beginangle;
        float x = r * cos(t) + x1;
        float y = r * sin(t) + y1;
        if (!testCoord(x, y)){
            return False;
        }
        i++;
        
    }
    return True;
}


// Circeltekende functie vanuit beginpunt en straal
void drawCircle(float x1, float y1, bool clockwise, float section, float r) {
    // Zorg dat alle cirkels even snel getekend worden
    double iterations = (double)(80*r*section);
    if (testCircle(x1, y1, clockwise, section, r, iterations)){
        double i = 0; // Teller in while-loop
        while( i < iterations) {
            if (!period_started) {      // Zolang de volledige periode van 20 ms nog niet om zijn (zie ISR) : wachten
                
                float t = (i*(2*PI) * section * (clockwise?-1:1))/iterations;
                float x = r * cos(t) + x1;
                float y = r * sin(t) + y1;
                
                
                // Pas delays aan zodat het OCR register juist kan aangepast worden
                delay1 = getDelay1(x, y);
                delay2 = getDelay2(x, y);

                if (True) {
                    if (penDown) {
                        delay3 = getCorrectedPencilHeight(x, y, LOW, LOW_OFFSET);
                    }
                }

                period_started = 1;

                i++;

                _delay_ms(0.1);
            }
        }
    }
    else{
        //schrijf iets op board
    }
}

// Circeltekende functie vanuit een middelpunt en beginpunt
void drawPartialCircle(float x1, float y1, bool clockwise, float section, float x0, float y0) {
    float r = DISTANCE(x0, y0, x1, y1);
    // Zorg dat alle cirkels even snel getekend worden
    double iterations = (double)(50*r*section);
    double beginangle = PI/2 - acos((x1-x0)/r);
    if (testPartialCircle(x1, y1, clockwise,section, r, iterations, beginangle)) {
        double i = 0; // Teller in while-loop
        while( i < iterations) {
            if (!period_started) {      // Zolang de volledige periode van 20 ms nog niet om zijn (zie ISR) : wachten
            
                float t = (i*(2*PI) * section * (clockwise?-1:1))/iterations + beginangle;
                float x = r * cos(t) + x1;
                float y = r * sin(t) + y1;
            
                // Pas delays aan zodat het OCR register juist kan aangepast worden
                delay1 = getDelay1(x, y);
                delay2 = getDelay2(x, y);

                period_started = True;

                i++;

                _delay_ms(0.1);
            }
        }
    }
    else{
        //schrijf naar board
    }
}
#endif