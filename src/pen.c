#include <pen.h>
#include <Draw.h>

// Servo 3
#define GoHIGH True
#define HIGH 1.02

#define GoLOW False

bool penDown;


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
    penDown = False;
    setDelay3(GoHIGH);
    _delay_ms(500);
}
void dropPencil(float x, float y){
    goToCoords(x, y);
    _delay_ms(500);

    penDown = True;
    delay3 = getCorrectedPencilHeight(x, y, LOW, LOW_OFFSET);
    // setDelay3(GoLOW);
    _delay_ms(500);
}