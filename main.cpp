#include <iostream>
#include <fstream>
#include <wtypes.h>
#include <conio.h>
#include "Game.h"

using namespace std;

int main()
{
    int choose;
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);
    int screenWidth, screenHeight;
    screenWidth = desktop.right;
    screenHeight = desktop.bottom;
    ifstream f("config.mySnake");
    int bestScore, lastScore;
    f >> bestScore >> lastScore;
    f.close();

    while(kbhit()) getch();
    cout << "Best schore: " << bestScore << '\n';
    cout << "Last Score: " << lastScore << '\n';
    cout << "Your graph mode: " << screenWidth << 'x' << screenHeight << '\n';
    cout << "1. 320x480 \n";
    cout << "2. 480x720 \n";
    cout << "3. 640x960 \n";
    do
    {
        cin >> choose;
    }while(choose<1 || choose>3);

    Game *mySnake;

    if(choose == 1)
        mySnake = new Game(320, 480);
    if(choose == 2)
        mySnake = new Game(480, 720);
    if(choose == 3)
        mySnake = new Game(640, 960);

    while(mySnake->isOpen())
    {
        mySnake->handleEvent();
        mySnake->update();
        mySnake->render();
    }

    main();
    return 0;
}
