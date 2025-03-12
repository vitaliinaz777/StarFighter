#include "framework/PhysicsSystem.h"

namespace st
{
    // variable "physicsSystem" is static, 
    // so it needs to have starting value to compile
    // if not you'll get a link error 
    unique<PhysicsSystem> PhysicsSystem::physicsSystem{ nullptr };

    PhysicsSystem PhysicsSystem::Get()
    {
        if (!physicsSystem) {
            physicsSystem = std::move(unique<PhysicsSystem>{new PhysicsSystem});
        }

        return *physicsSystem;
    }

    PhysicsSystem::PhysicsSystem()
        : mPhysicsWorld{ b2Vec2{0.f,0.f} }, // 0.f,0.f meams no gravity
        mPhysicsScale{0.01f}
    {
    }
}