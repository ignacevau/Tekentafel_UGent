#include <Draw.h>
#include <IK.h>

bool testCoord(float x, float y){
    if (x >= MIN_X && x <= MAX_X && y <= MAX_Y && y >= MIN_Y){
        return True;
    }
    return False;
}

// Pas pencil hoogte aan door rekening te houden met de doorzakking door de zwaartekracht
float getCorrectedPencilHeight(float x, float y, float low, float offset) {
    // Pas hoogte aan afhankelijk van hoe ver tweede arm gestrekt is
    return low + offset * ((delay2 - DELAY_0) / (DELAY_PI-DELAY_0));
}

void goToCoords(float x, float y) {
    // bereken delays
    delay1 = getDelay1(x, y);
    delay2 = getDelay2(x, y);
}