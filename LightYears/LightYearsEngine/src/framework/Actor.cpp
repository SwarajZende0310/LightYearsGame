#include"framework/Actor.h"

namespace ly
{
    Actor::Actor(World* owningWorld, const std::string& texturePath):
        mOwningWorld{owningWorld},
        mHasBeganPlay(false),
        mSprite(),
        mTexture()
    {
        SetTexture(texturePath);
    }

    Actor::~Actor()
    {
        LOG("Actor Destroyed");
    }

    void Actor::BeginPlayInternal()
    {
        if(!mHasBeganPlay)
        {
            mHasBeganPlay = true;
            BeginPlay();
        }
    }

    void Actor::TickInternal(float deltaTime)
    {
        if(!IsPendingDestroy())
        {
            Tick(deltaTime);
        }
    }
    void Actor::BeginPlay()
    {
        // LOG("Actor Began Play");
    }

    void Actor::Tick(float deltaTime)
    {
        // LOG("Actor Ticking");
    }

    void Actor::SetTexture(const std::string &texturePath)
    {
        mTexture = AssetManager::Get().LoadTexture(texturePath); 
        
        if(!mTexture)return;//Texture not loaded
        
        mSprite.setTexture(*mTexture);
        
        int textureWidth = mTexture->getSize().x;
        int textureHeight = mTexture->getSize().y;
        mSprite.setTextureRect(sf::IntRect{sf::Vector2i{},sf::Vector2i{textureWidth,textureHeight}});
        CenterPivot();
    }
    void Actor::Render(sf::RenderWindow &window)
    {
        if(IsPendingDestroy())
            return;

        window.draw(mSprite); 
    }

    void Actor::SetActorLocation(const sf::Vector2f &newLoc)
    {
        mSprite.setPosition(newLoc);
    }

    void Actor::SetActorRotation(const float newRot)
    {
        mSprite.setRotation(newRot);
    }
    
    void Actor::AddActorLocationOffset(const sf::Vector2f &offsetAmt)
    {
        SetActorLocation(GetActorLocation() + offsetAmt);
    }
    
    void Actor::AddActorRotationOffset(float offsetAmt)
    {
        SetActorRotation(GetActorRotation() + offsetAmt);
    }
    
    sf::Vector2f Actor::GetActorLocation() const
    {
        return mSprite.getPosition();
    }
    
    float Actor::GetActorRotation() const
    {
        return mSprite.getRotation();
    }
    sf::Vector2f Actor::GetActorForwardDirection() const
    {
        return RotationToVector(GetActorRotation());
    }
    sf::Vector2f Actor::GetActorRightDirection() const
    {
        return RotationToVector(GetActorRotation() + 90.f);
    }

    sf::Vector2u Actor::GetWindowSize() const
    {
        return mOwningWorld->GetWindowSize();
    }
    void Actor::CenterPivot()
    {
        sf::FloatRect bound= mSprite.getGlobalBounds();
        mSprite.setOrigin(bound.width/2.f, bound.height/2.f);
    }
}