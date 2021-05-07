#ifndef IK_H_
#define IK_H_

#define DISTANCE(x1, y1, x2, y2) sqrt(((x2)-(x1))*((x2)-(x1)) + ((y2)-(y1))*((y2)-(y1)))
#define SQUARE(x) ((x)*(x))
#define PI 3.14159265f
#define DELAY_0 0.7
#define DELAY_PI 2.3


// Custom boolean datatype
typedef unsigned char bool;
const bool False;
const bool True;

// Delay for servo 1
float delay1;
// Delay for servo 2
float delay2;
// Delay for servo 3
float delay3;

/**
 * @brief Get the delay needed for the pulse of servo 1 to move the
 * arm to a given coordinate
 * 
 * @param x x value coordinate
 * @param y y value coordinate
 */
float getDelay1(float x, float y);

/**
 * @brief Get the delay needed for the pulse of servo 2 to move the
 * arm to a given coordinate
 * 
 * @param x x value coordinate
 * @param y y value coordinate
 */
float getDelay2(float x, float y);

/**
 * @brief Whether the period (20ms) for the servos has started again
 */
volatile int period_started;
#endif // IK_H_