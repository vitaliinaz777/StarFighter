#pragma once
#include "framework/World.h"
#include "framework/TimerManager.h"

namespace st
{
    class PlayerSpaceship;

    class GameLevelOne : public World
    {
    public:
        GameLevelOne(Application* owningApp);

    private:
        virtual void BeginPlay() override;
        virtual void InitGameStages() override;

        weak<PlayerSpaceship> testPalyerSpaceship;
    };
}