#ifndef _BEZIER_HEADER_
#define _BEZIER_HEADER_
#include <Draw.h>
#include <Shapes/Bezier.h>
#include <util/delay.h>

bool testBezier(float x0, float y0, float x1, float y1, float x2, float y2, int iterations) {
    double i = 0; // Teller in while-loop
    while( i < iterations) {
        float t = i*(1.0f / iterations);
        // Stel parametervoorstelling op voor x en y van bezier-curve
        float x = SQUARE(1-t) * x0 + 2 * (1-t) * t * x1 + SQUARE(t) * x2;
        float y = SQUARE(1-t) * y0 + 2 * (1-t) * t * y1 + SQUARE(t) * y2;

        if (!testCoord(x, y)){
            return False;
        }
        i++;
    }
    return True;
}

double estimateBezierLength(float x0, float y0, float x1, float y1, float x2, float y2, int precision) {
    double length = 0.0f;
    float x_old = x0;
    float y_old = y0;
    
    for(int i=0; i<precision; i++) {
        float t = (float)i/(float)precision;
        // Stel parametervoorstelling op voor x en y van bezier-curve
        float x = SQUARE(1-t) * x0 + 2 * (1-t) * t * x1 + SQUARE(t) * x2;
        float y = SQUARE(1-t) * y0 + 2 * (1-t) * t * y1 + SQUARE(t) * y2;

        length += DISTANCE(x_old, y_old, x, y);
        x_old = x;
        y_old = y;
    }
    
    return length;
}

void drawBezier(float x0, float y0, float x1, float y1, float x2, float y2) {
    double i = 0;
    double length = estimateBezierLength(x0, y0, x1, y1, x2, y2, 10);
    double iterations = (double)(150*length);
    if (testBezier(x0, y0, x1, y1, x2, y2, iterations)) {
        while (i < iterations) {
            if (!period_started) {
                float t = i*(1.0f/iterations);
                float x = SQUARE(1-t) * x0 + 2 * (1-t) * t * x1 + SQUARE(t) * x2;
                float y = SQUARE(1-t) * y0 + 2 * (1-t) * t * y1 + SQUARE(t) * y2;
                

                delay1 = getDelay1(x, y);
                delay2 = getDelay2(x, y);

                period_started = 1;

                i++;

                _delay_ms(0.1);
            }
        }
    }
}
#endif