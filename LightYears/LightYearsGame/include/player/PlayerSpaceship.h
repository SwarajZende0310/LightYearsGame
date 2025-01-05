#pragma once
#include"spaceship/Spaceship.h"
#include<SFML/System.hpp>
#include"framework/MathUtility.h"

namespace ly
{
    class PlayerSpaceship : public Spaceship
    {
    public:
        PlayerSpaceship(World* owningWorld, const std::string& path="SpaceShooterRedux/PNG/playerShip1_blue.png");

        virtual void Tick(float deltaTime)override;
        void SetSpeed(float newSpeed){mSpeed = newSpeed;}
        float GetSpeed(){return mSpeed;}
    private:
        void HandleInput();
        void NormalizeInput();
        void ConsumeInput(float deltaTime);
        sf::Vector2f mMoveInput;
        float mSpeed;
    };
    
}