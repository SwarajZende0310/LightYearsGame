#include"framework/World.h"
#include"framework/Application.h"
#include "gameplay/GameStage.h"
#include"widgets/HUD.h"

namespace ly
{
    World:: World(Application* owningApp)
    :mOwningApp(owningApp),
    mBeganPlay(false),
    mActors{},
    mPendingActors{},
    mCleanCycleClock{},
    mCleanCycleInerval{2.f},
    mGameStages{},
    mCurrentStage{mGameStages.end()}
    {

    }

    void World::BeginPlayInternal()
    {
        if(!mBeganPlay)
        {
            mBeganPlay = true;
            BeginPlay();
            InitGameStages();
            StartStages();
        }
    }

    void World::TickInternal(float deltaTime)
    {
        for(shared<Actor> actor : mPendingActors)
        {
            mActors.push_back(actor);
            actor->BeginPlayInternal();
        }
        mPendingActors.clear();

        for(auto iter = mActors.begin(); iter != mActors.end();)
        {
            iter->get()->TickInternal(deltaTime);
            ++iter;
        }

        if(mCleanCycleClock.getElapsedTime().asSeconds() >= mCleanCycleInerval)
        {
            mCleanCycleClock.restart();
            CleanCycle();
        }

        if(mCurrentStage != mGameStages.end())
        {
            mCurrentStage->get()->TickStage(deltaTime);
        }

        Tick(deltaTime); 

        if(mHUD)
        {
            if( !mHUD->HasInit() )
                mHUD->NativeInit(mOwningApp->GetWindow());
            mHUD->Tick(deltaTime);
        }
    }

    void World::Render(sf::RenderWindow &window)
    {
        for(auto& actor : mActors)
        {
            actor->Render(window);
        }

        RenderHUD(window);
    }

    World::~World()
    {

    }

    sf::Vector2u World::GetWindowSize() const
    {
        return mOwningApp->GetWindowSize();
    }

    void World::CleanCycle()
    {
        for(auto iter = mActors.begin(); iter != mActors.end();)
        {
            if(iter->get()->IsPendingDestroy())
            {
                iter = mActors.erase(iter);
            }
            else
            {
                ++iter;
            }
        }
    }

    void World::AddStage(const shared<GameStage> &newStage)
    {
        mGameStages.push_back(newStage);
    }

    bool World::DispathEvent(const sf::Event event)
    {
        if(mHUD)
        {
            return mHUD->HandleEvent(event);
        }
        return false;
    }

    void World::BeginPlay()
    {
        // LOG("Began Play");
    }

    void World::Tick(float deltaTime)
    {
        // LOG("ticking at framerate: %f \n",1.f/deltaTime);
    }

    void World::RenderHUD(sf::RenderWindow &window)
    {
        if(mHUD)
        {
            mHUD->Draw(window);
        }
    }

    void World::InitGameStages()
    {

    }

    void World::AllGameStageFinished()
    {
        LOG("All Stage Finished");
    }

    void World::NextGameStage()
    {
        mCurrentStage = mGameStages.erase(mCurrentStage);
        if(mCurrentStage != mGameStages.end())
        {
            mCurrentStage->get()->StartStage();
            mCurrentStage->get()->onStageFinished.BindAction(GetWeakRef(), &World::NextGameStage);
        }
        else
        {
            AllGameStageFinished();
        }
    }

    void World::StartStages()
    {
        mCurrentStage = mGameStages.begin();
        if(mCurrentStage != mGameStages.end())
        {
            mCurrentStage->get()->StartStage();
            mCurrentStage->get()->onStageFinished.BindAction(GetWeakRef(), &World::NextGameStage);
        }
    }
}