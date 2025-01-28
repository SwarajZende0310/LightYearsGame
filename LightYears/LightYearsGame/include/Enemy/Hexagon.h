#pragma once

#include"Enemy/EnemySpaceship.h"

namespace ly
{
    class BulletShooter;
    class Hexagon : public EnemySpaceship
    {
        public:
            Hexagon(World* owningWorld, const std::string& texturePath = "SpaceShooterRedux/PNG/Enemies/enemyGreen4.png", const sf::Vector2f &velocity = sf::Vector2f{0.f, 100.f});

            virtual void Tick(float deltaTime);

        private:
            virtual void Shoot();

            unique<BulletShooter> mShooter1;
            unique<BulletShooter> mShooter2;
            unique<BulletShooter> mShooter3;
            unique<BulletShooter> mShooter4;
            unique<BulletShooter> mShooter5;
            unique<BulletShooter> mShooter6;
    };
}