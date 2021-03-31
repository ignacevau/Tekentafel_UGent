#include <Shapes.h>
#include <DwengoUtil.h>


int main(void)
{
    // zet registers goed:
    setRegisters();
    setOCR(PERIODE);

    while (1)
    {
        drawPartialCircle(6.0f, 6.0f, True, 1.0f, 4.5f, 4.5f);
    }

    return 0;
}