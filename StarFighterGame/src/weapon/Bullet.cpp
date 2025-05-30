#include "weapon/Bullet.h"

namespace st
{
    Bullet::Bullet(World* world, Actor* owner, const std::string& texturePath, 
                   float speed, float damage)
        : Actor{ world, texturePath },
        mOwner{ owner },
        mSpeed{ speed },
        mDamage{ damage }
    {
        SetTeamID(owner->GetTeamID()); // TeamID of Spaceship
    }

    void Bullet::SetSpeed(float newSpeed)
    {
        mSpeed = newSpeed;
    }

    void Bullet::SetDamage(float newDamage)
    {
        mDamage = newDamage;
    }

    void Bullet::Tick(float deltaTime)
    {
        Actor::Tick(deltaTime);
        Move(deltaTime);
        if (IsActorOutOfWindowBounds()) {
            Destroy();
        }
    }

    void Bullet::BeginPlay()
    {
        Actor::BeginPlay();
        SetEnablePhysics(true);
    }

    // Signaled by PhysicsContactListener::BeginContact()
    void Bullet::OnActorBeginOverlap(Actor* other)
    {
        // if 'other' is an enemy apply damage
        if (IsOtherHostile(other)) {
            other->ApplyDamage(GetDamage());
            Destroy(); // destoy itself (bullet)
        }
    }

    void Bullet::Move(float deltaTime)
    {
        AddActorLocationOffset(GetActorForwardDirection() * mSpeed * deltaTime);
    }
}