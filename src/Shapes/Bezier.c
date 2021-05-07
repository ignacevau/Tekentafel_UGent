#include <Draw.h>
#include <Shapes/Bezier.h>
#include <util/delay.h>
#include <pen.h>


/**
 * @brief Estimate bezier curve length by simulating the curve points controlled by a given precision
 * 
 * @param options Point values which define the bezier curve
 * @param iterations The amount of simulated points used for the approximation
 * @return Returns the estimated bezier curve length
 */
static float estimateBezierLength(struct bezierOptions options, int iterations);


bool testBezier(struct bezierOptions options, int iterations) {
    double i = 0; // Counter in while-loop
    while( i < iterations) {
        float t = i*(1.0f / iterations);
        // Parameter functions of x and y for the bezier curve
        float x = SQUARE(1-t) * options.x0 + 2 * (1-t) * t * options.x1 + SQUARE(t) * options.x2;
        float y = SQUARE(1-t) * options.y0 + 2 * (1-t) * t * options.y1 + SQUARE(t) * options.y2;

        if (!testCoord(x, y)){
            return False;
        }
        i++;
    }
    return True;
}

void drawBezier(struct bezierOptions options) {
    // Calculate amount of iterations to assure that every bezier curve gets drawn
    // at the same speed
    double length = estimateBezierLength(options, 10);
    double iterations = (double)(150*length);
    if (testBezier(options, iterations)) {
        double i = 0; // Counter in while-loop
        while (i < iterations) {
            if (!period_started) {  // Wait until the 20ms period is over (ISR)
                float t = i*(1.0f/iterations);
                float x = SQUARE(1-t) * options.x0 + 2 * (1-t) * t * options.x1 + SQUARE(t) * options.x2;
                float y = SQUARE(1-t) * options.y0 + 2 * (1-t) * t * options.y1 + SQUARE(t) * options.y2;
                
                // Set delays so that the OCR register can be set correctly
                delay1 = getDelay1(x, y);
                delay2 = getDelay2(x, y);

                // Correct the pencil height to adjust for the sagging of the arm due to gravity
                if (penDown) {
                    delay3 = getCorrectedPencilHeight(x, y, LOW, LOW_OFFSET);
                }

                period_started = 1;
                i++;

                // A minimal delay is necessary to account for fysical inaccuracies
                _delay_us(1);
            }
        }
    }
}

static float estimateBezierLength(struct bezierOptions options, int iterations) {
    float length = 0.0f;
    float x_old = options.x0;
    float y_old = options.y0;
    
    for(int i=0; i<iterations; i++) {
        float t = (float)i/(float)iterations;
        // Parameter functions of x and y for the bezier curve
        float x = SQUARE(1-t) * options.x0 + 2 * (1-t) * t * options.x1 + SQUARE(t) * options.x2;
        float y = SQUARE(1-t) * options.y0 + 2 * (1-t) * t * options.y1 + SQUARE(t) * options.y2;

        length += DISTANCE(x_old, y_old, x, y);
        x_old = x;
        y_old = y;
    }
    
    return length;
}