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
            BulletShooter(Actor*owner,
                float cooldownTime=1.f,
                sf::Vector2f localPositionOffset = {0.f,0.f},
                float localRotationOffset = 0.f,
                const std::string& bulletTexturePath = "SpaceShooterRedux/PNG/Lasers/laserBlue01.png"
                );

            virtual bool isOnCooldown()const override;

            virtual void IncrementLevel(int amt)override;
             
            void SetBulletTexturePath(const std::string& newBulletTexturePath);
        private:
            virtual void ShootImpl()override;
            sf::Clock mCooldownClock;
            float mCooldownTime;

            sf::Vector2f mLocalPositionOffset;
            float mLocalRotationOffset;

            std::string mBulletTexturePath;
    };
}