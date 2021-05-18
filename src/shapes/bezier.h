#ifndef SHAPES_BEZIER_H_
#define SHAPES_BEZIER_H_


#include <IK.h>


/**
 * @brief Options given to bezier functions to define the bezier curve
 * 
 * @param x0 x value starting point
 * @param y0 y value starting point
 * @param x1 x value control point
 * @param y1 y value control point
 * @param x2 x value end point
 * @param y2 y value end point
 */
typedef struct bezierOptions {
    float x0;
    float y0;
    float x1;
    float y1;
    float x2;
    float y2;
};


/**
 * @brief Test whether the given bezier function stays within the allowed boundaries 
 * by testing simulated bezier points
 * 
 * @param options Point values which define the bezier curve
 * @param iterations The amount of simulated points used for the approximation
 * @return Returns True if the bezier doesn't exceed the boundaries
 */
bool testBezier(struct bezierOptions options, int iterations);

/**
 * @brief Draw a bezier curve if it doesn't exceed the allowed boundaries
 * 
 * @param options Point values which define the bezier curve
 */
void drawBezier(struct bezierOptions options);
#endif // SHAPES_BEZIER_H_