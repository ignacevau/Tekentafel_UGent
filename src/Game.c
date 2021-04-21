#ifndef _Game_Header_
#define _Game_Header_
#include <Game.h>
#include <Bluetooth/Bluetooth.h>
#include <avr/io.h>
#include <Draw.h>
#include <util/delay.h>

#define LENGTH_GRID 12.0
#define LENGTH_BOX (LENGTH_GRID/3)
#define START_X 2.0
#define START_Y 2.0
#define OFFSET 0.5
#define Complete_Circle 1
#define Radius ((LENGTH_BOX - OFFSET) /2)
// Servo 3
#define GoHIGH True
#define HIGH 1.2

#define GoLOW False
#define LOW 1.05



// Hier kunnen we volledige tekeningen maken (door de arm opheffen enzo)
void setDelay3(bool up){
    if (up){
        delay3 = HIGH;
    }
    else{
        delay3 = LOW;
    }
    
}
void elevatePencil(){
    setDelay3(GoHIGH);
    _delay_ms(500);
}
void dropPencil(float x, float y){
    goToCoords(x, y);
    _delay_ms(500);
    setDelay3(GoLOW);
    _delay_ms(500);
}

void drawSingleLine(float x1, float y1, float x2, float y2) {
    elevatePencil();
    dropPencil(x1, y1);
    drawLine(x1, y1, x2, y1);
    elevatePencil();
}

void drawGrid(){
    drawSingleLine(LENGTH_GRID / 3 + 2, 2, LENGTH_GRID / 3 + 2, 14);
    drawSingleLine(2 * LENGTH_GRID / 3 + 2, 2, 2 * LENGTH_GRID / 3 + 2, 14);
    drawSingleLine(2, LENGTH_GRID / 3 + 2, 14,  LENGTH_GRID / 3 + 2);
    drawSingleLine(2, 2 * LENGTH_GRID / 3 + 2, 14, 2 * LENGTH_GRID / 3 + 2);
    goToCenter();
}

void drawCross(float x, float y){
    drawSingleLine(x - LENGTH_BOX / 2 + OFFSET, y - LENGTH_BOX / 2 + OFFSET, x + LENGTH_BOX / 2 - OFFSET, y + LENGTH_BOX / 2 - OFFSET);
    drawSingleLine(x - LENGTH_BOX / 2 + OFFSET, y + LENGTH_BOX / 2 - OFFSET, x + LENGTH_BOX / 2 - OFFSET, y - LENGTH_BOX / 2 + OFFSET);
}

void goToCenter(){
    // hef op
    goToCoords(OFFSET + LENGTH_GRID / 2, OFFSET + LENGTH_GRID / 2);
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

    goToCenter();
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
    elevatePencil();
    dropPencil(x, y);
    drawCircle(x, y, False, Complete_Circle, Radius);
    elevatePencil();

    goToCenter();
}

// Returnt True als data het stop commando is
bool HandleBluetoothCommand(unsigned char data) {
    unsigned char xx = data >> 6;
    unsigned char yyyy = (data & 0b00111100)>>2;

    // Stop commando
    if (xx == 0b01)
        return True;

    // Teken X
    if (xx == 0b11) {
        playCross(yyyy);
    }
    // Teken O
    if (xx == 0b10) {
        playCircle(yyyy);
    }

    return False;
}

void play() {
    unsigned char startData = Bluetooth_Receive();
    if (startData == 0) {
        drawGrid();

        while(1) {
            unsigned char data = Bluetooth_Receive();

            bool stop = HandleBluetoothCommand(data);

            if (stop){
                goToCenter();
                break;
            }
        }
    }
}
#endif