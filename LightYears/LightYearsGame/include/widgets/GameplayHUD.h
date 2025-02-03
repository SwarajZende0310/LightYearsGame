#pragma once

#include"widgets/HUD.h"
#include"widgets/TextWidget.h"
#include"widgets/ValueGuage.h"
#include"widgets/ImageWidget.h"

namespace ly
{
    class Actor;
    class GameplayHUD : public HUD
    {
        public:
            GameplayHUD();

            virtual void Draw(sf::RenderWindow& windowRef)override;
            virtual void Tick(float deltaTime)override;
        private:
            virtual void Init(const sf::RenderWindow& windowRef)override;
            void PlayerHealthUpdated(float amt, float currentHealth, float maxHealth);
            void RefreshHealthBar();
            void PlayerSpaceshipDestroyed(Actor* actor);
            TextWidget mFrameRateText;
            ValueGuage mPlayerHealthBar;
            ImageWidget mPlayerIcon;

            sf::Color mHealthyHealthBarColor;
            sf::Color mCriticalHealthBarColor;
            float mCriticalThreshold;

            float mWidgetSpacing;
    };
}