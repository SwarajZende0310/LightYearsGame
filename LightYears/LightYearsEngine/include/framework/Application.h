#pragma once
#include<SFML/Graphics.hpp>
#include"framework/Core.h"
#include "framework/World.h"

namespace ly
{
    class Application
    {
        public:
            Application(unsigned int windowWidth, unsigned int windowHeight, const std::string & title,sf::Uint32 style);
            void Run();

            template<typename worldType>
            weak<worldType> LoadWorld();
        private:
            void TickInternal(float deltaTime);
            void RenderInternal();

            virtual void Render();
            virtual void Tick(float deltaTIme);

            sf::RenderWindow mWindow;
            float mTargetFrameRate;
            sf::Clock mTickClock;

            shared<World> currentWorld;
    };

    template<typename worldType>
    weak<worldType> Application :: LoadWorld()
    {
        shared<worldType> newWorld{new worldType{this}};
        currentWorld = newWorld;
        currentWorld->BeginPlayInternal();
        return newWorld;
    }
}