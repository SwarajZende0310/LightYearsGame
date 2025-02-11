#pragma once
#include<SFML/Graphics.hpp>
#include"framework/Core.h"
#include "framework/World.h"
#include"framework/AssetManager.h"
#include"framework/PhysicsSystem.h"
#include"framework/TimerManager.h"

namespace ly
{
    class Application
    {
        public:
            Application(unsigned int windowWidth, unsigned int windowHeight, const std::string & title,sf::Uint32 style);
            void Run();

            template<typename worldType>
            weak<worldType> LoadWorld();

            sf::Vector2u GetWindowSize()const;

            sf::RenderWindow& GetWindow() { return mWindow; }
            const sf::RenderWindow& GetWindow() const { return mWindow; }

            void QuitApplication();
            void PlayPauseGame();
            bool IsGamePaused(){return mPlayPauseGame;}
        private:
            bool DispathEvent(const sf::Event& event);
            void TickInternal(float deltaTime);
            void RenderInternal();

            virtual void Render();
            virtual void Tick(float deltaTIme);

            sf::RenderWindow mWindow;
            float mTargetFrameRate;
            sf::Clock mTickClock;

            shared<World> mCurrentWorld;
            shared<World> mPendingWorld;
            sf::Clock mCleanCycleClock;
            float mCleanCycleInerval;

            bool mPlayPauseGame;
    };

    template<typename worldType>
    weak<worldType> Application :: LoadWorld()
    {
        shared<worldType> newWorld{new worldType{this}};
        mPendingWorld = newWorld;
        return newWorld;
    }
}