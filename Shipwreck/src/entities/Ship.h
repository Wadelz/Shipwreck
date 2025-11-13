#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Ship
{
private:
    Vector2f position;



    // A RectangleShape object
    RectangleShape shipShape;

    float shipSpeed = 1.0f;

    Sprite s_Sprite;

    Texture s_Texture;

public:
    Ship(float startX, float startY);

    FloatRect getPosition();

    RectangleShape getShape();
    
    Sprite getSprite();

    void resetPosition();

    void reboundRight();

    void reboundLeft();

    void moveLeft();

    void moveRight();

    void moveUp();
    
    void moveDown();

    void shipStop();

    void update();

    void shipHitRock();

    void reduceSpeed();

};