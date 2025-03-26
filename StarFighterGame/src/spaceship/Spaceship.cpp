#include "spaceship/Spaceship.h"
#include "framework/MathUtility.h"
#include "VFX/Explosion.h"

namespace st
{
    Spaceship::Spaceship(World* owningWorld, const std::string& texturePath)
        : Actor{ owningWorld, texturePath },
        mVelocity{ 0.0f, 0.0f },
        mHealthComp{ 100.f, 100.f },
        mBlinkTime{ 0.f },
        mBlinkDuration{0.2f},
        mBlinkColorOffset{255, 0, 0, 255}
    {
    }

    void Spaceship::Tick(float deltaTime)
    {
        Actor::Tick(deltaTime);

        AddActorLocationOffset(GetVelocity() * deltaTime); // Move the spaceship
        UpdateBlink(deltaTime);
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

    void Spaceship::Blink()
    {
        if (mBlinkTime == 0.f) {
            mBlinkTime = mBlinkDuration;
        }
    }

    void Spaceship::UpdateBlink(float deltaTime)
    {
        if (mBlinkTime > 0) {
            mBlinkTime -= deltaTime;
            mBlinkTime = mBlinkTime > 0 ? mBlinkTime : 0.f; // make mBlinkTime always be more than 0

            GetSprite().setColor(LerpColor(sf::Color::White, mBlinkColorOffset, mBlinkTime));
        }
    }

    // Callback function
    void Spaceship::OnHealthChanged(float amount, float health, float maxHealth)
    {
        //LOG("health changed by: %f, and is now: %f/%f", amount, health, maxHealth);
    }

    // Callback function
    void Spaceship::OnTakenDamage(float amount, float health, float maxHealth)
    {
        Blink();
    }

    // Callback function
    void Spaceship::Blow()
    {
        Explosion* exp = new Explosion();
        exp->SpawnExplosion(GetWorld(), GetActorLocation());
        Destroy();
        delete exp;
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