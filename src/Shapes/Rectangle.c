#include <Draw.h>
#include <Shapes/Line.h>
#include <Shapes/Rectangle.h>
#include <Game.h>


bool testRectangle(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
    if(testCoord(x1, y1) && testCoord(x2,y2) && testCoord(x3, y3) && testCoord(x4, y4)){
        return True;
    }
    return False;
}

// Punt1 and punt3 verbinden een diagonaal van de rechthoek
void drawRectangle(float x1, float y1, float x2, float y2, float x3, float y3) {
    float x4 = x1 + x3 - x2;
    float y4 = y1 + y3 - y2;
    if (testRectangle(x1, y1, x2, y2, x3, y3, x4, y4)) {
        dropPencil(x1, y1);
        drawLine(x1, y1, x2, y2);
        drawLine(x2, y2, x3, y3);
        drawLine(x3, y3, x4, y4);
        drawLine(x4, y4, x1, y1);
        elevatePencil();
    }
    else{
        // Schrijf iets op board
    }
}