#ifndef DRAW_H_
#define DRAW_H_

#include <IK.h>

#define MIN_X 0.0
#define MIN_Y 2.0
#define MAX_X 15.5
#define MAX_Y 21.0

bool testCoord(float x, float y);
float getCorrectedPencilHeight(float x, float y, float low, float offset);
void goToCoords(float x, float y);

#endif // DRAW_H_