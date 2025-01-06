#pragma once

namespace ly
{
    class Actor;
    class Shooter
    {
        public:
            void Shoot();

            virtual bool CanShoot()const{return true;}
            virtual bool isOnCooldown()const{return false;}
            Actor* GetQwenr()const{return mOwner;}

        protected:
            Shooter(Actor*owner);

        private:
            virtual void ShootImpl() = 0 ;
            Actor* mOwner;
    };
}