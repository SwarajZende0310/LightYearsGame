#pragma once
#include"framework/World.h"
#include"framework/TimerManager.h"

namespace ly
{
    class PlayerSpaceship;
    class GameLevelOne : public World
    {
        public:
            GameLevelOne(Application* owningApp);
        private:
            virtual void BeginPlay()override;
            void PlayerSpaceShipDestroyed(Actor* destroyedPlayerSpaceship);
            weak<PlayerSpaceship> mPlayerSpaceship;
            TimerHandle timerHandle_test;

            virtual void InitGameStages() override;

            void GameOver();
    };
}