#include "framework/Application.h"

namespace ly
{
    Application::Application(unsigned int windowWidth, unsigned int windowHeight, const std::string & title,sf::Uint32 style)
        :mWindow(sf::VideoMode({windowWidth, windowHeight}), title, style),
        mTargetFrameRate(60.f),
        mTickClock(),
        currentWorld(nullptr),
        mCleanCycleClock{},
        mCleanCycleInerval{2.f}
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
                    mWindow.close();
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
    
    void Application::TickInternal(float deltaTime)
    {
        Tick(deltaTime);

        if(currentWorld)
        {
            currentWorld->TickInternal(deltaTime);
        }

        // Clean Textures if not acquired by anyone
        if(mCleanCycleClock.getElapsedTime().asSeconds() >= mCleanCycleInerval)
        {
            mCleanCycleClock.restart();
            AssetManager::Get().CleanCycle();
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
        if(currentWorld)
        {
            currentWorld->Render(mWindow);
        }   
    }

    void Application::Tick(float deltaTime)
    {
        // LOG("ticking at framerate: %f \n",1.f/deltaTime);
    }
}
