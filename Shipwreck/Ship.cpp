#include "ship.h"

// This the constructor and it is called when we create an object
Ship::Ship(float startX, float startY)
{
    position.x = startX;
    position.y = startY;

    //collision ship
    shipShape.setSize(sf::Vector2f(25, 60));
    shipShape.setPosition(position + (sf::Vector2f(37, 15)));
    shipShape.setFillColor(sf::Color(255, 128, 182, 255));
    
    
    //visable ship
    s_Texture.loadFromFile("assets/RowBoatC.png");
    s_Sprite.setTexture(s_Texture);
    s_Sprite.setPosition(position);
    s_Sprite.setScale(sf::Vector2f(0.2, 0.2));
    
}
FloatRect Ship::getPosition()
{
    
    return shipShape.getGlobalBounds();
}

Sprite Ship::getSprite()
{
    return s_Sprite;
}


RectangleShape Ship::getShape()
{
    return shipShape;
}

void Ship::reboundRight()
{
    position.x -= shipSpeed;
}

void Ship::reboundLeft()
{
    position.x += shipSpeed;
}

void Ship::resetPosition()
{
    position.x = 512;
    position.y = 650;
}

void Ship::shipHitRock()
{
    if (Keyboard::isKeyPressed(Keyboard::Up))
    {
        position.y += 7;

    }

    if (Keyboard::isKeyPressed(Keyboard::Down))
    {
        position.y -= 7;
 
    }

    if (Keyboard::isKeyPressed(Keyboard::Left))
    {
        position.x += 7;

    }

    if (Keyboard::isKeyPressed(Keyboard::Right))
    {
        position.x -= 7;
        

    }
}




void Ship::moveLeft()
{
    position.x -= shipSpeed;
}

void Ship::moveRight()
{
    position.x += shipSpeed;
}

void Ship::moveUp()
{
    position.y -= shipSpeed;
}

void Ship::moveDown()
{
    position.y += shipSpeed;
}

void Ship::reduceSpeed()
{
    shipSpeed = 0.6f;
}

void Ship::shipStop()
{
    shipSpeed = .0f;
}

void Ship::update()
{
    s_Sprite.setPosition(position);
    shipShape.setPosition(position + (sf::Vector2f(37, 15)));
}