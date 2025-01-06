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
        :mOwner{owner}
    {

    }
}