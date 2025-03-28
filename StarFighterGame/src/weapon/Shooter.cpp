#include "weapon/Shooter.h"

namespace st 
{
    Shooter::Shooter(Actor* owner)
        : mOwner{ owner }
    {
    }

    void Shooter::Shoot()
    {
        if (CanShoot() && !IsOnCooldown()) {
            ShootImpl(); // child class implementation
        }
    }
}