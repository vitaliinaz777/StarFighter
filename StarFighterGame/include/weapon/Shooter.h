#pragma once

namespace st
{
    // forward declaration
    class Actor;

    // Abstract class
    class Shooter {
    public:
        void Shoot();

        virtual bool CanShoot() const { return true; }
        virtual bool IsOnCooldown() const { return false; }
        const Actor* GetOwner() const { return mOwner; }

    protected:
        Shooter(Actor* owner);

    private:
        virtual void ShootImpl() = 0; // pure virtual function make this class abstract
        Actor* mOwner;
    };
}