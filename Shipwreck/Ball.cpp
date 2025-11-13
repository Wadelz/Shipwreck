#include "easterBall.h"

// This the constructor and it is called when we create an object
EasterBall::EasterBall(float startX, float startY)
{
    position.x = startX;
    position.y = startY;

    b_Texture.loadFromFile("assets/easterBeachBall.png");
    ballShape.setTexture(&b_Texture);
    ballShape.setSize(sf::Vector2f(100, 100));
    ballShape.setPosition(position);
    ballShape.setSize(sf::Vector2f(100, 100));
    ballShape.setPosition(position);
    
}
FloatRect EasterBall::getPosition()
{
    return ballShape.getGlobalBounds();
}

RectangleShape EasterBall::getShape()
{
    return ballShape;
}

float EasterBall::getXVelocity()
{
    return xVelocity;
}

void EasterBall::reboundSides()
{
    xVelocity = -xVelocity;
}

void EasterBall::reboundBatOrTop()
{
    position.y -= (yVelocity);
    yVelocity = -yVelocity;

}

void EasterBall::increaseSpeed()
{
    yVelocity = .5f;
    xVelocity = .5f;
}

void EasterBall::resetSpeed()
{
    yVelocity = .2f;
    xVelocity = .2f;
}

void EasterBall::hitBottom()
{
   
    yVelocity = -yVelocity;
}

void EasterBall::update()
{
    // Update the ball position variables
    position.y += yVelocity;
    position.x += xVelocity;

    // Move the ball and the bat
    ballShape.setPosition(position);
}