#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class EasterBall
{
private:
    Vector2f position;

    // A RectangleShape object called ref
    RectangleShape ballShape;

    Texture b_Texture;

    float xVelocity = .5f;
    float yVelocity = .5f;

public:
    EasterBall(float startX, float startY);

    FloatRect getPosition();

    RectangleShape getShape();

    float getXVelocity();

    void increaseSpeed();

    void resetSpeed();

    void reboundSides();

    void reboundBatOrTop();

    void hitBottom();

    void update();

};