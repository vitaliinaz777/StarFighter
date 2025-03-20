#include "spaceship/Spaceship.h"

namespace st
{
    Spaceship::Spaceship(World* owningWorld, const std::string& texturePath)
        : Actor{ owningWorld, texturePath },
        mVelocity{ 0.0f, 0.0f },
        mHealthComp{ 100.f, 100.f}
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
        This function that accepts(bind) a callback.
        Basicly any function is a pointer to some piece of code in 'code segment' in memory.
        &Spaceship::OnHealthChanged - is an address of function OnHealthChanged() 
                                      in a memory.
        We passing this address as an second argument to function BindAction(),
        [ void(ClassName::*callback)(Args...) ]  <--- [ &Spaceship::OnHealthChanged ]
        */
        mHealthComp.onHealthChangedDelegate.BindAction(GetWeakRef(), &Spaceship::OnHealthChanged);
    }

    // Callback function
    void Spaceship::OnHealthChanged(float amount, float health, float maxHealth)
    {
    }
}