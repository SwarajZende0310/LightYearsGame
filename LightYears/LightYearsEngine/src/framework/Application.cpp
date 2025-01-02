#include "framework/Application.h"
#include "framework/Core.h"

namespace ly
{
    Application::Application()
        :mWindow(sf::VideoMode({1024, 1440}), "Light Years"),
        mTargetFrameRate(60.f),
        mTickClock()
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
            LOG("ticking at framerate: %f \n",1.f/frameDeltaTime);
        }
    }

    void Application::TickInternal(float deltaTime)
    {
        Tick(deltaTime);
    }

    void Application::RenderInternal()
    {
        mWindow.clear();

        Render();

        mWindow.display();
    }

    void Application :: Render()
    {
        sf::RectangleShape rect{sf::Vector2f{100,100}};
        rect.setFillColor(sf::Color::Green);
        rect.setOrigin(50,50);
        rect.setPosition(mWindow.getSize().x/2.f,mWindow.getSize().y/2.f);

        mWindow.draw(rect);
    }

    void Application::Tick(float deltaTime)
    {
        // std::cout<<"ticking at framerate: "<< 1.f/deltaTime <<std::endl;
        LOG("ticking at framerate: %f \n",1.f/deltaTime);
    }
}
