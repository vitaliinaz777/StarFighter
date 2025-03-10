#pragma once
#include <SFML/Graphics.hpp>

namespace st {
    sf::Vector2f RotationToVector(float rotation);
    float DegreesToRadians(float degrees);
    float RadiansToDegrees(float radians);

    template<typename T>
    float GetVectorLength(const sf::Vector2<T> vector) {
        return sqrt(vector.x * vector.x + vector.y * vector.y);
    }

    template<typename T>
    sf::Vector2<T>& ScaleVector(sf::Vector2<T>& vectorToScale, float scale) {
        vectorToScale.x *= scale;
        vectorToScale.y *= scale;

        return vectorToScale;
    }

    template<typename T>
    sf::Vector2<T> Normalize(sf::Vector2<T>& vector) {
        float vectorLeangth = GetVectorLength<T>(vector);
        if (vectorLeangth == 0.f) return sf::Vector2<T>{0.f, 0.f};

        // Normalize the vector
        ScaleVector(vector, 1.0 / vectorLeangth);

        // It could be done like this:
        // vectorToScale.x /= vectorLeangth;
        // vectorToScale.y /= vectorLeangth;

        return vector;
    }
}