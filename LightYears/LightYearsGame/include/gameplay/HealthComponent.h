#pragma once
#include"framework/Core.h"
#include"framework/Delegate.h"

namespace ly
{
    class HealthComponent
    {
    public:
        HealthComponent(float health, float maxHealth);
        void ChangeHealth(float amt);
        float GetHealth()const {return mHealth;}
        float GetMaxHealth()const{return mMaxHealth;}

        Delegate<float , float ,float> onHealthChanged;
    private:
        void HealthEmpty();
        void HealthRegen(float amt);
        void TakenDamage(float amt);
        float mHealth;
        float mMaxHealth;
    };  
}