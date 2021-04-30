#include <Game.h>
#include <DwengoUtil.h>

int main(void)
{
    // Zet registers goed
    setRegisters();
    setOCR(PERIODE);


    while (1)
    {
        // Blijf spel herhalen
        play();
    }

    return 0;
}