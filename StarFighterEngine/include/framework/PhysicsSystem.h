#pragma once
#include "framework/Core.h"
#include <box2d/b2_world.h>

namespace st
{
    class Actor; // forward declaration
    
    // implement b2ContactListener class to get contact inforamtion
    class PhysicsContactListener : public b2ContactListener
    {
        virtual void BeginContact(b2Contact* contact) override;
        virtual void EndContact(b2Contact* contact) override;
    };

    // Singelton class
    class PhysicsSystem 
    {
    public:
        static PhysicsSystem& Get();
        void Step(float deltaTime);
        b2Body* AddListener(Actor* listener);
        void RemoveListener(b2Body* bodyToRemove);

        float GetPhysicsScale() const { return mPhysicsScale; };

        // Completely purge the physiscs system and recreate a new one.
        // Useful when we have a new world or a new map loaded.
        static void Cleanup();

    protected:
        PhysicsSystem();

    private:
        void ProcessPendingRemoveListeners();

        static unique<PhysicsSystem> physicsSystem;
        b2World mPhysicsWorld;

        float mPhysicsScale;
        int mVelocityIterations;
        int mPositionIterations;

        PhysicsContactListener mContactListener;

        Set<b2Body*> mPendingRemoveListeners;
    };
}