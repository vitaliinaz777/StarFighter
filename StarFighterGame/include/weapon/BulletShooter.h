#pragma once
#include <SFML/System.hpp>
#include "weapon/Shooter.h"

namespace st 
{
    // It will be added to Spaceships as a "component"
    class BulletShooter : public Shooter {
    public:
        BulletShooter(Actor* owner, float cooldownTime = 1.f, const sf::Vector2f& localPositionOffset = {0.f, 0.f}, float localRotationOffset = 0.f);
        virtual bool IsOnCooldown() const override;
    private:
        virtual void ShootImpl() override;
        sf::Clock mCooldownClock;
        float mCooldownTime;
        
        // Making offsets for two 'BulletShooter's located on one 'Spaceship'
        sf::Vector2f mLocalPositionOffset;
        float mLocalRotationOffset;
    };
}
