#pragma once

namespace st
{
    // forward declaration
    class Actor;

    // Abstract class. It will be added to Spaceships as a "component"
    class Shooter {
    public:
        void Shoot(); // shoot interface

        virtual bool CanShoot() const { return true; }
        virtual bool IsOnCooldown() const { return false; }
        Actor* GetOwner() const { return mOwner; }

    protected:
        Shooter(Actor* owner);

    private:
        virtual void ShootImpl() = 0; // pure virtual function make this class abstract
        Actor* mOwner;
    };
}