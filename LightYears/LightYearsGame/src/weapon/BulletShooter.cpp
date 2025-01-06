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
        weak<Bullet> newBullet = GetOwner()->GetWorld()->SpawnActor<Bullet>(GetOwner(),"SpaceShooterRedux/PNG/Lasers/laserBlue01.png");
        newBullet.lock()->SetActorLocation(GetOwner()->GetActorLocation());
        newBullet.lock()->SetActorRotation(GetOwner()->GetActorRotation());
    }
}