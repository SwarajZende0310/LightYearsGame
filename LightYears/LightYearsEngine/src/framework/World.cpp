#include"framework/World.h"
#include "framework/Core.h"

namespace ly
{
    World:: World(Application* owningApp)
    :mOwningApp(owningApp),
    mBeganPlay(false)
    {

    }

    void World::BeginPlayInternal()
    {
        if(!mBeganPlay)
        {
            mBeganPlay = true;
            BeginPlay();
        }
    }

    void World::TickInternal(float deltaTime)
    {
        Tick(deltaTime);
    }

    World::~World()
    {

    }

    void World::BeginPlay()
    {
        LOG("Began Play");
    }

    void World::Tick(float deltaTime)
    {
        LOG("ticking at framerate: %f \n",1.f/deltaTime);
    }

}