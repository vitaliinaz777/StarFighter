#include "framework/MathUtility.h"

namespace st {
    const float PI = 3.14159265359f;

    // Convert rotation in degrees to a unit vector
    sf::Vector2f RotationToVector(float rotation)
    {
        float radians = DegreesToRadians(rotation);
        return sf::Vector2f(std::cos(radians), std::sin(radians));
    }

    float DegreesToRadians(float degrees)
    {
        return degrees * PI / 180.0f;
    }

    float RadiansToDegrees(float radians)
    {
        return radians * 180.0f / PI;
    }
}