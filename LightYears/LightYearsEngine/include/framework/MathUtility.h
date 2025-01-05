#pragma once
#include<SFML/Graphics.hpp>
#include<cmath>

namespace ly
{
    sf::Vector2f RotationToVector(float rotation);
    float DegreesToRadians(float degrees);
    float RadiansToDegrees(float radians);
}