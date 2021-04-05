#ifndef _LINE_HEADER_
#define _LINE_HEADER_
#include <Draw.h>
#include <Shapes/Line.h>
#include <util/delay.h>



bool testLine(float x1, float y1, float x2, float y2) {
    if (testCoord(x1,y1) && testCoord(x2,y2)){
        return True;
    }
    return False;
}

void drawLine(float x1, float y1, float x2, float y2) {
    if (testLine(x1, y1, x2, y2)) {
        double i = 0;
        double iterations = (double)(5*DISTANCE(x1, y1, x2, y2));
        while(i < iterations) {
            if (!period_started) {
                double fac = i/iterations;
                float x = x1 + fac*(x2-x1);
                float y = y1 + fac*(y2-y1);

                
                // Pas delays aan zodat het OCR register juist kan aangepast worden
                delay1 = getDelay1(x, y);
                delay2 = getDelay2(x, y);

                i++;

                period_started = 1;

                // Kleine delay nodig om edge case op te lossen
                _delay_ms(1);
            }
        }
    }
    else{
        // Schrijf op boardje dat niet werkt
    }
}

// void drawCross(float x, float y){
    
// }
#endif