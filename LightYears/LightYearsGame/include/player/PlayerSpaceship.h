#pragma once
#include"spaceship/Spaceship.h"
#include<SFML/System.hpp>
#include"framework/MathUtility.h"
#include"weapon/BulletShooter.h"
#include"weapon/ThreeWayShooter.h"
#include"weapon/FrontalWiper.h"

namespace ly
{
    class Shooter;
    class PlayerSpaceship : public Spaceship
    {
    public:
        PlayerSpaceship(World* owningWorld, const std::string& path="SpaceShooterRedux/PNG/playerShip1_blue.png");

        virtual void Tick(float deltaTime)override;
        void SetSpeed(float newSpeed){mSpeed = newSpeed;}
        float GetSpeed(){return mSpeed;}
        virtual void Shoot()override;

        void SetShooter(unique<Shooter>&& newShooter);

    private:
        void HandleInput();
        void NormalizeInput();
        void ClampInputOnEdge();
        void ConsumeInput(float deltaTime);
        sf::Vector2f mMoveInput;
        float mSpeed;

        unique<Shooter> mShooter;
    };
    
}