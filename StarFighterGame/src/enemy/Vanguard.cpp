#include "enemy/Vanguard.h"
//#include "weapon/BulletShooter.h"

namespace st
{
    Vanguard::Vanguard(World* owningWorld, const std::string& texturePath, const sf::Vector2f& velocity)
        : EnemySpaceship{owningWorld, texturePath},
        mShooter{ new BulletShooter{this} }
    {
        SetVelocity(velocity);
        SetActorRotation(90.f);
    }

    void Vanguard::Tick(float deltaTime)
    {
        EnemySpaceship::Tick(deltaTime);
        Shoot();
    }

    void Vanguard::Shoot()
    {
        if (mShooter) {
            mShooter->Shoot();
        }
    }
}