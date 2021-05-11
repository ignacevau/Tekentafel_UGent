#include <game.h>
#include <dwengo_util.h>


int main(void)
{
    // Setup registers
    setRegisters();
    setOCR(PERIODE);

    // Start game
    while (1)
    {
        play();
    }

    return 0;
}