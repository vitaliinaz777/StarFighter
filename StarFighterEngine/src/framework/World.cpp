#include "framework/Actor.h"
#include "framework/Application.h"
#include "framework/Core.h"
#include "framework/World.h"
#include "gameplay/GameStage.h"

namespace st
{
    World::World(Application* owningApp)
        : mOwningApp{ owningApp },
        mBeganPaly{ false },
        mActors{},
        mPendingActors{},
        mGameStages{},
        mCurrentStageIter{ mGameStages.end()}
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
            InitGameStages();
            StartStages();
        }
    }

    void World::TickInternal(float deltaTime)
    {
        // Put all pending actors in the world
        for (shared<Actor> actor : mPendingActors) {
            mActors.push_back(actor);
            actor->BeginPlayInternal();
        }
        mPendingActors.clear();

        // Tick all actors
        for (auto iter = mActors.begin(); iter != mActors.end();) {
            iter->get()->TickInternal(deltaTime);
            ++iter;
        }

        // Tick current stage
        if (mCurrentStageIter != mGameStages.end()) {
            mCurrentStageIter->get()->TickStage(deltaTime);
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

    void World::CleanCycle()
    {
        // Claen Actros pending for destroy
        for (auto iter = mActors.begin(); iter != mActors.end();) 
        {
            if (iter->get()->IsPendingDestroy()) {
                iter = mActors.erase(iter);
            } else {
                ++iter;
            }
        }
    }

    void World::AddStage(const shared<GameStage>& newStage)
    {
        mGameStages.push_back(newStage);
    }

    void World::BeginPlay()
    {
        LOG("World began play");
    }

    void World::Tick(float deltaTime)
    {
        //LOG("World tick at frame rate %f", 1.f / deltaTime);
    }

    void World::InitGameStages()
    {
    }

    void World::AllGameStageFinished()
    {
        LOG("All Stages Finished");
    }

    void World::NextGameStage()
    {
        mCurrentStageIter = mGameStages.erase(mCurrentStageIter);
        if(mCurrentStageIter != mGameStages.end()){
            mCurrentStageIter->get()->StartStage();
            mCurrentStageIter->get()->OnStageFinishedDelegate.BindAction(GetWeakRef(), &World::NextGameStage);
        } else {
            AllGameStageFinished();
        }
    }

    void World::StartStages()
    {
        mCurrentStageIter = mGameStages.begin();
        mCurrentStageIter->get()->StartStage();
        mCurrentStageIter->get()->OnStageFinishedDelegate.BindAction(GetWeakRef(), &World::NextGameStage);
    }
}