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

    // lerp(start, finish, alpha) = start * (1 - alpha) + finish * alpha
    float LerpFloat(float a, float b, float alpha) {
        if (alpha > 1) alpha = 1;
        if (alpha < 0) alpha = 0;

        return a + (b - a) * alpha;
    }

    sf::Color LerpColor(const sf::Color& a, const sf::Color& b, float alpha) {
        int lerpR = LerpFloat(a.r, b.r, alpha);
        int lerpG = LerpFloat(a.g, b.g, alpha);
        int lerpB = LerpFloat(a.b, b.b, alpha);
        int lerpA = LerpFloat(a.a, b.a, alpha);

        return sf::Color(lerpR, lerpG, lerpB, lerpA);
    }

    sf::Vector2f LerpVector(const sf::Vector2f& a, const sf::Vector2f& b, float alpha) {
        int lerpX = LerpFloat(a.x, b.x, alpha);
        int lerpY = LerpFloat(a.y, b.y, alpha);

        return sf::Vector2f(lerpX, lerpY);
    }
}