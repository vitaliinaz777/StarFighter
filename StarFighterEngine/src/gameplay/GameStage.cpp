#include "gameplay/GameStage.h"
#include "framework/Core.h"

namespace st
{
    GameStage::GameStage(World* owningWorld)
        : mWorld{ owningWorld },
        mStageFinished{false}
    {
    }

    void GameStage::StartStage()
    {
        LOG("Stage started");
    }

    void GameStage::TickStage(float deltaTime)
    {
        // LOG("Stage ticking");
    }

    void GameStage::FinishStage()
    {
        mStageFinished = true;
        StageFinished();
        OnStageFinishedDelegate.Broadcast();
    }

    void GameStage::StageFinished()
    {
        LOG("Stage finished");
    }
}