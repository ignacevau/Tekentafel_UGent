#include <pen.h>
#include <util/delay.h>

// The delay needed for servo3 to rise the pencil from the board
#define HIGH 1.02


void elevatePencil() {
    penDown = False;
    delay3 = HIGH;

    // Give time for the pencil to go up
    _delay_ms(500);
}

void dropPencil(float x, float y) {
    goToCoords(x, y);
    // Give time for the pencil to reach the coords
    _delay_ms(500);

    penDown = True;
    delay3 = getCorrectedPencilHeight(x, y, LOW, LOW_OFFSET);

    // Give time for the pencil to go down
    _delay_ms(500);
}