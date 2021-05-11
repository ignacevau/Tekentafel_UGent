#include <game.h>
#include <pen.h>
#include <bluetooth/bluetooth.h>
#include <avr/io.h>
#include <draw.h>
#include <util/delay.h>
#include <shapes/bezier.h>
#include <shapes/circle.h>
#include <shapes/line.h>
#include <shapes/rectangle.h>

#define LENGTH_GRID 12.0
#define LENGTH_BOX (LENGTH_GRID/3)
#define START_X 2.0
#define START_Y 2.0
#define OFFSET 0.5
#define Radius ((LENGTH_BOX - 2 * OFFSET) /2)


/**
 * @brief Raise the pencil, draw a single line from point 1 to point 2 and raise the pencil again
 * 
 * @param x1 x value point 1
 * @param y1 y value point 1
 * @param x2 x value point 2
 * @param y2 y value point 2
 */
static void drawSingleLine(float x1, float y1, float x2, float y2);

/**
 * @brief Draw the playing grid for the Tic Tac Toe game
 * 
 */
static void drawGrid();

/**
 * @brief Draw a cross on the playing grid at the given coordinates
 * 
 * @param x x value center cross
 * @param y y value center cross
 */
static void drawCross(float x, float y);

/**
 * @brief Make a move for player X
 * 
 * @param BOX int between 1-9 at which grid position the player makes the move
 */
static void playCross(int BOX);

/**
 * @brief Make a move for player O
 * 
 * @param BOX int between 1-9 at which grid position the player makes the move
 */
static void playCircle(int BOX);

/**
 * @brief Raise the pen and position it above the center of the playing field
 * 
 */
static void goToCenter();

/**
 * @brief Write above the playing field who won the game
 * 
 * @param x Did player X win the game
 */
static void drawWinText(bool x);

/**
 * @brief Write the text "TIE" above the playing field
 * 
 */
static void drawTieText();

/**
 * @brief Interpret a bluetooth command sent by the Android application
 * 
 * @param data The bluetooth command (8 bits)
 * @result Returns True if a stop command was given
 */
static bool HandleBluetoothCommand(unsigned char data);


static void drawSingleLine(float x1, float y1, float x2, float y2) {
    elevatePencil();
    dropPencil(x1, y1);

    drawLine(x1, y1, x2, y2);
    
    elevatePencil();
}

static void drawGrid() {
    drawSingleLine(LENGTH_GRID / 3 + 2, 2, LENGTH_GRID / 3 + 2, 14);
    drawSingleLine(2 * LENGTH_GRID / 3 + 2, 2, 2 * LENGTH_GRID / 3 + 2, 14);
    drawSingleLine(2, LENGTH_GRID / 3 + 2, 14,  LENGTH_GRID / 3 + 2);
    drawSingleLine(2, 2 * LENGTH_GRID / 3 + 2, 14, 2 * LENGTH_GRID / 3 + 2);
    goToCenter();
}

static void drawCross(float x, float y){
    drawSingleLine(x - LENGTH_BOX / 2 + OFFSET, y - LENGTH_BOX / 2 + OFFSET, x + LENGTH_BOX / 2 - OFFSET, y + LENGTH_BOX / 2 - OFFSET);
    drawSingleLine(x - LENGTH_BOX / 2 + OFFSET, y + LENGTH_BOX / 2 - OFFSET, x + LENGTH_BOX / 2 - OFFSET, y - LENGTH_BOX / 2 + OFFSET);
}

static void playCross(int BOX){
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

static void playCircle(int BOX){
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

    struct circleOptions options;
    options.x0 = x;
    options.y0 = y+Radius;
    options.clockwise = False;
    options.section = 1;
    options.r = Radius;
    drawCircle(options);

    elevatePencil();

    goToCenter();
}

static void goToCenter() {
    elevatePencil();

    goToCoords(OFFSET + LENGTH_GRID / 2, OFFSET + LENGTH_GRID / 2);
}

static void drawWinText(bool x) {
    // X won
    if (x) {
        // Draw letter X
        drawSingleLine(2.5, 15.5, 3.5, 14.5);
        drawSingleLine(2.5, 14.5, 3.5, 15.5);
    }
    // O won
    else {
        // Draw letter O
        dropPencil(3.7, 15);
        
        struct circleOptions options;
        options.x0 = 3;
        options.y0 = 15;
        options.clockwise = True;
        options.section = 1;
        options.r = 0.7;
        drawCircle(options);

        elevatePencil();
    }

    // Draw letter W
    dropPencil(4.5, 15.5);
    drawLine(4.5, 15.5, 5, 14.5);
    drawLine(4.9, 14.5, 5.2, 15);
    drawLine(5.2, 15, 5.5, 15);
    drawLine(5.5, 14.5, 5.9, 15.5);
    elevatePencil();

    // Draw letter I
    drawSingleLine(6.2, 14.5, 6.2, 15.4);
    dropPencil(6.2, 15.6);
    elevatePencil();

    // Draw letter N
    dropPencil(6.5, 14.5);
    drawLine(6.5, 14.5, 6.5, 15.5);
    drawLine(6.5, 15.5, 7.0, 14.5);
    drawLine(7.0, 14.5, 7.0, 15.5);
    elevatePencil();

    // Draw letter T
    drawSingleLine(7.3, 15.5, 8.0, 15.5);
    drawSingleLine(7.7, 15.5, 7.7, 14.5);
}

static void drawTieText() {
    // Draw letter T
    drawSingleLine(3.5, 15.5, 4.3, 15.5);
    drawSingleLine(3.9, 15.5, 3.9, 14.5);

    // Draw letter I
    drawSingleLine(4.5, 14.5, 4.5, 15.4);
    dropPencil(4.5, 15.6);
    elevatePencil();

    // Draw letter E
    drawSingleLine(4.8, 15.5, 4.8, 14.5);
    drawSingleLine(4.8, 15.5, 5.3, 15.5);
    drawSingleLine(4.8, 15, 5.3, 15);
    drawSingleLine(4.8, 14.5, 5.3, 14.5);
}

static bool HandleBluetoothCommand(unsigned char data) {
    unsigned char xx = data >> 6;
    unsigned char yyyy = (data & 0b00111100)>>2;

    // Stop command
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

    // Draw X
    if (xx == 0b11) {
        playCross(yyyy);
    }
    // Draw O
    if (xx == 0b10) {
        playCircle(yyyy);
    }

    return False;
}


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