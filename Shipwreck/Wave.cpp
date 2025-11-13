#include "wave.h"


// This the constructor and it is called when we create an object
Wave::Wave(float startX, float startY)
{
    position.x = startX;
    position.y = startY;

    w_texture.loadFromFile("assets/WavesHalf.png");
    waveShape.setTexture(&w_texture);
    waveShape.setSize(sf::Vector2f(5000, 100));
    waveShape.setPosition(position);


}
FloatRect Wave::getPosition()
{
    return waveShape.getGlobalBounds();
}

RectangleShape Wave::getShape()
{
    return waveShape;
}

float Wave::waveYpos()
{
    return position.y;
}

void Wave::waveHitShip()
{
    position.x = 0;
    position.y = 0;

}

void Wave::waveStop()
{
    position.y = 0;
}

void Wave::resetPosition()
{
    position.y = 0;
    position.x = -3076;
}

void Wave::setPos1()
{
    position.x = 0;
}

void Wave::setPos2()
{
    position.x = -500;
}

void Wave::update()
{
    // Update the ball position variables
    position.y += yVelocity;
    

    // Move the ball and the bat
    waveShape.setPosition(position);
}