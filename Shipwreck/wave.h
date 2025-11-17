#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Wave
{
private:
    Vector2f position;

    // A RectangleShape object called ref
    RectangleShape waveShape;
    Texture w_texture;

    float yVelocity = .9f;

public:
    Wave(float startX, float startY);

    FloatRect getPosition();

    float waveYpos();

    RectangleShape getShape();

    void waveHitShip();

    void waveStop();

    void resetPosition();

    void setPos1();

    void setPos2();

    void update();

};