#include"framework/World.h"
#include"framework/Actor.h"
#include"framework/Core.h"

namespace ly
{
    Actor::Actor(World* owningWorld):
    mHasBeganPlay(false)
    {

    }

    Actor::~Actor()
    {

    }

    void Actor::BeginPlayInternal()
    {
        if(!mHasBeganPlay)
        {
            mHasBeganPlay = true;
            BeginPlay();
        }
    }

    void Actor::BeginPlay()
    {
        LOG("Actor Began Play");
    }

    void Actor::Tick(float deltaTime)
    {
        LOG("Actor Ticking");
    }
}