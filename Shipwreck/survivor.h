#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Survivor
{
private:
    Vector2f position;

    RectangleShape survivorShape;

    Texture s_Texture;

public:
    Survivor(float startX, float startY);

    RectangleShape getShape();

    FloatRect getPosition();

    void collectSurvivor();

    void update();

};