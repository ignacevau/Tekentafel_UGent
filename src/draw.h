#ifndef DRAW_H_
#define DRAW_H_

#include <IK.h>

#define MIN_X 0.0
#define MIN_Y 2.0
#define MAX_X 15.5
#define MAX_Y 21.0


/**
 * @brief Test whether a coordinate stays within allowed boundaries
 * 
 * @param x x value coordinate
 * @param y y value coordinate
 * @return Returns True if the coordinate doesn't exceed the boundaries
 */
bool testCoord(float x, float y);

/**
 * @brief Get corrected pencil height to account for the sagging of
 * the drawing arm caused by gravity
 * The corrections are made depending on the angle of the second
 * drawing arm
 * 
 * @param x x value pencil
 * @param y y value pencil
 * @param low Delay for the lowest point of the pencil
 * @param offset Offset between delays for the nearest and furthest point
 */
float getCorrectedPencilHeight(float x, float y, float low, float offset);

/**
 * @brief Move the pen to the specified coordinates
 * 
 * @param x x value coordinate
 * @param y y value coordinate
 */
void goToCoords(float x, float y);

#endif // DRAW_H_