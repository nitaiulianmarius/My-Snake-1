#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <sstream>
#include <vector>
#include <windows.h>
#include <time.h>
#include <fstream>
#include "Box.h"
#include "Gold.h"

class Game
{
    sf::RenderWindow *window;
    sf::Event event;
    sf::Font font;
    sf::Text text;
    sf::CircleShape player;
    std::vector<Box> box;
    std::vector<Gold> gold;
    int width, height;
    int currentFPS;
    float lenght;
    float score;
    bool playerBoxCollision;
    DWORD lastGoldTime;
    DWORD globalTime;

public:
    Game(int w, int h):width(w), height(h)
    {
        window = new sf::RenderWindow(sf::VideoMode(w, h), "mySnake v1");
        currentFPS = 60;
        window->setFramerateLimit(currentFPS);

        // jucatorul
        player.setRadius(w*0.03);
        player.setFillColor(sf::Color::Blue);
        player.setPosition(w*0.5, h*0.66);
        player.setOrigin(player.getGlobalBounds().width*0.5, player.getGlobalBounds().height*0.5);

        lenght = 4;
        score = 0;


        // textul
        font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");
        text.setFont(font);

        srand(time(NULL));
        lastGoldTime = clock()-500;
        globalTime = clock();
    };

    void handleEvent();
    void update();
    void render();
    bool isOpen();
    bool onFocus();
    void outtextxy(int x, int y, int t, int size, int align);     // afisaza variabila
    void outtextxy(int x, int y, char* t, int size, int align);   // afisaza text
};

#endif // GAME_H
