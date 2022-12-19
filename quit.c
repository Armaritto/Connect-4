#include <stdio.h>
#include <windows.h>

int main()
{
    HWND myWindow = GetConsoleWindow();
    printf("Hiding the window\n");
    Sleep(3000);
    ShowWindow(myWindow, SW_HIDE);
    return 0;
}
