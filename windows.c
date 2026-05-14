/*
5/14/26
mouse jiggler for windows
*/

#include <windows.h>
#include <stdio.h>

int main(void)
{
    printf("mouse jiggler running\n");

    while (1)
    {
        INPUT input = {0};

        input.type = INPUT_MOUSE;
        input.mi.dx = 4;
        input.mi.dy = 0;
        input.mi.dwFlags = MOUSEEVENTF_MOVE;

        SendInput(1, &input, sizeof(INPUT));

        Sleep(1000);

        input.mi.dx = -4;
        input.mi.dy = 0;
        input.mi.dwFlags = MOUSEEVENTF_MOVE;

        SendInput(1, &input, sizeof(INPUT));
        Sleep(10000);
    }
    return 0;
}