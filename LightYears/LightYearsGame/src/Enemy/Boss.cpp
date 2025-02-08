#include"Enemy/Boss.h"

namespace ly
{
    Boss::Boss(World *owningWorld)
        : EnemySpaceship{owningWorld,"SpaceShooterRedux/PNG/Enemies/boss.png"},
        mSpeed{100.f},
        mSwitchDistanceToEdge{100.f}
    {
        SetActorRotation(90.f);
    }
    
    void Boss::Tick(float deltaTime)
    {
        EnemySpaceship::Tick(deltaTime);
    }
}