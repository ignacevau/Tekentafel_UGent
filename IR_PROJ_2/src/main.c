#include <avr/io.h>
#include <util/delay.h>
#include <math.h>

#define SQUARE(x) ((x)*(x))
#define PI 3.14159265f


const float L1 = 12.4f;
const float L2 = 12.3f;


float * getAngleFromCoords(float x, float y) {
    const float r = sqrt(SQUARE(x) + SQUARE(y));
    float _theta1 = atan(y/x) - acos((SQUARE(L2)-SQUARE(L1)-SQUARE(r))/(-2.0f*L1*r));
    float _theta2 = PI - acos((SQUARE(r)-SQUARE(L1)-SQUARE(L2))/(-2.0f*L1*L2));

    float alpha1 = PI - _theta1;
    float alpha2 = PI - _theta2;

    static float result[2];
    result[0] = alpha1;
    result[1] = alpha2;
    return result;
}

float getDelayFromAngle(float angle) {
    return ((2.3-0.7)/PI)*angle + 0.7;
}


int main(void)
{
    DDRC |= (1<<PC0) | (1<<PC1);
    PORTC &= ~(1<<PC0) & ~(1<<PC1);

    while (1)
    {
        float *angles = getAngleFromCoords(10.0f, 10.0f);
        float delay1 = getDelayFromAngle(angles[0]);
        float delay2 = getDelayFromAngle(angles[1]);

        PORTC |= (1<<PC0);
        _delay_ms(delay1);
        PORTC &= ~(1<<PC0);

        PORTC |= (1<<PC1);
        _delay_ms(delay2);
        PORTC &= ~(1<<PC1);

        _delay_ms(10);
    }

    return 0;
}