#pragma once
#include<SFML/System.hpp>
#include"weapon/Shooter.h"
#include"framework/Core.h"
#include"weapon/Bullet.h"
#include"framework/World.h"

namespace ly
{
    class BulletShooter : public Shooter
    {
        public:
            BulletShooter(Actor*owner,float cooldownTime=1.f);
            virtual bool isOnCooldown()const override;
        private:
            virtual void ShootImpl()override;
            sf::Clock mCooldownClock;
            float mCooldownTime;
    };
}