#include "widgets/GameplayHUD.h"
#include"player/PlayerManager.h"
#include"player/PlayerSpaceship.h"
#include"framework/Actor.h"

namespace ly
{
    GameplayHUD::GameplayHUD()
        :mFrameRateText{"Frame Rate:"},
        mPlayerHealthBar{},
        mPlayerIcon{"SpaceShooterRedux/PNG/pickups/playerLife1_blue.png"},
        mPlayerLifeText{""},
        mHealthyHealthBarColor{128,255,128,255},
        mCriticalHealthBarColor{255,0,0,255},
        mCriticalThreshold{0.3f},
        mWidgetSpacing{10.f}
    {
        mFrameRateText.SetTextSize(30);
        mPlayerLifeText.SetTextSize(20);
    }

    void GameplayHUD::Draw(sf::RenderWindow &windowRef)
    {
        mFrameRateText.NativeDraw(windowRef);
        mPlayerHealthBar.NativeDraw(windowRef);
        mPlayerIcon.NativeDraw(windowRef);
        mPlayerLifeText.NativeDraw(windowRef);
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

        sf::Vector2f nextWidgetPos = mPlayerHealthBar.GetWidgetLocation();
        nextWidgetPos += sf::Vector2f{ mPlayerHealthBar.GetBound().width + mWidgetSpacing, 0.f};
        mPlayerIcon.SetWidgetLocation(nextWidgetPos);

        nextWidgetPos += sf::Vector2f{mPlayerIcon.GetBound().width + mWidgetSpacing, 0.f};
        mPlayerLifeText.SetWidgetLocation(nextWidgetPos);

        RefreshHealthBar();
        ConnectPlayerLifeCount();
    }

    void GameplayHUD::PlayerHealthUpdated(float amt, float currentHealth, float maxHealth)
    {
        mPlayerHealthBar.UpdateValue(currentHealth, maxHealth);
        if( currentHealth / maxHealth < mCriticalThreshold)
        {
            mPlayerHealthBar.SetForegroundColor(mCriticalHealthBarColor);
        }
        else
        {
            mPlayerHealthBar.SetForegroundColor(mHealthyHealthBarColor);
        }
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
            PlayerHealthUpdated(0, healthComp.GetHealth(), healthComp.GetMaxHealth());
        }
    }

    void GameplayHUD::ConnectPlayerLifeCount()
    {
        Player* player = PlayerManager::Get().GetPlayer();
        if(player)
        {
            int lifeCount = player->GetLifeCount();
            mPlayerLifeText.SetString(std::to_string(lifeCount));
            player->onLifeChange.BindAction(GetWeakRef(), &GameplayHUD::PlayerLifeCountUpdated);
        }
    }
    void GameplayHUD::PlayerLifeCountUpdated(int amt)
    {
        mPlayerLifeText.SetString(std::to_string(amt));
    }

    void GameplayHUD::PlayerSpaceshipDestroyed(Actor *actor)
    {
        RefreshHealthBar();
    }
}