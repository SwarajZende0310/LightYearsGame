#include"player/PlayerSpaceship.h"

namespace ly
{
    PlayerSpaceship::PlayerSpaceship(World* owningWorld, const std::string& path)
        :Spaceship(owningWorld,path),
        mMoveInput{},
        mSpeed{200.f},
        mShooter{new BulletShooter{this, 0.1f}}
    {
        SetTeamID(1);
    }

    void PlayerSpaceship::Tick(float deltaTime)
    {
        Spaceship::Tick(deltaTime);
        HandleInput();
        ConsumeInput(deltaTime);
    }

    void PlayerSpaceship::Shoot()
    {
        if(mShooter)
        {
            mShooter->Shoot();
        }
    }

    void PlayerSpaceship::HandleInput()
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            mMoveInput.y = -1.f;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            mMoveInput.y = 1.f;
        }
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            mMoveInput.x = -1.f;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            mMoveInput.x = 1.f;
        }

        ClampInputOnEdge();

        NormalizeInput();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            Shoot();
        }
    }

    void PlayerSpaceship::NormalizeInput()
    {
        Normalize(mMoveInput);
        // LOG("move input is now: %f , %f",mMoveInput.x,mMoveInput.y);
    }

    void PlayerSpaceship::ClampInputOnEdge()
    {
        sf::Vector2f actorLocation = GetActorLocation();
        
        if((actorLocation.x < 0 && mMoveInput.x == -1) || (actorLocation.x > GetWindowSize().x && mMoveInput.x == 1.f))
        {
            mMoveInput.x = 0.f;
        }

        if((actorLocation.y < 0 && mMoveInput.y == -1)||(actorLocation.y > GetWindowSize().y && mMoveInput.y == 1.f))
        {
            mMoveInput.y = 0.f;
        }
    }

    void PlayerSpaceship::ConsumeInput(float deltaTime)
    {
        SetVelocity(mMoveInput * mSpeed);
        mMoveInput.x = mMoveInput.y = 0.f;
    }
}