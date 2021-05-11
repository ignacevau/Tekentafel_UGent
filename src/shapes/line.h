#ifndef SHAPES_LINE_H_
#define SHAPES_LINE_H_


/**
 * @brief Tests whether the line stays within the allowed boundaries
 * 
 * @param x1 x value first point
 * @param y1 y value first point
 * @param x2 x value second point
 * @param y2 y value second point
 * @return Returns True if the line doesn't exceed the boundaries
 */
bool testLine(float x1, float y1, float x2, float y2);

/**
 * @brief Draw a line from the first point to the second
 * 
 * @param x1 x value first point
 * @param y1 y value first point
 * @param x2 x value second point
 * @param y2 y value second point
 */
void drawLine(float x1, float y1, float x2, float y2);
#endif // SHAPES_LINE_H_