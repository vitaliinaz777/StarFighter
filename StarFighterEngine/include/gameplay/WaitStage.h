#pragma once

#include "gameplay/GameStage.h"

namespace st
{
    class WaitStage : public GameStage
    {
    public:
        WaitStage(World* owningWorld, float waitDuration = 5.f);

        virtual void StartStage() override;

    private:
        float mWaitDuration;
    };
}