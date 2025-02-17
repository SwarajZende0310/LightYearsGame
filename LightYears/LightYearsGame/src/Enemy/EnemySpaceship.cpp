#include"Enemy/EnemySpaceship.h"
#include"framework/MathUtility.h"
#include"player/PlayerManager.h"

namespace ly
{
    EnemySpaceship::EnemySpaceship(World *owningWorld, const std::string &texturePath, float collisionDamage, float rewardSpawnWeight, const List<RewardFactoryFunc> rewards)
        :Spaceship{owningWorld,texturePath},
        mCollisionDamage{collisionDamage},
        mScoreRewardAmt{10},
        mRewardSpawnWeight{rewardSpawnWeight},
        mRewardFactories{rewards}
    {
        SetTeamID(2);
    }

    void EnemySpaceship::Tick(float deltaTime)
    {
        Spaceship::Tick(deltaTime);
        if(isActorOutOfWindowBounds(GetActorGlobalBounds().width * 2.f))
        {
            Destroy();
        }
    }

    void EnemySpaceship::SetScoreAwardAmt(unsigned int amt)
    {
        mScoreRewardAmt = amt;
    }

    void EnemySpaceship::SetrewardSpawnWeight(float weight)
    {
        if(weight < 0 || weight > 1)
            return;
        mRewardSpawnWeight = weight;
    }

    void EnemySpaceship::SpawnReward()
    {
        if(mRewardFactories.size() == 0)return;

        if(mRewardSpawnWeight < RandomRange(0,1))
            return;

        int pick = (int)RandomRange(0, mRewardFactories.size());
        if(pick >= 0 && pick < mRewardFactories.size())
        {
            weak<Reward> newReward = mRewardFactories[pick](GetWorld());
            newReward.lock()->SetActorLocation(GetActorLocation());
        }
    }

    void EnemySpaceship::OnActorBeginOverlap(Actor *other)
    {
        Spaceship::OnActorBeginOverlap(other);

        if(IsOtherHostile(other))
        {
            other->ApplyDamage(mCollisionDamage);
        }
    }

    void EnemySpaceship::Blew()
    {
        SpawnReward();
        Player* player = PlayerManager::Get().GetPlayer();
        if(player)
        {
            player->AddScore(mScoreRewardAmt);
        }
    }
}