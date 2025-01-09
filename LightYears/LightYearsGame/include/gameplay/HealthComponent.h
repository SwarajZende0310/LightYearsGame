#pragma once
#include"framework/Core.h"

namespace ly
{
    class HealthComponent
    {
    public:
        HealthComponent(float health, float maxHealth);
        void ChangeHealth(float amt);
        float GetHealth()const {return mHealth;}
        float GetMaxHealth()const{return mMaxHealth;}
    private:
        void HealthEmpty();
        void HealthRegen(float amt);
        void TakenDamage(float amt);
        float mHealth;
        float mMaxHealth;
    };  
}