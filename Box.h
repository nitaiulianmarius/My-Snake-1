#ifndef BOX_H
#define BOX_H

class Box
{
    sf::RectangleShape rectangle;
    int lenght;
    float resist;

public:
    Box(int width):lenght(width*0.2), resist(0)
    {
        rectangle.setSize(sf::Vector2f(lenght, lenght));
    }

    void setResist(float res)
    {
        resist = res;
        rectangle.setFillColor(sf::Color(res*5, (50-res)*5, 0));
    }

    float getResist()
    {
        return resist;
    }

    void setPosition(float x, float y)
    {
        rectangle.setPosition(x, y);
    }

    sf::Vector2f getPosition()
    {
        return rectangle.getPosition();
    }

    sf::RectangleShape getImage()
    {
        return rectangle;
    }

    void update(int h)
    {
        rectangle.move(0, h*0.007);
    }


};

#endif // BOX_H
