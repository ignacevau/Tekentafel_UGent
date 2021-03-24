
#include <IK.h>

const float L1 = 12.4f;
const float L2 = 12.4f;

float getAlpha1FromCoords(float x, float y) {
    const float r = sqrt(SQUARE(x) + SQUARE(y));
    float _theta1 = atan(y/x) - acos((SQUARE(L2)-SQUARE(L1)-SQUARE(r))/(-2.0f*L1*r));

    float alpha1 = PI/2 - _theta1;

    return alpha1;
}

float  getAlpha2FromCoords(float x, float y) {
    const float r = sqrt(SQUARE(x) + SQUARE(y));
    float _theta2 = PI - acos((SQUARE(r)-SQUARE(L1)-SQUARE(L2))/(-2.0f*L1*L2));
    float alpha2 = PI - _theta2;
    return alpha2;
}

float getDelayFromAngle(float angle) {
    return ((2.3-0.7)/PI)*angle + 0.7;
}