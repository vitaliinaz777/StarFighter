#pragma once

namespace st
{
    class HealthComponent
    {
    public:
        HealthComponent(float health, float maxHealth);
        void ChangeHealth( float amount);
        float GetHealth() const { return mHealth; }
        float GetMaxHealth() const { return mMaxHealth; }

    private:
        void TakenDamage(float amount);
        void HealthEmpty();
        void HealthRegen(float amount);
        float mHealth;
        float mMaxHealth;
    };
}