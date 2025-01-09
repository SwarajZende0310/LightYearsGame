#pragma once
#include<box2d/b2_world.h>
#include<box2d/b2_body.h>
#include<box2d/b2_polygon_shape.h>
#include<box2d/b2_fixture.h>
#include<box2d/b2_contact.h>

#include"framework/Core.h"
#include"framework/Actor.h"
#include"framework/MathUtility.h"

namespace ly
{
    class Actor;

    class PhysicsConatctListener : public b2ContactListener
    {
        virtual void BeginContact(b2Contact* contact)override;
        virtual void EndContact(b2Contact* contact)override;
    };

    class PhysicsSystem
    {
        public:
            static PhysicsSystem& Get();
            void Step(float deltaTime);
            b2Body* AddListener(Actor*listener);
            void RemoveListener(b2Body* bodyToRemove);

            float GetPhysicsScale()const{return mPhysicsScale;}

            static void Cleanup(); 
        protected:
            PhysicsSystem();
        private:
            void ProcessPendingListeners();
            static unique<PhysicsSystem> physicsSystem;
            b2World mPhysicsWorld;
            float mPhysicsScale;
            int mVelocityIterations;
            int mPositionIterations;

            PhysicsConatctListener mContactListener;
            Set<b2Body*> mPendingRemoveListener;
    };
}