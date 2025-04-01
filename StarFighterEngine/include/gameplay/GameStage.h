#pragma once
#include "framework/Object.h"
#include "framework/Delegate.h"

namespace st
{
    class World;

    class GamaStage : public Object
    {
    public:
        GamaStage(World* owningWorld);
        const World* GetWorld() const { return mWorld; }
        World* GetWorld() { return mWorld; }

        Delegate<> OnStageFinishedDelegate;

        virtual void StratStage();
        virtual void TickStage(float deltaTime);
        void FinishStage();
        bool IsStageFinished() const { return mStageFinished; }

    private:
        virtual void StageFinished();

        World* mWorld;
        bool mStageFinished
    };
}