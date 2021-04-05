#include <Game.h>
#include <DwengoUtil.h>
#include <util/delay.h>
#include <avr/io.h>

int main(void)
{
    // Zet registers goed
    setRegisters();
    setOCR(PERIODE);

    while (1)
    {
        // drawPartialCircle(6.0f, 6.0f, True, 1.0f, 4.5f, 4.5f);
        if(Bluetooth_Receive() == 0){
        play();
        }
    }

    return 0;
}