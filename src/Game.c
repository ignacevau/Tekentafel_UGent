#ifndef _Game_Header_
#define _Game_Header_
#include <Game.h>
#define LENGTH_GRID 14.0

// Hier kunnen we volledige tekeningen maken (door de arm opheffen enzo)

void DrawGrid(){
    drawLine(LENGTH_GRID / 3 + 2, 2, LENGTH_GRID / 3 + 2, 16);
    drawLine(2 * LENGTH_GRID / 3 + 2, 2, 2 * LENGTH_GRID / 3 + 2, 16);
    drawLine(2, LENGTH_GRID / 3 + 2, 16,  LENGTH_GRID / 3 + 2);
    drawLine(2, 2 * LENGTH_GRID / 3 + 2, 16, 2 * LENGTH_GRID / 3 + 2);
}

// void playCross(int BOX){
//     switch (BOX){
//         case 1:

//     }
// }
#endif