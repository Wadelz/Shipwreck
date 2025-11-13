#include "Flag.h"


// This the constructor of the flag object
Flag::Flag(float startX, float startY)
{
    // Starting position
    position.x = startX;
    position.y = startY;

    // Setting texture, size and position for flags
    f_texture.loadFromFile("assets/textures/Flag2k.png");
    flagShape.setTexture(&f_texture);
    flagShape.setSize(sf::Vector2f(6400, 100));
    flagShape.setPosition(position);

    // Setting colour, size and position for finish line in flags
    finish.setSize(sf::Vector2f(150, 10));
    finish.setFillColor(sf::Color(255, 0, 0, 255));
    finish.setPosition(position + (sf::Vector2f(5, 60)));

}

// Getting position of flags
FloatRect Flag::getPosition()
{
    return flagShape.getGlobalBounds();
}

// Getting position of finish line between flags
FloatRect Flag::getFinPosition()
{
    return finish.getGlobalBounds();
}

// Getting shape for drawing of object
RectangleShape Flag::getShape()
{
    return flagShape;
}

// Getting shape for drawing of object
RectangleShape Flag::getfinish()
{
    return finish;
}

float Flag::waveYpos()
{
    return position.y;
}

void Flag::waveHitShip()
{
    position.x = 0;
    position.y = 0;
}

void Flag::resetPosition()
{
    position.y = 0;
    position.x = -3076;
}

void Flag::setPos1()
{
    position.x = 315;
}

void Flag::setPos2()
{
    position.x = -5885;
}

void Flag::update()
{
    flagShape.setPosition(position);
}