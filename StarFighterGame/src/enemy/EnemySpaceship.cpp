#include "enemy/EnemySpaceship.h"

namespace st
{
    EnemySpaceship::EnemySpaceship(World* owningWorld, const std::string& texturePath, float collisionDamage)
        : Spaceship{owningWorld, texturePath}, 
        mCollisionDamage{ collisionDamage }
    {
        SetTeamID(2);
    }

    void EnemySpaceship::Tick(float deltaTime)
    {
        Spaceship::Tick(deltaTime);
        if (IsActorOutOfWindowBounds(GetActorGlobalBounds().width)) {
            Destroy();
        }
    }

    // The player will explode when he hits an enemy.
    void EnemySpaceship::OnActorBeginOverlap(Actor* other)
    {
        Spaceship::OnActorBeginOverlap(other);
        if (IsOtherHostile(other)) {
            other->ApplyDamage(mCollisionDamage);
        }
    }
}