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
#include"player/PlayerManager.h"
#include"widgets/GameplayHUD.h"

namespace ly
{
    GameLevelOne::GameLevelOne(Application *owningApp)
        :World{owningApp}
    {
        
    }

    void GameLevelOne::BeginPlay()
    {
        Player& newPlayer = PlayerManager::Get().CreateNewPlayer();
        mPlayerSpaceship = newPlayer.SpawnSpaceship(this);
        mPlayerSpaceship.lock()->onActorDestroyed.BindAction(GetWeakRef(), &GameLevelOne::PlayerSpaceShipDestroyed);

        mGameplayHUD = SpawnHUD<GameplayHUD>();
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
    }

    void GameLevelOne::GameOver()
    {
        LOG("Game Over! ==================================");
    }
}