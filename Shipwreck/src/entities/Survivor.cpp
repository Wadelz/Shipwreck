#include "Survivor.h"

// This the constructor of the survivor objects
Survivor::Survivor(float startX, float startY)
{
    position.x = startX;
    position.y = startY;

    s_Texture.loadFromFile("assets/textures/head.png");
    survivorShape.setTexture(&s_Texture);
    survivorShape.setSize(sf::Vector2f(50, 50));
    survivorShape.setPosition(position);
}

RectangleShape Survivor::getShape()
{
    return survivorShape;
}

FloatRect Survivor::getPosition()
{
    return survivorShape.getGlobalBounds();
}

void Survivor::collectSurvivor()
{
    position.x = 5000;
    position.y = 5000;
}

void Survivor::update()
{
    survivorShape.setPosition(position);
}