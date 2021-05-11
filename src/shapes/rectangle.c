#include <draw.h>
#include <shapes/line.h>
#include <shapes/rectangle.h>
#include <pen.h>


bool testRectangle(struct rectangleOptions options) {
    float x4 = options.x1 + options.x3 - options.x2;
    float y4 = options.y1 + options.y3 - options.y2;

    if(testCoord(options.x1, options.y1) && 
       testCoord(options.x2, options.y2) && 
       testCoord(options.x3, options.y3) && 
       testCoord(x4, y4)) {
        return True;
    }
    return False;
}

void drawRectangle(struct rectangleOptions options) {
    float x4 = options.x1 + options.x3 - options.x2;
    float y4 = options.y1 + options.y3 - options.y2;
    
    if (testRectangle(options)) {
        dropPencil(options.x1, options.y1);
        drawLine(options.x1, options.y1, options.x2, options.y2);
        drawLine(options.x2, options.y2, options.x3, options.y3);
        drawLine(options.x3, options.y3, x4, y4);
        drawLine(x4, y4, options.x1, options.y1);
        elevatePencil();
    }
}