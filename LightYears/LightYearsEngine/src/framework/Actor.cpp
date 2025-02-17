#include"framework/Actor.h"

namespace ly
{
    Actor::Actor(World* owningWorld, const std::string& texturePath):
        mOwningWorld{owningWorld},
        mHasBeganPlay(false),
        mSprite(),
        mTexture(),
        mPhysicsBody{nullptr},
        mPhysicsEnabled{false},
        mTeamID{GetNeutralTeamID()}
    {
        SetTexture(texturePath);
    }

    Actor::~Actor()
    {
        // LOG("Actor Destroyed");
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
        UpdatePhysicsBodyTransform();
    }

    void Actor::SetActorRotation(const float newRot)
    {
        mSprite.setRotation(newRot);
        UpdatePhysicsBodyTransform();
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

    sf::FloatRect Actor::GetActorGlobalBounds() const
    {
        return mSprite.getGlobalBounds();
    }

    sf::Vector2u Actor::GetWindowSize() const
    {
        return mOwningWorld->GetWindowSize();
    }

    bool Actor::isActorOutOfWindowBounds(float allowance) const
    {
        float windowWidth = mOwningWorld->GetWindowSize().x;
        float windowHeight = mOwningWorld->GetWindowSize().y;

        float width = GetActorGlobalBounds().width + allowance;
        float height = GetActorGlobalBounds().height + allowance;

        sf::Vector2f actorPos = GetActorLocation();

        if(actorPos.x < -width || actorPos.x > windowWidth + width || actorPos.y < -height || actorPos.y > windowHeight + height)
        {
            return true;
        }

        return false;
    }

    void Actor::SetEnablePhysics(bool enable)
    {
        mPhysicsEnabled = enable;
        if(mPhysicsEnabled){
            IntializePhysics();
        }else{
            UninitializePhysics();
        }
    }
    void Actor::OnActorBeginOverlap(Actor *other)
    {
        
    }
    void Actor::OnActorEndOverlap(Actor *other)
    {

    }

    void Actor::Destroy()
    {
        UninitializePhysics();
        onActorDestroyed.Broadcast(this);
        Object::Destroy();
    }

    bool Actor::IsOtherHostile(Actor *other) const
    {
        if(!other)return false;
        if(GetTeamID() == GetNeutralTeamID() || other->GetTeamID() == GetNeutralTeamID())
        {
            return false;
        }

        return GetTeamID() != other->GetTeamID();
    }

    void Actor::ApplyDamage(float amt)
    {

    }

    void Actor::SetTextureRepeated(bool repeated)
    {
        mTexture->setRepeated(repeated);
    }

    void Actor::IntializePhysics()
    {
        if(!mPhysicsBody)
        {
            mPhysicsBody = PhysicsSystem::Get().AddListener(this);
        }
    }
    void Actor::UninitializePhysics()
    {
        if(mPhysicsBody)
        {
            PhysicsSystem::Get().RemoveListener(mPhysicsBody);
            mPhysicsBody->GetUserData().pointer = reinterpret_cast<uintptr_t>(nullptr);
            mPhysicsBody = nullptr;
        }
    }
    void Actor::UpdatePhysicsBodyTransform()
    {
        if(mPhysicsBody)
        {
            float physicsScale = PhysicsSystem::Get().GetPhysicsScale();
            b2Vec2 pos{GetActorLocation().x * physicsScale, GetActorLocation().y * physicsScale};
            float rotation = DegreesToRadians(GetActorRotation());

            mPhysicsBody->SetTransform(pos,rotation);
        }
    }
    void Actor::CenterPivot()
    {
        sf::FloatRect bound= mSprite.getGlobalBounds();
        mSprite.setOrigin(bound.width/2.f, bound.height/2.f);
    }
}