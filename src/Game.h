#ifndef GAME_H_
#define GAME_H_

#include <Shapes/Bezier.h>
#include <Shapes/Circle.h>
#include <Shapes/Line.h>
#include <Shapes/Rectangle.h>

void drawGrid();
void drawCross(float x, float y);
void playCross(int BOX);
void playCircle(int BOX);
void goToCenter();
void dropPencil(float x, float y);
void elevatePencil();
void drawSingleLine(float x1, float y1, float x2, float y2);

void play();

#endif // GAME_H_