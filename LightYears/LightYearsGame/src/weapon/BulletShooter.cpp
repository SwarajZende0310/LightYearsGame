#include"weapon/BulletShooter.h"

namespace ly
{
    BulletShooter::BulletShooter(Actor *owner,float cooldownTime)
        :Shooter{owner},
        mCooldownClock{},
        mCOoldownTime{cooldownTime}
    {

    }
    bool BulletShooter::isOnCooldown() const
    {
        if(mCooldownClock.getElapsedTime().asSeconds() > mCOoldownTime)
        {
            return false;
        }
        return true;
    }
    void BulletShooter::ShootImpl()
    {
        mCooldownClock.restart();
        LOG("Shooting!");
    }
}