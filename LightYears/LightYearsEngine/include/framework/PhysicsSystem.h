#pragma once
#include<box2d/b2_world.h>
#include<box2d/b2_body.h>
#include<box2d/b2_polygon_shape.h>
#include<box2d/b2_fixture.h>

#include"framework/Core.h"
#include"framework/Actor.h"
#include"framework/MathUtility.h"

namespace ly
{
    class Actor;
    class PhysicsSystem
    {
        public:
            static PhysicsSystem& Get();
            void Step(float deltaTime);
            b2Body* AddListener(Actor*listener);
            void RemoveListener(b2Body* bodyToRemove);

            float GetPhysicsScale()const{return mPhysicsScale;}
        protected:
            PhysicsSystem();
        private:
            static unique<PhysicsSystem> physicsSystem;
            b2World mPhysicsWorld;
            float mPhysicsScale;
            int mVelocityIterations;
            int mPositionIterations;
    };
}