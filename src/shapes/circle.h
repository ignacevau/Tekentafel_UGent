#ifndef SHAPES_CIRCLE_H_
#define SHAPES_CIRCLE_H_


#include <IK.h>


/**
 * @brief Options given to bezier functions to define the bezier curve
 * 
 * @param x0
 * @param y0 y value starting point
 * @param clockwise Draw clockwise
 * @param section Value between 0 and 1, which fraction of the circle must be drawn
 * @param r Radius of the circle
 */
typedef struct circleOptions {
    float x0;
    float y0;
    bool clockwise;
    float section;
    float r;
};


/**
 * @brief Tests whether the given partial circle stays within the allowed boundaries 
 * by testing simulated circle points
 * 
 * @param options Point values which define the circle
 * @param iterations The amount of simulated points used for the approximation
 * @return Returns True if the partial circle doesn't exceed the boundaries
 */
bool testCircle(struct circleOptions options, double iterations);

/**
 * @brief Tests whether the given partial circle stays within the allowed boundaries 
 * by testing simulated circle points
 * 
 * @param options Point values which define the circle
 * @param iterations The amount of simulated points used for the approximation
 * @param beginangle The angle at which the circle starts drawing
 * @return Returns True if the partial circle doesn't exceed the boundaries
 */
bool testCircleFromPoint(struct circleOptions options, double iterations, double beginangle);


/**
 * @brief Draw a (partial) circle from center point and radius
 * 
 * @param options Point values which define the circle
 */
void drawCircle(struct circleOptions options);

/**
 * @brief Draw a (partial) circle from center point and begin point
 * 
 * @param options Point values which define the circle
 * @param x1 x value begin point
 * @param y1 y value begin point
 */
void drawCircleFromPoint(struct circleOptions options, float x1, float y1);

#endif // SHAPES_CIRCLE_H_