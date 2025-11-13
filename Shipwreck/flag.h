#pragma once
#include <SFML/Graphics.hpp>

// Setting up of the Flag class
using namespace sf;

class Flag
{
private:
    Vector2f position;

    // A RectangleShape object called ref
    RectangleShape flagShape;
    Texture f_texture;

    RectangleShape finish;

    float yVelocity = .9f;
    float xVelocity = .2f;

public:
    Flag(float startX, float startY);

    FloatRect getPosition();
    
    FloatRect getFinPosition();

    float waveYpos();

    RectangleShape getShape();

    RectangleShape getfinish();

    void waveHitShip();

    void resetPosition();

    void setPos1();

    void setPos2();

    void update();

};