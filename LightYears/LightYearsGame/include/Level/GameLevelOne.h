#pragma once
#include"framework/World.h"
#include"framework/TimerManager.h"

namespace ly
{
    class PlayerSpaceship;
    class GameplayHUD;
    class GameLevelOne : public World
    {
        public:
            GameLevelOne(Application* owningApp);
        private:
            virtual void BeginPlay()override;
            void PlayerSpaceShipDestroyed(Actor* destroyedPlayerSpaceship);
            weak<PlayerSpaceship> mPlayerSpaceship;
            weak<GameplayHUD> mGameplayHUD;
            TimerHandle timerHandle_test;

            virtual void InitGameStages() override;

            void QuitGame();
            void RestartGame();
            void GameOver();
            virtual void AllGameStageFinished() override;
    };
}