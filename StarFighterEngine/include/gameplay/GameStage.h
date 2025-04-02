#pragma once
#include "framework/Delegate.h"
#include "framework/Object.h"

namespace st
{
    class World;

    class GameStage : public Object
    {
    public:
        GameStage(World* owningWorld);
        const World* GetWorld() const { return mWorld; }
        World* GetWorld() { return mWorld; }

        Delegate<> OnStageFinishedDelegate;

        virtual void StartStage();
        virtual void TickStage(float deltaTime);
        void FinishStage();
        bool IsStageFinished() const { return mStageFinished; }

    private:
        virtual void StageFinished();

        World* mWorld;
        bool mStageFinished;
    };
}