#include <draw.h>


bool testCoord(float x, float y) {
    if (x >= MIN_X && x <= MAX_X && y <= MAX_Y && y >= MIN_Y) {
        return True;
    }
    return False;
}

float getCorrectedPencilHeight(float x, float y, float low, float offset) {
    // Adjust the height depending on the angle of the second arm
    return low + offset * ((delay2 - DELAY_0) / (DELAY_PI-DELAY_0));
}

void goToCoords(float x, float y) {
    // Calculate and set delays
    delay1 = getDelay1(x, y);
    delay2 = getDelay2(x, y);
}