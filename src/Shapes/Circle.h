#ifndef SHAPES_CIRCLE_H_
#define SHAPES_CIRCLE_H_

#include <IK.h>
#include <pen.h>

// Options given to bezier functions to define the bezier curve
// @param x0 x value starting point
// @param y0 y value starting point
// @param clockwise draw clockwise
// @param section value between 0 and 1, how much of the circle must be drawn
// @param r radius of the circle
typedef struct circleOptions {
    float x0;
    float y0;
    bool clockwise;
    float section;
    float r;
};

bool testCircle(float x1, float y1, bool clockwise, float section, float r, double iterations);
bool testPartialCircle(float x1, float y1, bool clockwise, float section, float r, double iterations, double beginangle);

void drawCircle(float x1, float y1, bool clockwise, float section, float r);
void drawCircleFromPoint(struct circleOptions options, float x1, float y1);
#endif // SHAPES_CIRCLE_H_