#include"Level/GameLevelOne.h"
#include"player/PlayerSpaceship.h"
#include"Enemy/Vanguard.h"
#include"Enemy/UFO.h"
#include"framework/TimerManager.h"
#include"gameplay/GameStage.h"
#include"gameplay/WaitStage.h"
#include"Enemy/VanguardStage.h"
#include"Enemy/TwinBladeStage.h"
#include"Enemy/HexagonStage.h"
#include"Enemy/UFOStage.h"
#include"Enemy/ChaosStage.h"
#include"Enemy/BossStage.h"
#include"player/PlayerManager.h"
#include"widgets/GameplayHUD.h"
#include"framework/Application.h"
#include"framework/BackdropActor.h"
#include"framework/BackgroundLayer.h"

namespace ly
{
    GameLevelOne::GameLevelOne(Application *owningApp)
        :World{owningApp}
    {
        
    }

    void GameLevelOne::BeginPlay()
    {
        SpawnCosmetics();

        Player& newPlayer = PlayerManager::Get().CreateNewPlayer();
        mPlayerSpaceship = newPlayer.SpawnSpaceship(this);
        mPlayerSpaceship.lock()->onActorDestroyed.BindAction(GetWeakRef(), &GameLevelOne::PlayerSpaceShipDestroyed);

        mGameplayHUD = SpawnHUD<GameplayHUD>();

        mGameplayHUD.lock()->OnQuitButtonClicked.BindAction(GetWeakRef(), &GameLevelOne::QuitGame);
        mGameplayHUD.lock()->OnRestartButtonClicked.BindAction(GetWeakRef(), &GameLevelOne::RestartGame);
    }

    void GameLevelOne::PlayerSpaceShipDestroyed(Actor *destroyedPlayerSpaceship)
    {
        mPlayerSpaceship = PlayerManager::Get().GetPlayer()->SpawnSpaceship(this);
        if(!mPlayerSpaceship.expired())
        {
            mPlayerSpaceship.lock()->onActorDestroyed.BindAction(GetWeakRef(), &GameLevelOne::PlayerSpaceShipDestroyed);
        }
        else
        {
            GameOver();
        }
    }

    void GameLevelOne::InitGameStages()
    {
        AddStage(shared<WaitStage>{new WaitStage{this,5.f}});
        AddStage(shared<VanguardStage>{new VanguardStage{this}});

        AddStage(shared<WaitStage>{new WaitStage{this,15.f}});
        AddStage(shared<TwinBladeStage>{new TwinBladeStage{this}});

        AddStage(shared<WaitStage>{new WaitStage{this,12.f}});
        AddStage(shared<HexagonStage>{new HexagonStage{this}});

        AddStage(shared<WaitStage>{new WaitStage{this,10.f}});
        AddStage(shared<UFOStage>{new UFOStage{this}});

        AddStage(shared<WaitStage>{new WaitStage{this,10.f}});
        AddStage(shared<ChaosStage>{new ChaosStage{this}});

        AddStage(shared<WaitStage>{new WaitStage{this,10.f}});
        AddStage(shared<BossStage>{new BossStage{this}});
    }

    void GameLevelOne::QuitGame()
    {
        GetApplication()->QuitApplication();
    }

    void GameLevelOne::RestartGame()
    {
        PlayerManager::Get().Reset();
        GetApplication()->LoadWorld<GameLevelOne>();
    }

    void GameLevelOne::GameOver()
    {
        // LOG("Game Over! ==================================");
        // Player Died in between some stage and lost 
        mGameplayHUD.lock()->GameFinsihed(false);
    }
    void GameLevelOne::AllGameStageFinished()
    {
        // All Game stages done player WON
        mGameplayHUD.lock()->GameFinsihed(true);
    }

    void GameLevelOne::SpawnCosmetics()
    {
        auto backdropActor = SpawnActor<BackdropActor>("SpaceShooterRedux/Backgrounds/darkPurple.png");
        weak<BackgroundLayer> planets = SpawnActor<BackgroundLayer>();
        planets.lock()->SetAssets(
            {
                "SpaceShooterRedux/PNG/Planets/Planet1.png",
                "SpaceShooterRedux/PNG/Planets/Planet2.png",
                "SpaceShooterRedux/PNG/Planets/Planet3.png",
                "SpaceShooterRedux/PNG/Planets/planet4.png",
                "SpaceShooterRedux/PNG/Planets/planet5.png",
                "SpaceShooterRedux/PNG/Planets/planet6.png",
                "SpaceShooterRedux/PNG/Planets/planet7.png"
            }
        );

        planets.lock()->SetSpriteCount(1);
        planets.lock()->SetSizes(1.f, 1.5f);
        planets.lock()->SetVelocities({0.f,30.f},{0.f,80.f});

        weak<BackgroundLayer> meteors = SpawnActor<BackgroundLayer>();
        meteors.lock()->SetAssets(
            {
                "SpaceShooterRedux/PNG/Meteors/meteorGrey_tiny1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_tiny2.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_big1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_big2.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_big3.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_big4.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_med1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_med3.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_small1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_small2.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_tiny1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_tiny2.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_big1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_big2.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_big3.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_big4.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_med1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_med2.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_small1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_small2.png"
            }
        );

        meteors.lock()->SetSpriteCount(20);
        meteors.lock()->SetSizes(0.2f, 0.5f);
    }
}