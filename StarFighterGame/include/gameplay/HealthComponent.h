#pragma once
#include "framework/Delegate.h"

namespace st
{
    class HealthComponent
    {
    public:
        HealthComponent(float health, float maxHealth);
        void ChangeHealth( float amount);
        float GetHealth() const { return mHealth; }
        float GetMaxHealth() const { return mMaxHealth; }

        Delegate<float, float, float> onHealthChangedDelegate;
        Delegate<float, float, float> onTakenDamageDelegate;
        Delegate<> onHealthEmptyDelegate;

    private:
        void TakenDamage(float amount);
        void HealthEmpty();
        
        float mHealth;        
        float mMaxHealth;
    };
}