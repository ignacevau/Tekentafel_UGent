#include <draw.h>
#include <shapes/circle.h>
#include <util/delay.h>
#include <pen.h>


bool testCircle(struct circleOptions options, double iterations) {
    double i = 0; // Counter in while-loop
    while( i < iterations) {  
        float t = (i*(2*PI) * options.section * (options.clockwise?-1:1))/iterations;
        float x = options.r * cos(t) + options.x0;
        float y = options.r * sin(t) + options.y0;
        if (!testCoord(x, y)){
            return False;
        }
        i++;
        
    }
    return True;
}

bool testCircleFromPoint(struct circleOptions options, double iterations, double beginangle) {
    double i = 0; // Counter in while-loop
    while( i < iterations) { 
        float t = (i*(2*PI) * options.section * (options.clockwise?-1:1))/iterations + beginangle;
        float x = options.r * cos(t) + options.x0;
        float y = options.r * sin(t) + options.y0;
        if (!testCoord(x, y)){
            return False;
        }
        i++;
        
    }
    return True;
}


void drawCircle(struct circleOptions options) {
    // Calculate amount of iterations to assure that every circle gets drawn
    // at the same speed
    double iterations = (double)(80*options.r*options.section);
    if (testCircle(options, iterations)){
        double i = 0; // Counter in while-loop
        while( i < iterations) {
            if (!period_started) {  // Wait until the 20ms period is over (ISR)
                
                float t = (i*(2*PI) * options.section * (options.clockwise?-1:1))/iterations;
                float x = options.r * cos(t) + options.x0;
                float y = options.r * sin(t) + options.y0;
                
                // Set delays so that the OCR register can be set correctly
                delay1 = getDelay1(x, y);
                delay2 = getDelay2(x, y);

                // Correct the pencil height to adjust for the sagging of the arm due to gravity
                if (penDown) {
                    delay3 = getCorrectedPencilHeight(x, y, LOW, LOW_OFFSET);
                }

                period_started = True;
                i++;

                // A minimal delay is necessary to account for fysical inaccuracies
                _delay_us(1);
            }
        }
    }
}

void drawCircleFromPoint(struct circleOptions options, float x1, float y1) {
    float r = DISTANCE(x1, y1, options.x0, options.y0);
    // Calculate amount of iterations to assure that every circle gets drawn
    // at the same speed
    double iterations = (double)(50*r*options.section);
    double beginangle = PI/2 - acos((options.x0-x1)/r);
    if (testPartialCircle(options.x0, options.y0, options.clockwise, options.section, r, iterations, beginangle)) {
        double i = 0; // Counter in while-loop
        while( i < iterations) {
            if (!period_started) {  // Wait until the 20ms period is over (ISR)
            
                float t = (i*(2*PI) * options.section * (options.clockwise?-1:1))/iterations + beginangle;
                float x = r * cos(t) + options.x0;
                float y = r * sin(t) + options.y0;
            
                // Set delays so that the OCR register can be set correctly
                delay1 = getDelay1(x, y);
                delay2 = getDelay2(x, y);

                // Correct the pencil height to adjust for the sagging of the arm due to gravity
                if (penDown) {
                    delay3 = getCorrectedPencilHeight(x, y, LOW, LOW_OFFSET);
                }

                period_started = True;
                i++;

                // A minimal delay is necessary to account for fysical inaccuracies
                _delay_us(1);
            }
        }
    }
}