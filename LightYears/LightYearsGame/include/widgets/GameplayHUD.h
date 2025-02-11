#pragma once

#include"widgets/HUD.h"
#include"widgets/TextWidget.h"
#include"widgets/ValueGuage.h"
#include"widgets/ImageWidget.h"
#include"widgets/Button.h"

namespace ly
{
    class Actor;
    class GameplayHUD : public HUD
    {
        public:
            GameplayHUD();

            virtual void Draw(sf::RenderWindow& windowRef)override;
            virtual void Tick(float deltaTime)override;
            virtual bool HandleEvent(const sf::Event& event)override;
            void UpdatePauseButton(bool paused);
            
            void GameFinsihed(bool playerWon);
            Delegate<> OnRestartButtonClicked;
            Delegate<> OnQuitButtonClicked;
            Delegate<> OnPauseButtonClicked;
        private:
            virtual void Init(const sf::RenderWindow& windowRef)override;
            void PlayerHealthUpdated(float amt, float currentHealth, float maxHealth);
            void RefreshHealthBar();
            void ConnectPlayerStatus();
            void PlayerLifeCountUpdated(int amt);
            void PlayerScoreUpdated(int newScore);
            void PlayerSpaceshipDestroyed(Actor* actor);
            void RestartButtonClicked();
            void QuitButtonClicked();
            void PauseButtonClicked();
            TextWidget mFrameRateText;
            ValueGuage mPlayerHealthBar;
            ImageWidget mPlayerIcon;
            TextWidget mPlayerLifeText;

            ImageWidget mPlayerScoreIcon;
            TextWidget mPlayerScoreText;

            sf::Color mHealthyHealthBarColor;
            sf::Color mCriticalHealthBarColor;
            float mCriticalThreshold;

            float mWidgetSpacing;

            TextWidget mWinLoseText;
            TextWidget mFinalScoreText;
            Button mRestartButton;
            Button mQuitButton;

            sf::Vector2u mWindowSize;

            Button mPauseButton;
            ButtonColor mPauseButtonColor;
            ButtonColor mResumeButtonColor;
    };
}