#pragma once

#include"Enemy/EnemySpaceship.h"
#include"weapon/BulletShooter.h"
#include"weapon/ThreeWayShooter.h"
#include"weapon/FrontalWiper.h"

namespace ly
{
    class Boss : public EnemySpaceship
    {
        public:
            Boss(World* owningWorld);
            virtual void Tick(float deltaTime)override;
        private:
            float mSpeed;
            float mSwitchDistanceToEdge;

            void CheckMove();

            BulletShooter mBaseShooterLeft;
            BulletShooter mBaseShooterRight;

            void ShootBaseShooters();
    };
}