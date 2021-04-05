#ifndef _Game_Header_
#define _Game_Header_
#include <Game.h>
#include <Bluetooth.h>
#include <avr/io.h>

#define LENGTH_GRID 12.0
#define LENGTH_BOX (LENGTH_GRID/3)
#define START_X 2.0
#define START_Y 2.0
#define OFFSET 0.5
#define Complete_Circle 1
#define Radius ((LENGTH_BOX - OFFSET) /2)


// Hier kunnen we volledige tekeningen maken (door de arm opheffen enzo)

void drawGrid(){
    drawLine(LENGTH_GRID / 3 + 2, 2, LENGTH_GRID / 3 + 2, 14);
    drawLine(2 * LENGTH_GRID / 3 + 2, 2, 2 * LENGTH_GRID / 3 + 2, 14);
    drawLine(2, LENGTH_GRID / 3 + 2, 14,  LENGTH_GRID / 3 + 2);
    drawLine(2, 2 * LENGTH_GRID / 3 + 2, 14, 2 * LENGTH_GRID / 3 + 2);
}

void drawCross(float x, float y){
    drawLine(x - LENGTH_BOX / 2 + OFFSET, y - LENGTH_BOX / 2 + OFFSET, x + LENGTH_BOX / 2 - OFFSET, y + LENGTH_BOX / 2 - OFFSET);
    drawLine(x - LENGTH_BOX / 2 + OFFSET, y + LENGTH_BOX / 2 - OFFSET, x + LENGTH_BOX / 2 - OFFSET, y - LENGTH_BOX / 2 + OFFSET);
}

void playCross(int BOX){
    switch (BOX){
        case 1:
            drawCross(START_X + LENGTH_BOX / 2, START_Y + 5 * LENGTH_BOX / 2);
            break;
        case 2:
            drawCross(START_X + 3 * LENGTH_BOX / 2, START_Y + 5 * LENGTH_BOX / 2);
            break;
        case 3:
            drawCross(START_X + 5 * LENGTH_BOX / 2, START_Y + 5 * LENGTH_BOX / 2);
            break;
        case 4:
            drawCross(START_X + LENGTH_BOX / 2, START_Y + 3 * LENGTH_BOX / 2);
            break;
        case 5:
            drawCross(START_X + 3 * LENGTH_BOX / 2, START_Y + 3 * LENGTH_BOX / 2);
            break;
        case 6:
            drawCross(START_X + 5 * LENGTH_BOX / 2, START_Y + 3 * LENGTH_BOX / 2);
            break;
        case 7:
            drawCross(START_X + LENGTH_BOX / 2, START_Y + LENGTH_BOX / 2);
            break;
        case 8:
            drawCross(START_X + 3 * LENGTH_BOX / 2, START_Y + LENGTH_BOX / 2);
            break;
        case 9:
            drawCross(START_X + 5 * LENGTH_BOX / 2, START_Y + LENGTH_BOX / 2);
            break;
    }
}
void playCircle(int BOX){
    float x = 0;
    float y = 0;
    switch (BOX){
        case 1:
            x = START_X + LENGTH_BOX / 2;
            y = START_Y + LENGTH_BOX * 2 + OFFSET;
            break;
        case 2:
            x = START_X + 3 * LENGTH_BOX / 2;
            y = START_Y + LENGTH_BOX * 2 + OFFSET;
            break;
        case 3:
            x = START_X + 5 * LENGTH_BOX / 2;
            y = START_Y + LENGTH_BOX * 2 + OFFSET;
            break;
        case 4:
            x = START_X + LENGTH_BOX / 2;
            y = START_Y + LENGTH_BOX * 2 + OFFSET;
            break;
        case 5:
            x = START_X + 3 * LENGTH_BOX / 2;
            y = START_Y + LENGTH_BOX * 2 + OFFSET;
            break;
        case 6:
            x = START_X + 5 * LENGTH_BOX / 2;
            y = START_Y + LENGTH_BOX * 2 + OFFSET;
            break;
        case 7:
            x = START_X + LENGTH_BOX / 2;
            y = START_Y + LENGTH_BOX * 2 + OFFSET;
            break;
        case 8:
            x = START_X + 3 * LENGTH_BOX / 2;
            y = START_Y + LENGTH_BOX * 2 + OFFSET;
            break;
        case 9:
            x = START_X + 5 * LENGTH_BOX / 2;
            y = START_Y + LENGTH_BOX * 2 + OFFSET;
            break;
    }
    drawCircle(x, y, False, Complete_Circle, Radius);
}
void play(){
    drawGrid();
    unsigned char data = Bluetooth_Receive();
}
#endif