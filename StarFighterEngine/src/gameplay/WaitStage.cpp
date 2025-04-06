#include "gameplay/WaitStage.h"
#include "framework/TimerManager.h"

namespace st
{
    WaitStage::WaitStage(World* owningWorld, float waitDuration)
        : GameStage{ owningWorld },
        mWaitDuration{ waitDuration }
    {
    }

    void WaitStage::StartStage()
    {
        TimerManager::Get().SetTimer(GetWeakRef(), &WaitStage::FinishStage, mWaitDuration);
    }
}