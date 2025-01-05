#pragma once
#include"framework/Core.h"

namespace ly
{
    class Object
    {
        public:
            Object();
            virtual ~Object();

            void Destroy();
            bool IsPendingDestroy() const { return mIsPendingDestroy; }
        private:
            bool mIsPendingDestroy;
    };
}