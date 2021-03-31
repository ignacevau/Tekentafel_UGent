#include <math.h>

#define DISTANCE(x1, y1, x2, y2) sqrt(((x2)-(x1))*((x2)-(x1)) + ((y2)-(y1))*((y2)-(y1)))
#define SQUARE(x) ((x)*(x))
#define PI 3.14159265f
#define DELAY_0 0.7
#define DELAY_PI 2.3

typedef unsigned char bool;
const bool False;
const bool True;

float delay1;
float delay2;
float delay3;

float getAlpha1FromCoords(float x, float y);

float getAlpha2FromCoords(float x, float y);

float getDelay1(float x, float y);

float getDelay2(float x, float y);

volatile int period_started;