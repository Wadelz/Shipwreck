#include "Rock.h"
#include "Ship.h"

// This the constructor and it is called when we create an object
Rock::Rock(float rockX, float rockY)
{
    position.x = rockX;
    position.y = rockY;

    if (!r_Texture.loadFromFile("assets/textures/Rock2_1.png")) {
        // texture load failed; proceed without texture to avoid warning/crash
    }
    rockShape.setTexture(&r_Texture);
    rockShape.setSize(sf::Vector2f(100, 100));
    rockShape.setPosition(position);

    //safe zone
    safeZone.setSize(sf::Vector2f(70, 768));
    safeZone.setPosition(position + (sf::Vector2f(15, 75)));

    //overlay
    if (!o_Texture.loadFromFile("assets/textures/WaveFade.png")) {
        // overlay texture failed to load
    }
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