#include "rock.h"
#include "ship.h"

// This the constructor and it is called when we create an object
Rock::Rock(float rockX, float rockY)
{
    position.x = rockX;
    position.y = rockY;

    r_Texture.loadFromFile("assets/Rock2_1.png");
    rockShape.setTexture(&r_Texture);
    rockShape.setSize(sf::Vector2f(100, 100));
    rockShape.setPosition(position);

    //safe zone   
    safeZone.setSize(sf::Vector2f(70, 768));
    safeZone.setPosition(position + (sf::Vector2f(15, 75)));

    //overlay
    o_Texture.loadFromFile("assets/WaveFade.png");
    overlay.setTexture(&o_Texture);
    overlay.setSize(sf::Vector2f(95, 768));
    overlay.setFillColor(sf::Color(26, 128, 182, 255));
    overlay.setPosition(position + (sf::Vector2f(3, 60)));
}

RectangleShape Rock::getShape()
{
    return rockShape;
}

FloatRect Rock::getPosition()
{
    return rockShape.getGlobalBounds();
}

FloatRect Rock::safeZonPos()
{
   return safeZone.getGlobalBounds();
}

RectangleShape Rock::getOverlay()
{
    return overlay;
}