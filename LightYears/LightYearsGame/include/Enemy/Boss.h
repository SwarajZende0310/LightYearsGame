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
            virtual void BeginPlay()override;
        private:
            float mSpeed;
            float mBaseSpeed;
            float mSwitchDistanceToEdge;

            void CheckMove();

            BulletShooter mBaseShooterLeft;
            BulletShooter mBaseShooterRight;

            ThreeWayShooter mThreeWayShooter;
            FrontalWiper mFrontalWiperLeft;
            FrontalWiper mFrontalWiperRight;

            BulletShooter mFinalStageShooterLeft;
            BulletShooter mFinalStageShooterRight;

            void ShootBaseShooters();
            void ShootThreewayShooter();
            void ShootFrontalShooter();

            void HealthChanged(float amt, float currHealth, float maxHealth);

            void SetStage(int newStage);
            int mStage;
    };
}