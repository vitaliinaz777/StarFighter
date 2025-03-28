#pragma once
#include "spaceship/Spaceship.h"

namespace st
{
    class EnemySpaceship : public Spaceship
    {
    public:
        EnemySpaceship(World* owningWorld, const std::string& texturePath, float collisionDamage = 200.f);
        virtual void Tick(float deltaTime) override;

    private:
        virtual void OnActorBeginOverlap(Actor* other) override;

        float mCollisionDamage;
    };
}