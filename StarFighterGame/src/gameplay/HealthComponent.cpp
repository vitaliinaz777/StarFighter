#include "gameplay/HealthComponent.h"
#include "framework/Core.h"

namespace st
{
    HealthComponent::HealthComponent(float health, float maxHealth)
        : mHealth{health},
        mMaxHealth{maxHealth}
    { }

    void HealthComponent::ChangeHealth(float amount) {
        if (amount == 0) { return; } // no damdage or regen
        if (mHealth == 0) { return; } // probably dead

        mHealth += amount;
        
        if (mHealth < 0) {
            mHealth = 0;
        }

        if (mHealth > mMaxHealth) {
            mHealth = mMaxHealth;
        }

        if (amount < 0) {
            TakenDamage(-amount);
            if (mHealth <= 0) { // probably dead
                HealthEmpty();
            }
        } 

        onHealthChangedDelegate.Broadcast(amount, mHealth, mMaxHealth);
    }
    
    void HealthComponent::TakenDamage(float amount)
    {
        //LOG("Took damage: %f, now health is: %f,%f", amount, mHealth, mMaxHealth);
        onTakenDamageDelegate.Broadcast(amount, mHealth, mMaxHealth);
    }
    
    void HealthComponent::HealthEmpty()
    {
        //LOG("Dead");
        onHealthEmptyDelegate.Broadcast();
    }
}