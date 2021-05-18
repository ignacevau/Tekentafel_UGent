#include <shapes/line.h>
#include <util/delay.h>
#include <pen.h>


bool testLine(float x1, float y1, float x2, float y2) {
    if (testCoord(x1,y1) && testCoord(x2,y2)){
        return True;
    }
    return False;
}

void drawLine(float x1, float y1, float x2, float y2) {
    if (testLine(x1, y1, x2, y2)) {
        // Calculate amount of iterations to assure that every circle gets drawn
        // at the same speed
        double iterations = (double)(20*DISTANCE(x1, y1, x2, y2));

        double i = 0;
        while(i < iterations) {
            if (!period_started) {  // Wait until the 20ms period is over (ISR)
                double fac = i/iterations;
                float x = x1 + fac*(x2-x1);
                float y = y1 + fac*(y2-y1);
                
                // Set delays so that the OCR register can be set correctly
                delay1 = getDelay1(x, y);
                delay2 = getDelay2(x, y);

                // Correct the pencil height to adjust for the sagging of the arm due to gravity
                if (penDown) {
                    delay3 = getCorrectedPencilHeight(x, y, LOW, LOW_OFFSET);
                }

                i++;
                period_started = 1;

                // A minimal delay is necessary to account for fysical inaccuracies
                _delay_us(1);
            }
        }
    }
}