#pragma once
#include"framework/Actor.h"

namespace ly
{
    class Bullet : public Actor
    {
    public:
        Bullet(World* world, Actor * owner, const std::string & texturePath, float speed = 600.f, float damage = 10.f);

        void SetSpeed(float newSpeed);
        void SetDamage(float newDamage);

        virtual void Tick(float deltaTime)override;
        void Move(float deltaTime);
    private:
        Actor* mOwner;
        float mSpeed;
        float mDamage;
    };
}
