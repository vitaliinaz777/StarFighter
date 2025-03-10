#include "spaceship/Spaceship.h"

namespace st
{
    Spaceship::Spaceship(World* owningWorld, const std::string& texturePath)
        : Actor{ owningWorld, texturePath },
        mVelocity{ 0.0f, 0.0f }
    {
    }
    void Spaceship::Tick(float deltaTime)
    {
        Actor::Tick(deltaTime);

        AddActorLocationOffset(GetVelocity() * deltaTime); // Move the spaceship
    }
    void Spaceship::SetVelocity(const sf::Vector2f& newVel)
    {
        mVelocity = newVel;
    }
    void Spaceship::Shoot()
    {
    }
}