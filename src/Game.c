#include <Game.h>
#include <pen.h>
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
#define Radius ((LENGTH_BOX - 2 * OFFSET) /2)


// Raise the pencil, draw a single line from point 1 to point 2 and raise the pencil again
void drawSingleLine(float x1, float y1, float x2, float y2) {
    elevatePencil();
    dropPencil(x1, y1);
    drawLine(x1, y1, x2, y2);
    elevatePencil();
}

// Draw the playing grid for the Tic Tac Toe game
void drawGrid() {
    drawSingleLine(LENGTH_GRID / 3 + 2, 2, LENGTH_GRID / 3 + 2, 14);
    drawSingleLine(2 * LENGTH_GRID / 3 + 2, 2, 2 * LENGTH_GRID / 3 + 2, 14);
    drawSingleLine(2, LENGTH_GRID / 3 + 2, 14,  LENGTH_GRID / 3 + 2);
    drawSingleLine(2, 2 * LENGTH_GRID / 3 + 2, 14, 2 * LENGTH_GRID / 3 + 2);
    goToCenter();
}

// Draw a cross on the playing grid at the given coordinates
void drawCross(float x, float y){
    drawSingleLine(x - LENGTH_BOX / 2 + OFFSET, y - LENGTH_BOX / 2 + OFFSET, x + LENGTH_BOX / 2 - OFFSET, y + LENGTH_BOX / 2 - OFFSET);
    drawSingleLine(x - LENGTH_BOX / 2 + OFFSET, y + LENGTH_BOX / 2 - OFFSET, x + LENGTH_BOX / 2 - OFFSET, y - LENGTH_BOX / 2 + OFFSET);
}

// Write above the playing field who won the game
// @param x did player X win the game
void drawWinText(bool x) {
    // X won
    if (x) {
        // Draw X
        drawSingleLine(2.5, 15.5, 3.5, 14.5);
        drawSingleLine(2.5, 14.5, 3.5, 15.5);
    }
    // O won
    else {
        // Draw O
        dropPencil(3.7, 15);
        drawCircle(3, 15, True, 1, 0.7);
        elevatePencil();
    }

    // w
    dropPencil(4.5, 15.5);
    drawLine(4.5, 15.5, 5, 14.5);
    drawLine(4.9, 14.5, 5.2, 15);
    drawLine(5.2, 15, 5.5, 15);
    drawLine(5.5, 14.5, 5.9, 15.5);
    elevatePencil();

    // i
    drawSingleLine(6.2, 14.5, 6.2, 15.4);
    dropPencil(6.2, 15.6);
    elevatePencil();

    // n
    dropPencil(6.5, 14.5);
    drawLine(6.5, 14.5, 6.5, 15.5);
    drawLine(6.5, 15.5, 7.0, 14.5);
    drawLine(7.0, 14.5, 7.0, 15.5);
    elevatePencil();

    // t
    drawSingleLine(7.3, 15.5, 8.0, 15.5);
    drawSingleLine(7.7, 15.5, 7.7, 14.5);
}

// Write the text TIE above the playing field
void drawTieText() {
    // t
    drawSingleLine(3.5, 15.5, 4.3, 15.5);
    drawSingleLine(3.9, 15.5, 3.9, 14.5);

    // i
    drawSingleLine(4.5, 14.5, 4.5, 15.4);
    dropPencil(4.5, 15.6);
    elevatePencil();

    // e
    drawSingleLine(4.8, 15.5, 4.8, 14.5);
    drawSingleLine(4.8, 15.5, 5.3, 15.5);
    drawSingleLine(4.8, 15, 5.3, 15);
    drawSingleLine(4.8, 14.5, 5.3, 14.5);
}

// Raise the pen and position it above the center of the playing field
void goToCenter() {
    elevatePencil();

    goToCoords(OFFSET + LENGTH_GRID / 2, OFFSET + LENGTH_GRID / 2);
}

// Make a move for player X
// @param BOX int between 1-9 at which grid position the player makes the move
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

// Make a move for player O
// @param BOX int between 1-9 at which grid position the player makes the move
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
            y = START_Y + LENGTH_BOX + OFFSET;
            break;
        case 5:
            x = START_X + 3 * LENGTH_BOX / 2;
            y = START_Y + LENGTH_BOX + OFFSET;
            break;
        case 6:
            x = START_X + 5 * LENGTH_BOX / 2;
            y = START_Y + LENGTH_BOX  + OFFSET;
            break;
        case 7:
            x = START_X + LENGTH_BOX / 2;
            y = START_Y + OFFSET;
            break;
        case 8:
            x = START_X + 3 * LENGTH_BOX / 2;
            y = START_Y  + OFFSET;
            break;
        case 9:
            x = START_X + 5 * LENGTH_BOX / 2;
            y = START_Y + OFFSET;
            break;
    }
    elevatePencil();
    dropPencil(x+Radius, y+Radius);
    drawCircle(x, y+Radius, False, Complete_Circle, Radius);
    elevatePencil();

    goToCenter();
}

// Interpret a bluetooth command send by the Android application
// @param data The bluetooth command (8 bits)
// @result Returns True if a stop command was given
bool HandleBluetoothCommand(unsigned char data) {
    unsigned char xx = data >> 6;
    unsigned char yyyy = (data & 0b00111100)>>2;

    // Stop commando
    if (xx == 0b01) {
        // X won
        if (yyyy == 0b1000) {
            drawWinText(True);
        }
        // O won
        else if (yyyy == 0b0100) {
            drawWinText(False);
        }
        // Tie game
        else if (yyyy == 0b1100) {
            drawTieText();
        }

        return True;
    }

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

// Start the game loop
void play() {
    // Center drawing arm
    goToCenter();

    // Wait for bluetooth start signal
    unsigned char startData = Bluetooth_Receive();
    if (startData == 0) {
        drawGrid();

        while(1) {
            unsigned char data = Bluetooth_Receive();

            bool stop = HandleBluetoothCommand(data);

            if (stop) {
                goToCenter();
                break;
            }
        }
    }
}