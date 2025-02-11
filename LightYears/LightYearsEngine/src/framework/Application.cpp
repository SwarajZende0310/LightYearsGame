#include "framework/Application.h"

namespace ly
{
    Application::Application(unsigned int windowWidth, unsigned int windowHeight, const std::string & title,sf::Uint32 style)
        :mWindow(sf::VideoMode({windowWidth, windowHeight}), title, style),
        mTargetFrameRate(60.f),
        mTickClock(),
        mCurrentWorld(nullptr),
        mCleanCycleClock{},
        mCleanCycleInerval{2.f},
        mPlayPauseGame{false}
    {
        
    }

    void Application::Run()
    {
        mTickClock.restart();
        float accumalatedTime = 0.f;
        float targetDeltaTime = 1.f / mTargetFrameRate;

        while(mWindow.isOpen())
        {
            sf::Event windowEvent;
            while(mWindow.pollEvent(windowEvent))
            {
                if(windowEvent.type == sf::Event::EventType::Closed)
                {
                    QuitApplication();
                }
                else
                {
                    DispathEvent(windowEvent);
                }
            }

            // accumalatedTime += mTickClock.restart().asSeconds();//Calculating the time elapsed before rendering
            float frameDeltaTime = mTickClock.restart().asSeconds();
            accumalatedTime += frameDeltaTime;
            
            while(accumalatedTime > targetDeltaTime)//Rendering only to achieve det frame rate
            {
                accumalatedTime -= targetDeltaTime;
                TickInternal(targetDeltaTime);
                RenderInternal();
            }
        }
    }

    sf::Vector2u Application::GetWindowSize() const
    {
        return mWindow.getSize();
    }

    void Application::QuitApplication()
    {
        mWindow.close();
    }

    void Application::PlayPauseGame()
    {
        mPlayPauseGame = !mPlayPauseGame;
    }

    bool Application::DispathEvent(const sf::Event &event)
    {
        if(mCurrentWorld)
        {
            return mCurrentWorld->DispathEvent(event);
        }
        return false;
    }

    void Application::TickInternal(float deltaTime) 
    {
        if(mPlayPauseGame)return;

        Tick(deltaTime);

        if(mCurrentWorld)
        {
            mCurrentWorld->TickInternal(deltaTime);
        }

        TimerManager::Get().UpdateTimer(deltaTime);
        
        //Tick the Physics Engine
        PhysicsSystem::Get().Step(deltaTime);

        // Clean Textures if not acquired by anyone
        if(mCleanCycleClock.getElapsedTime().asSeconds() >= mCleanCycleInerval)
        {
            mCleanCycleClock.restart();
            AssetManager::Get().CleanCycle();
        }

        if(mPendingWorld && mPendingWorld != mCurrentWorld)
        {
            mCurrentWorld = mPendingWorld;
            
            PhysicsSystem::Get().Cleanup();
            mCurrentWorld->BeginPlayInternal();
        }
    }

    void Application::RenderInternal()
    {
        mWindow.clear();

        Render();

        mWindow.display();
    }

    void Application :: Render()
    {
        if(mCurrentWorld)
        {
            mCurrentWorld->Render(mWindow);
        }   
    }

    void Application::Tick(float deltaTime)
    {
        // LOG("ticking at framerate: %f \n",1.f/deltaTime);
    }
}
