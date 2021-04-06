#ifndef _Draw_HEADER_
#define _Draw_HEADER_

#include <Draw.h>
#include <IK.h>

bool testCoord(float x, float y){
    if (x >= MIN_X && x <= MAX_X && y <= MAX_Y && y >= MIN_Y){
        return True;
    }
    return False;
}

void goToCoords(float x, float y) {
    // bereken delays
    delay1 = getDelay1(x, y);
    delay2 = getDelay2(x, y);
}
#endif