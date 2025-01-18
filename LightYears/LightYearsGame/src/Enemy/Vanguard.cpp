#include"Enemy/Vanguard.h"

namespace ly
{       
    Vanguard::Vanguard(World *owningWorld, const std::string &texturePath, const sf::Vector2f &velocity)
        :EnemySpaceship(owningWorld,texturePath),
        mShooter{ new BulletShooter{this,0.3f}}
    {
        SetVelocity(velocity);
        SetActorRotation(90.f);
    }

    void Vanguard::Tick(float deltaTime)
    {
        EnemySpaceship::Tick(deltaTime);
        Shoot();
    }

    void Vanguard::Shoot()
    {
        mShooter->Shoot();
    }
}