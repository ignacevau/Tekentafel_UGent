#include <Shapes/Bezier.h>
#include <Shapes/Circle.h>
#include <Shapes/Line.h>
#include <Shapes/Rectangle.h>

#define LOW 0.83
// Offset caused by gravity at the furthest point
#define LOW_OFFSET 0.3

bool penDown;

void drawGrid();
void drawCross(float x, float y);
void playCross(int BOX);
void playCircle(int BOX);
void goToCenter();
void dropPencil(float x, float y);
void elevatePencil();
void drawSingleLine(float x1, float y1, float x2, float y2);

void play();