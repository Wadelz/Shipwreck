#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Rock
{
private:
    Vector2f position;

    RectangleShape rockShape;

    RectangleShape overlay;

    RectangleShape safeZone;

    Texture r_Texture;

    Texture o_Texture;

public:
    Rock(float startX, float startY);


    RectangleShape getShape();

    RectangleShape getOverlay();

    FloatRect getPosition();

    FloatRect safeZonPos();

};