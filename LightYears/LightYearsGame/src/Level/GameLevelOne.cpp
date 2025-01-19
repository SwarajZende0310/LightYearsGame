#include"Level/GameLevelOne.h"
#include"player/PlayerSpaceship.h"
#include"Enemy/Vanguard.h"
#include"framework/TimerManager.h"

namespace ly
{
    GameLevelOne::GameLevelOne(Application *owningApp)
        :World{owningApp}
    {
        testPlayerSpaceship = SpawnActor<PlayerSpaceship>();
        testPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(300,690));
        testPlayerSpaceship.lock()->SetActorRotation(-90.f);

        weak<Vanguard> testSpaceship = SpawnActor<Vanguard>();
        testSpaceship.lock()->SetActorLocation(sf::Vector2f(300.f,0.f));
    }

    void GameLevelOne::BeginPlay()
    {
        timerIndex_test = TimerManager::Get().SetTimer(GetWeakRef(),&GameLevelOne::TimerCallback_Test,2,true);
    }
    
    void GameLevelOne::TimerCallback_Test()
    {
        LOG("Callback called!");
        TimerManager::Get().ClearTimer(timerIndex_test);
    }
}