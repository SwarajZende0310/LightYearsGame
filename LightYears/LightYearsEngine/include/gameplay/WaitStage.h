#pragma once

#include"gameplay/GameStage.h"

namespace ly
{
    class WaitStage : public GameStage
    {
        public:
            WaitStage(World* world, float waitDuration = 5.f);

            virtual void StartStage();
        private:
            float mWaitDuration;
    };
}