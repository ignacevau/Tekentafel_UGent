#ifndef _Draw_HEADER_
#define _Draw_HEADER_

#include <Draw.h>
#include <IK.h>

float delay1 = 0.7f;
float delay2 = 0.7f;

volatile int angle_berekend = 0;


void drawLine(float x1, float y1, float x2, float y2) {
    double i = 0;
    double iterations = (double)(5*DISTANCE(x1, y1, x2, y2));
    while(i < iterations) {
        if (angle_berekend == 0) {
            double fac = i/iterations;
            float x = x1 + fac*(x2-x1);
            float y = y1 + fac*(y2-y1);

            float alpha1 = getAlpha1FromCoords(x, y);
            float alpha2 = getAlpha2FromCoords(x, y);
            
            //pas delays aan zodat het OCR register juist kan aangepast worden
            delay1 = getDelayFromAngle(alpha1);
            delay2 = getDelayFromAngle(alpha2);

            i++;

            angle_berekend = 1;

            // Kleine delay nodig om edge case op te lossen
            _delay_us(1);
        }
    }
}


#endif