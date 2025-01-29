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
        AddStage(shared<UFOStage>{new UFOStage{this}});

        AddStage(shared<WaitStage>{new WaitStage{this,5.f}});
        AddStage(shared<VanguardStage>{new VanguardStage{this}});

        AddStage(shared<WaitStage>{new WaitStage{this,10.f}});
        AddStage(shared<TwinBladeStage>{new TwinBladeStage{this}});

        AddStage(shared<WaitStage>{new WaitStage{this,10.f}});
        AddStage(shared<HexagonStage>{new HexagonStage{this}});
    }
}