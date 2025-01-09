#include"framework/PhysicsSystem.h"

namespace ly
{
    unique<PhysicsSystem> PhysicsSystem :: physicsSystem{nullptr};

    PhysicsSystem& PhysicsSystem::Get()
    {
        if(!physicsSystem)
        {
            physicsSystem = std::move(unique<PhysicsSystem>{new PhysicsSystem});
        }
        return *physicsSystem;
    }

    void PhysicsSystem::Step(float deltaTime)
    {
        ProcessPendingListeners();
        mPhysicsWorld.Step(deltaTime,mVelocityIterations,mPositionIterations);
    }

    b2Body* PhysicsSystem::AddListener(Actor *listener)
    {
        if(listener->IsPendingDestroy())return nullptr;

        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        
        bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(listener);

        bodyDef.position.Set(listener->GetActorLocation().x * GetPhysicsScale() ,listener->GetActorLocation().y * GetPhysicsScale());
        bodyDef.angle = DegreesToRadians(listener->GetActorRotation()); 

        b2Body* body = mPhysicsWorld.CreateBody(&bodyDef);
        
        b2PolygonShape shape;
        auto bound = listener->GetActorGlobalBounds();
        shape.SetAsBox(bound.width/2.f * GetPhysicsScale(), bound.height/2.f * GetPhysicsScale());

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = 1.f;
        fixtureDef.friction = 0.3f;
        fixtureDef.isSensor = true;

        body->CreateFixture(&fixtureDef);

        return body;
    }

    void PhysicsSystem::RemoveListener(b2Body *bodyToRemove)
    {
        mPendingRemoveListener.insert(bodyToRemove);
    }

    void PhysicsSystem::Cleanup()
    {
        physicsSystem = std::move(unique<PhysicsSystem>{new PhysicsSystem});
    }

    PhysicsSystem::PhysicsSystem()
        : mPhysicsWorld{b2Vec2{0.f, 0.f}},
          mPhysicsScale{0.01f},
          mVelocityIterations{8},
          mPositionIterations{3},
          mContactListener{},
          mPendingRemoveListener{}
    {
        mPhysicsWorld.SetContactListener(&mContactListener);
        mPhysicsWorld.SetAllowSleeping(false);
    }

    void PhysicsSystem::ProcessPendingListeners()
    {
        for(auto listener : mPendingRemoveListener)
        {
            mPhysicsWorld.DestroyBody(listener);
        }

        mPendingRemoveListener.clear();
    }
    void PhysicsConatctListener::BeginContact(b2Contact *contact)
    {
        Actor * ActorA = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
        Actor * ActorB = reinterpret_cast<Actor*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

        // Notify Actors
        if(ActorA && !ActorA->IsPendingDestroy())
        {
            ActorA->OnActorBeginOverlap(ActorB);
        }

        if(ActorB && !ActorB->IsPendingDestroy())
        {
            ActorB->OnActorBeginOverlap(ActorA);
        }
    }

    void PhysicsConatctListener::EndContact(b2Contact *contact)
    {
        Actor* ActorA = nullptr;
        Actor* ActorB = nullptr;

        // Check whether fixtures exist then move pointer 
        if(contact->GetFixtureA() && contact->GetFixtureA()->GetBody())
        {
            ActorA = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
        }

        if(contact->GetFixtureB() && contact->GetFixtureB()->GetBody())
        {
            ActorB = reinterpret_cast<Actor*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);
        }

        // Notify Actors
        if(ActorA && !ActorA->IsPendingDestroy())
        {
            ActorA->OnActorEndOverlap(ActorB);
        }

        if(ActorB && !ActorB->IsPendingDestroy())
        {
            ActorB->OnActorEndOverlap(ActorA);
        }
    }
}