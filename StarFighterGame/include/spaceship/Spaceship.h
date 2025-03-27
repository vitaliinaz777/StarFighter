#pragma once
#include "framework/Actor.h"
#include "gameplay/HealthComponent.h"

namespace st 
{
    class Spaceship : public Actor {
    public:
        Spaceship(World* owningWorld, const std::string& texturePath = "");
        virtual void Tick(float deltaTime) override;
        void SetVelocity(const sf::Vector2f& newVel);
        sf::Vector2f GetVelocity() const { return mVelocity; }
        virtual void Shoot();
        virtual void BeginPlay() override;
        virtual void ApplyDamage(float amount) override;

    private:
        void Blink();
        void UpdateBlink(float deltaTime);

        virtual void OnHealthChanged(float amount, float health, float maxHealth);
        virtual void OnTakenDamage(float amount, float health, float maxHealth);
        virtual void Blow();

        void OnDestroy(Object* obj);

        sf::Vector2f mVelocity;

        HealthComponent mHealthComp;

        float mBlinkTime;
        float mBlinkDuration;
        sf::Color mBlinkColorOffset;
    };
}