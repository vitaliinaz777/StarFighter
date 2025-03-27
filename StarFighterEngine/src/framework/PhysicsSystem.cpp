#include <box2d/b2_body.h>
#include <box2d/b2_contact.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>


#include "framework/PhysicsSystem.h"
#include "framework/Actor.h"
#include "framework/MathUtility.h"


namespace st
{
    PhysicsSystem::PhysicsSystem()
        : mPhysicsWorld{ b2Vec2{0.f,0.f} }, // 0.f,0.f means no gravity
        mPhysicsScale{ 0.01f }, // to make everything faster
        mVelocityIterations{ 8 },
        mPositionIterations{ 3 },
        mContactListener{},
        mPendingRemoveListeners{}
    {
        // Set b2ContactListener to listen for contact events and trigger 'BeginContact()' and 'EndContact()' signals
        mPhysicsWorld.SetContactListener(&mContactListener);

        mPhysicsWorld.SetAllowSleeping(false);
    }

    // Variable 'physicsSystem' is static, 
    // so it needs to have starting value to be compiled.
    // If not, you'll get a link error.
    unique<PhysicsSystem> PhysicsSystem::physicsSystem{ nullptr };

    PhysicsSystem& PhysicsSystem::Get()
    {
        if (!physicsSystem) {
            physicsSystem = std::move(unique<PhysicsSystem>{new PhysicsSystem});
        }

        return *physicsSystem;
    }

    void PhysicsSystem::Step(float deltaTime)
    {
        // Basicly we claen listeners afeter calling function 'currentWorld->TickInternal(deltaTime)'
        // in 'Application::TickInternal()' function,
        // and before 'b2World::Step()' function in PhysicsSystem class
        ProcessPendingRemoveListeners();

        mPhysicsWorld.Step(deltaTime, mVelocityIterations, mPositionIterations);
    }

    b2Body* PhysicsSystem::AddListener(Actor* listener)
    {
        if(listener->IsPendingDestroy()) return nullptr;

        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(listener);
        bodyDef.position.Set(listener->GetActorLocation().x * GetPhysicsScale(),
                             listener->GetActorLocation().y * GetPhysicsScale());
        bodyDef.angle = DegreesToRadians(listener->GetActorRotation());

        b2Body* body = mPhysicsWorld.CreateBody(&bodyDef);

        b2PolygonShape shape;
        auto bound = listener->GetActorGlobalBounds();
        shape.SetAsBox(bound.width / 2.f * GetPhysicsScale(), 
                       bound.height / 2.f * GetPhysicsScale());
        
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;
        fixtureDef.isSensor = true; // collects contact information, but never generates a collision response.

        body->CreateFixture(&fixtureDef);

        return body; 
    }

    void PhysicsSystem::RemoveListener(b2Body* bodyToRemove)
    {
        mPendingRemoveListeners.insert(bodyToRemove);
    }

    // Completely purge the physics system and recreate a new one.
    // Useful when we have a new world or a new map loaded.
    void PhysicsSystem::Cleanup() 
    {
        physicsSystem = std::move(unique<PhysicsSystem>{new PhysicsSystem});
    }

    void PhysicsSystem::ProcessPendingRemoveListeners()
    {
        for (auto listener : mPendingRemoveListeners) {
            mPhysicsWorld.DestroyBody(listener);
        }

        mPendingRemoveListeners.clear();
    }

    void PhysicsContactListener::BeginContact(b2Contact* contact)
    {
        Actor* ActorA = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
        Actor* ActorB = reinterpret_cast<Actor*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

        if (ActorA && !ActorA->IsPendingDestroy()) {
            ActorA->OnActorBeginOverlap(ActorB);
        }

        if (ActorB && !ActorB->IsPendingDestroy()) {
            ActorB->OnActorBeginOverlap(ActorA);
        }

    }

    void PhysicsContactListener::EndContact(b2Contact* contact)
    {
        Actor* ActorA = nullptr;
        Actor* ActorB = nullptr;

        if (contact->GetFixtureA() && contact->GetFixtureA()->GetBody()) {
            ActorA = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
        }

        if (contact->GetFixtureB() && contact->GetFixtureB()->GetBody()) {
            ActorB = reinterpret_cast<Actor*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);
        }

        if (ActorA && !ActorA->IsPendingDestroy()) {
            ActorA->OnActorEndOverlap(ActorB);
        }

        if (ActorB && !ActorB->IsPendingDestroy()) {
            ActorB->OnActorEndOverlap(ActorA);
        }
    }
}