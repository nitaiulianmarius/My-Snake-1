#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <SFML/Graphics.hpp>
#include <vector>

class stateMachine
{
    bool sound;

    sf::RenderWindow *window;
    sf::Event event;
    sf::Texture menuBackgroundTexture;
    sf::Sprite menuBackgroundSprite;
    sf::Music backgroundMusic;

    sf::Font font;
    sf::Text text;

public:
    stateMachine(){};

    virtual void handleEvent(sf::RenderWindow*,std::vector<stateMachine*>&) = 0;
    virtual void update(sf::RenderWindow*,std::vector<stateMachine*>&) = 0;
    virtual void render(sf::RenderWindow*&) = 0;
};

#endif // STATEMACHINE_H
