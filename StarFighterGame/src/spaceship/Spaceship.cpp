#include "spaceship/Spaceship.h"

namespace st
{
    Spaceship::Spaceship(World* owningWorld, const std::string& texturePath)
        : Actor{ owningWorld, texturePath },
        mVelocity{ 0.0f, 0.0f },
        mHealthComp{ 100.f, 100.f }
    {
    }

    void Spaceship::Tick(float deltaTime)
    {
        Actor::Tick(deltaTime);

        AddActorLocationOffset(GetVelocity() * deltaTime); // Move the spaceship
    }

    void Spaceship::SetVelocity(const sf::Vector2f& newVel)
    {
        mVelocity = newVel;
    }

    void Spaceship::Shoot()
    {
    }

    void Spaceship::BeginPlay()
    {
        Actor::BeginPlay();
        SetEnablePhysics(true);

        /*
        Function BindAction() accepts(bind) a callback.
        Basicly any function is a pointer to some piece of code in 'code segment' in memory.
        &Spaceship::OnHealthChanged - is an address of function OnHealthChanged()
                                      in a memory.
        We passing this address as an second argument to function BindAction(),
        [ void(ClassName::*callback)(Args...) ]  <---  [ &Spaceship::OnHealthChanged ]
        */
        mHealthComp.onHealthChangedDelegate.BindAction(GetWeakRef(), &Spaceship::OnHealthChanged);
        mHealthComp.onTakenDamageDelegate.BindAction(GetWeakRef(), &Spaceship::OnTakenDamage);
        mHealthComp.onHealthEmptyDelegate.BindAction(GetWeakRef(), &Spaceship::Blow);

        onDestroyDelegate.BindAction(GetWeakRef(), &Spaceship::OnDestroy);
    }

    // Callback function
    void Spaceship::OnHealthChanged(float amount, float health, float maxHealth)
    {
        //LOG("health changed by: %f, and is now: %f/%f", amount, health, maxHealth);
    }

    // Callback function
    void Spaceship::OnTakenDamage(float amount, float health, float maxHealth)
    {
    }

    // Callback function
    void Spaceship::Blow()
    {
        Destroy();
    }

    // Callback function
    void Spaceship::ApplyDamage(float amount)
    {
        mHealthComp.ChangeHealth(-amount); // negative amount
    }

    // Callback function
    void Spaceship::OnDestroy(Object* obj) {

        // Clean up or invalidate any delegates referencing this object
        //mHealthComp.onHealthChangedDelegate.Clear();
    }
}