/*
5/14/26
mouse jiggler for windows
*/

#include <windows.h>
#include <stdio.h>
#include <conio.h>

int main(void)
{
    printf("mouse jiggler running. Press q or esc to quit\n");

    while (1)
    {
        INPUT input = {0};

        input.type = INPUT_MOUSE;
        input.mi.dx = 4;
        input.mi.dy = 0;
        input.mi.dwFlags = MOUSEEVENTF_MOVE;

        SendInput(1, &input, sizeof(INPUT));

        Sleep(100);

        input.mi.dx = -4;
        input.mi.dy = 0;
        input.mi.dwFlags = MOUSEEVENTF_MOVE;

        SendInput(1, &input, sizeof(INPUT));

        for (int i = 0; i < 200; i++)
        {
            Sleep(50);
            if (_kbhit())
            {
                int key = _getch();
                if (key == 'q' || key == 'Q' || key == 27)
                {
                    printf("Exiting\n");
                    return 0;
                }
            }
        }
    }
    return 0;
}