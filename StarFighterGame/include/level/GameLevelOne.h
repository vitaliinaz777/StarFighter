#pragma once
#include "framework/World.h"

namespace st
{
    class PlayerSpaceship;

    class GameLevelOne : public World
    {
    public:
        GameLevelOne(Application* owningApp);

    private:
        virtual void BeginPlay() override;
        void TimerCallback_Test();

        weak<PlayerSpaceship> testPalyerSpaceship;

        unsigned int timerIndex_Test{0};
    };
}