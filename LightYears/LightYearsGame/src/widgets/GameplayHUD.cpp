#include "widgets/GameplayHUD.h"
#include"player/PlayerManager.h"
#include"player/PlayerSpaceship.h"
#include"framework/Actor.h"

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

        RefreshHealthBar();
    }

    void GameplayHUD::PlayerHealthUpdated(float amt, float currentHealth, float maxHealth)
    {
        mPlayerHealthBar.UpdateValue(currentHealth, maxHealth);
    }

    void GameplayHUD::RefreshHealthBar()
    {
        Player* player = PlayerManager::Get().GetPlayer();
        if(player && !player->GetCurrentSpaceship().expired())
        {
            weak<PlayerSpaceship> playerSpaceship = player->GetCurrentSpaceship();
            playerSpaceship.lock()->onActorDestroyed.BindAction(GetWeakRef(), &GameplayHUD::PlayerSpaceshipDestroyed);
            HealthComponent& healthComp = player->GetCurrentSpaceship().lock()->GetHealthComp(); 
            healthComp.onHealthChanged.BindAction(GetWeakRef(), &GameplayHUD::PlayerHealthUpdated);
            mPlayerHealthBar.UpdateValue(healthComp.GetHealth(), healthComp.GetMaxHealth());
        }
    }

    void GameplayHUD::PlayerSpaceshipDestroyed(Actor *actor)
    {
        RefreshHealthBar();
    }
}