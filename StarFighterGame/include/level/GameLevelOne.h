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
        weak<PlayerSpaceship> testPalyerSpaceship;
    };
}