#pragma once
#include<SFML/System.hpp>
#include"weapon/Shooter.h"
#include"framework/Core.h"

namespace ly
{
    class BulletShooter : public Shooter
    {
        public:
            BulletShooter(Actor*owner,float cooldownTime=0.3f);
            virtual bool isOnCooldown()const override;
        private:
            virtual void ShootImpl()override;
            sf::Clock mCooldownClock;
            float mCOoldownTime;
    };
}