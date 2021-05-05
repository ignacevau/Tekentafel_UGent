#include <IK.h>

const bool False = 0;
const bool True = 1;

const float L1 = 12.4f;
const float L2 = 12.4f;

float delay1 = 1.7f;
float delay2 = 1.1f;
float delay3 = 1.05f;

volatile int period_started = 0;


float getAlpha1FromCoords(float x, float y) {
    const float r = sqrt(SQUARE(x) + SQUARE(y));
    float _theta1 = atan(y/x) - acos((SQUARE(L2)-SQUARE(L1)-SQUARE(r))/(-2.0*L1*r));

    float alpha1 = PI/2 - _theta1;

    return alpha1;
}

float  getAlpha2FromCoords(float x, float y) {
    const float r = sqrt(SQUARE(x) + SQUARE(y));
    float _theta2 = PI - acos((SQUARE(r)-SQUARE(L1)-SQUARE(L2))/(-2.0*L1*L2));
    float alpha2 = PI - _theta2;
    return alpha2;
}

float getDelay2(float x, float y) {
    float angle = getAlpha2FromCoords(x,y);
    return ((DELAY_PI - DELAY_0) / PI) * angle + DELAY_0;
}

float getDelay1(float x, float y) {
    float angle = getAlpha1FromCoords(x,y);
    return ((DELAY_PI - DELAY_0) / PI) * angle + DELAY_0;
}