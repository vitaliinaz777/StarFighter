#include "enemy/EnemySpaceship.h"

namespace st
{
    EnemySpaceship::EnemySpaceship(World* owningWorld, const std::string& texturePath, float collisionDamage)
        : Spaceship{owningWorld, texturePath}, 
        mCollisionDamage{ collisionDamage }
    {
        SetTeamID(2);
    }

    EnemySpaceship::~EnemySpaceship()
    {
    }

    void EnemySpaceship::Tick(float deltaTime)
    {
        Spaceship::Tick(deltaTime);
        if (IsActorOutOfWindowBounds(GetActorGlobalBounds().width)) {
            Destroy();
        }
    }

    // The player spaceship will explode when he hits an enemy spaceship
    void EnemySpaceship::OnActorBeginOverlap(Actor* other)
    {
        Spaceship::OnActorBeginOverlap(other);
        if (IsOtherHostile(other)) {
            other->ApplyDamage(mCollisionDamage);
        }
    }
}