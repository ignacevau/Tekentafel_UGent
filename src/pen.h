#ifndef PEN_H_
#define PEN_H_

#include <draw.h>

#define LOW 0.83
// Offset caused by gravity at the furthest point
#define LOW_OFFSET 0.3


/**
 * @brief Is the pen drawing right now
 */
bool penDown;


/**
 * @brief Rise the pencil from the drawing board in 0.5 seconds
 */
void elevatePencil();

/**
 * @brief Drop the pencil on the drawing board. The height of the
 * pencil depends on the coordinates given.
 * 
 * @param x x value of coord to drop pencil at
 * @param y y value of coord to drop pencil at
 */
void dropPencil(float x, float y);

#endif // PEN_H_