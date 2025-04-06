#pragma once
#include <SFML/Graphics.hpp>
#include "gameplay/GameStage.h"
#include "framework/TimerManager.h"

namespace st
{
    class TwinBladeStage : public GameStage
    {
    public:
        TwinBladeStage(World* owningWorld);
        virtual void StartStage() override;

    private:
        void SpawnTwinBlade();
        virtual void StageFinished() override;

        float mSpawnInterval;
        float mSpawnDistanceToCenter;

        sf::Vector2f mLeftSpawnLoc;
        sf::Vector2f mRightSpawnLoc;
        sf::Vector2f mSpawnLoc;

        int mSpawnAmount;
        int mCurrentSpawnCount;

        TimerIndexHandle mSpawnTimerHandle;
    };
}