#ifndef SHAPES_RECTANGLE_H_
#define SHAPES_RECTANGLE_H_


/**
 * @brief Options given to rectangle functions to define the rectangle
 * 
 * @param x1 x value first point of diagonal
 * @param y1 y value first point of diagonal
 * @param x2 x value second point rectangle
 * @param y2 y value second point rectangle
 * @param x3 x value second point of diagonal
 * @param y3 y value second point of diagonal
 */
typedef struct rectangleOptions {
    float x1;
    float y1;
    float x2;
    float y2;
    float x3;
    float y3;
};


/**
 * @brief Tests whether the given rectangle stays within the allowed boundaries 
 * 
 * @param options Point values which define the rectangle
 * @return Returns True if the rectangle doesn't exceed the boundaries
 */
bool testRectangle(struct rectangleOptions options);

/**
 * @brief Draw a rectangle from 3 points, the first and third point make
 * the diagonal
 * 
 * @param options Point values which define the rectangle
 */
void drawRectangle(struct rectangleOptions options);
#endif // SHAPES_RECTANGLE_H_