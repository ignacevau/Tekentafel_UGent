#ifndef SHAPES_BEZIER_H_
#define SHAPES_BEZIER_H_

#include <IK.h>

// Options given to bezier functions to define the bezier curve
// @param x0 x value starting point
// @param y0 y value starting point
// @param x1 x value control point
// @param y1 y value control point
// @param x2 x value end point
// @param y2 y value end point
typedef struct bezierOptions {
    float x0;
    float y0;
    float x1;
    float y1;
    float x2;
    float y2;
};

bool testBezier(struct bezierOptions, int iterations);
double estimateBezierLength(struct bezierOptions, int iterations);

void drawBezier(struct bezierOptions);
#endif // SHAPES_BEZIER_H_