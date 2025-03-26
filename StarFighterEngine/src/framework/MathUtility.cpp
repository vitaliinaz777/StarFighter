#include "framework/MathUtility.h"
#include <random>

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
    float LerpFloat(float a, float b, float alpha) 
    {
        if (alpha > 1) alpha = 1;
        if (alpha < 0) alpha = 0;

        return a + (b - a) * alpha;
    }

    sf::Color LerpColor(const sf::Color& a, const sf::Color& b, float alpha, float alphaFactor)
    {
        float alphaF = alpha / alphaFactor;

        int lerpR = LerpFloat(a.r, b.r, alphaF);
        int lerpG = LerpFloat(a.g, b.g, alphaF);
        int lerpB = LerpFloat(a.b, b.b, alphaF);
        int lerpA = LerpFloat(a.a, b.a, alphaF);

        return sf::Color(lerpR, lerpG, lerpB, lerpA);
    }

    sf::Vector2f LerpVector(const sf::Vector2f& a, const sf::Vector2f& b, float alpha, float alphaFactor)
    {
        float alphaF = alpha * alphaFactor;

        float lerpX = LerpFloat(a.x, b.x, alphaF);
        float lerpY = LerpFloat(a.y, b.y, alphaF);

        return sf::Vector2f(lerpX, lerpY);
    }

    float RandomRange(float min, float max)
    {
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_real_distribution<float> distribution{ min, max };

        return distribution(generator);
    }

    sf::Vector2f RandomUnitVector()
    {
        float randomX = RandomRange(-1, 1);
        float randomY = RandomRange(-1, 1);
        sf::Vector2f randomVec{ randomX, randomY };
        Normalize(randomVec);
        
        return randomVec;
    }
}