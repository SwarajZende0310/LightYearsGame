#include"Level/GameLevelOne.h"
#include"player/PlayerSpaceship.h"
#include"Enemy/Vanguard.h"
#include"framework/TimerManager.h"
#include"gameplay/GameStage.h"
#include"Enemy/VanguardStage.h"
#include"Enemy/TwinBladeStage.h"

namespace ly
{
    GameLevelOne::GameLevelOne(Application *owningApp)
        :World{owningApp}
    {
        testPlayerSpaceship = SpawnActor<PlayerSpaceship>();
        testPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(300,690));
        testPlayerSpaceship.lock()->SetActorRotation(-90.f);
    }

    void GameLevelOne::BeginPlay()
    {
        
    }

    void GameLevelOne::InitGameStages()
    {
        AddStage(shared<TwinBladeStage>{new TwinBladeStage{this}});
        AddStage(shared<VanguardStage>{new VanguardStage{this}});
    }
}