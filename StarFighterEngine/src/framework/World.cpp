#include "framework/World.h"
#include "framework/Core.h"
#include "framework/Actor.h"
#include "framework/Application.h"

namespace st
{
    World::World(Application* owningApp)
        : mOwningApp{ owningApp },
        mBeganPaly{ false },
        mActors{},
        mPendingActors{}
    {
    }

    World::~World()
    {
    }

    // this function is called by the application when the world is loaded
    void World::BeginPlayInternal()
    {
        // this is called only once
        if (!mBeganPaly) {
            mBeganPaly = true;
            BeginPlay();
        }
    }

    void World::TickInternal(float deltaTime)
    {
        // put all pending actors in the world
        for (shared<Actor> actor : mPendingActors) {
            mActors.push_back(actor);
            actor->BeginPlayInternal();
        }
        mPendingActors.clear();

        // tick all actors
        for (auto iter = mActors.begin(); iter != mActors.end();) {
            if (iter->get()->IsPendingDestroy()) {
                iter = mActors.erase(iter);
            } else {
                iter->get()->TickInternal(deltaTime);
                ++iter;
            }
        }

        Tick(deltaTime);
    }

    void World::Render(sf::RenderWindow& window)
    {
        for (auto& actor : mActors) {
            actor->Render(window);
        }
    }

    sf::Vector2u World::GetWindowSize() const
    {
        return mOwningApp->GetWindowSize();
    }

    void World::BeginPlay()
    {
        LOG("World began play");
    }

    void World::Tick(float deltaTime)
    {
        //LOG("World tick at frame rate %f", 1.f / deltaTime);
    }
}