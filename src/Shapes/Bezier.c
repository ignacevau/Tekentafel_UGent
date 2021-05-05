#include <Draw.h>
#include <Shapes/Bezier.h>
#include <util/delay.h>

// Test whether the given bezier function stays within the allowed boundaries
// by testing simulated bezier points
// @param options Point values which define the bezier curve
// @param iterations The amount of simulated points used for the approximation
// @result Returns True if the bezier doesn't exceed the boundaries
bool testBezier(struct bezierOptions options, int iterations) {
    double i = 0; // Teller in while-loop
    while( i < iterations) {
        float t = i*(1.0f / iterations);
        // Stel parametervoorstelling op voor x en y van bezier-curve
        float x = SQUARE(1-t) * options.x0 + 2 * (1-t) * t * options.x1 + SQUARE(t) * options.x2;
        float y = SQUARE(1-t) * options.y0 + 2 * (1-t) * t * options.y1 + SQUARE(t) * options.y2;

        if (!testCoord(x, y)){
            return False;
        }
        i++;
    }
    return True;
}

// Estimate bezier curve length by simulating the curve points controlled by a given precision
// @param options Point values which define the bezier curve
// @param iterations The amount of simulated points used for the approximation
// @result Returns the estimated bezier curve length
double estimateBezierLength(struct bezierOptions options, int iterations) {
    double length = 0.0f;
    float x_old = options.x0;
    float y_old = options.y0;
    
    for(int i=0; i<iterations; i++) {
        float t = (float)i/(float)iterations;
        // Stel parametervoorstelling op voor x en y van bezier-curve
        float x = SQUARE(1-t) * options.x0 + 2 * (1-t) * t * options.x1 + SQUARE(t) * options.x2;
        float y = SQUARE(1-t) * options.y0 + 2 * (1-t) * t * options.y1 + SQUARE(t) * options.y2;

        length += DISTANCE(x_old, y_old, x, y);
        x_old = x;
        y_old = y;
    }
    
    return length;
}

// Draw a bezier curve if it doesn't exceed the allowed boundaries
// @param options Point values which define the bezier curve
void drawBezier(struct bezierOptions options) {
    double i = 0;
    double length = estimateBezierLength(options, 10);
    double iterations = (double)(150*length);
    if (testBezier(options, iterations)) {
        while (i < iterations) {
            if (!period_started) {
                float t = i*(1.0f/iterations);
                float x = SQUARE(1-t) * options.x0 + 2 * (1-t) * t * options.x1 + SQUARE(t) * options.x2;
                float y = SQUARE(1-t) * options.y0 + 2 * (1-t) * t * options.y1 + SQUARE(t) * options.y2;
                

                delay1 = getDelay1(x, y);
                delay2 = getDelay2(x, y);

                period_started = 1;

                i++;

                _delay_ms(0.1);
            }
        }
    }
}