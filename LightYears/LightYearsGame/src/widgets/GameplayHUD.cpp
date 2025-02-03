#include "widgets/GameplayHUD.h"

namespace ly
{
    GameplayHUD::GameplayHUD()
        :mFrameRateText{"Frame Rate:"},
        mPlayerHealthBar{}
    {
        mFrameRateText.SetTextSize(30);
    }

    void GameplayHUD::Draw(sf::RenderWindow &windowRef)
    {
        mFrameRateText.NativeDraw(windowRef);
        mPlayerHealthBar.NativeDraw(windowRef);
    }

    void GameplayHUD::Tick(float deltaTime)
    {
        int frameRate = int(1.0 / deltaTime) ;
        std::string frameRateStr = "Frame Rate: " + std::to_string(frameRate);
        mFrameRateText.SetString(frameRateStr);
    }

    void GameplayHUD::Init(const sf::RenderWindow &windowRef)
    {
        auto windowSize = windowRef.getSize();
        mPlayerHealthBar.SetWidgetLocation(sf::Vector2f{20.f, windowSize.y - 50.f});
        mPlayerHealthBar.UpdateValue(100.f, 200.f);
    }
}