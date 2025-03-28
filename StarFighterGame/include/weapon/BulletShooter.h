#pragma once
#include <SFML/System.hpp>
#include "weapon/Shooter.h"

namespace st 
{
    // It will be added to Spaceships as a "component"
    class BulletShooter : public Shooter {
    public:
        BulletShooter(Actor* owner, float cooldownTime = 1.f);
        virtual bool IsOnCooldown() const override;
    private:
        virtual void ShootImpl() override;
        sf::Clock mCooldownClock;
        float mCooldownTime;
    };
}
