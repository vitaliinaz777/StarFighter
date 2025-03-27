#include "weapon/Shooter.h"

namespace st 
{
    void Shooter::Shoot()
    {
        if (CanShoot() && !IsOnCooldown()) {
            ShootImpl(); // child class implementation
        }
    }

    Shooter::Shooter(Actor* owner)
        : mOwner{ owner }
    {
    }
}