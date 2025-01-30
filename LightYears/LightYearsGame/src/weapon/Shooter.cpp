#include "weapon/Shooter.h"

namespace ly
{
    void Shooter::Shoot()
    {
        if(CanShoot() && !isOnCooldown())
        {
            ShootImpl();
        }
    }

    Shooter::Shooter(Actor *owner)
        :mOwner{owner},
        mCurrentLevel{1},
        mMaxLevel{4}
    {

    }

    void Shooter::IncrementLevel(int amt)
    {
        if(mCurrentLevel == mMaxLevel)return;
        ++mCurrentLevel;
    }    
}