#ifndef GOLD_H
#define GOLD_H

class Gold
{
    sf::CircleShape circle;
    int value;

public:
    Gold(sf::Vector2f pos, int v, int width)
    {
        circle.setPosition(pos);
        value = v;
        circle.setRadius(width*0.025);
        circle.setFillColor(sf::Color::Yellow);
        circle.setOrigin(circle.getGlobalBounds().width*0.5, circle.getGlobalBounds().height*0.5);
    }

    sf::CircleShape getImage()
    {
        return circle;
    }

    sf::Vector2f getPosition()
    {
        return circle.getPosition();
    }

    int getValue()
    {
        return value;
    }

    void update(int h)
    {
        circle.move(0, h*0.007);
    }
};
#endif // GOLD_H
