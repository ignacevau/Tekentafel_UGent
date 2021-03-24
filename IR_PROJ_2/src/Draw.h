#include <util/delay.h>
#define DISTANCE(x1, y1, x2, y2) sqrt(((x2)-(x1))*((x2)-(x1)) + ((y2)-(y1))*((y2)-(y1)))

void drawLine(float x1, float y1, float x2, float y2);
float delay1;
float delay2;
volatile int angle_berekend;