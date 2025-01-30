#pragma once

#include<functional>
#include"framework/Actor.h"

namespace ly
{
    class PlayerSpaceship;
    using RewardFunction = std::function<void(PlayerSpaceship*)>;

    class Reward : public Actor
    {
        public:
            Reward(World* world, const std::string& texturePath, RewardFunction rewardFunction, float speed = 200.f);
            virtual void BeginPlay()override;
            virtual void Tick(float deltaTime)override;
        private:
            virtual void OnActorBeginOverlap(Actor* otherActor)override;
            float mSpeed;
            RewardFunction mRewardFunc;
    };

    using RewardFactoryFunc = std::function<weak<Reward>(World*)>;

    weak<Reward> CreateHealthReward(World* world);
    weak<Reward> CreateThreewayShooterReward(World* world);
    weak<Reward> CreateFrontalWiperReward(World* world);
    weak<Reward> CreateReward(World* world, const std::string& texturePath, RewardFunction rewardFunction);

    void RewardHealth(PlayerSpaceship* player);
    void RewardThreewayShooter(PlayerSpaceship* player);
    void RewardFrontalWiper(PlayerSpaceship* player);
}