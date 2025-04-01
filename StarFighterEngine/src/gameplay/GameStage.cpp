#include "gameplay/GameStage.h"
#include "framework/Core.h"

namespace st
{
    GamaStage::GamaStage(World* owningWorld)
        : mWorld{ owningWorld },
        mStageFinished{false}
    {
    }

    void GamaStage::StratStage()
    {
        LOG("Stage started");
    }

    void GamaStage::TickStage(float deltaTime)
    {
        LOG("Stage ticking");

    }

    void GamaStage::FinishStage()
    {
        OnStageFinishedDelegate.Broadcast();
        mStageFinished = true;
        StageFinished();
    }

    void GamaStage::StageFinished()
    {
        LOG("Stage finished");
    }
}