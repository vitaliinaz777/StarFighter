#pragma once
#include "spaceship/Spaceship.h"

namespace st
{
    class EnemySpaceship : public Spaceship
    {
    public:
        EnemySpaceship(World* owningWorld, const std::string& texturePath, float collisionDamage = 200.f);
        virtual ~EnemySpaceship();
        virtual void Tick(float deltaTime) override;

    private:
        // The player will explode when he hits an enemy.
        virtual void OnActorBeginOverlap(Actor* other) override;

        float mCollisionDamage;
    };
}