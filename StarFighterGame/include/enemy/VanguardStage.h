#pragma once
#include "framework/TimerManager.h"
#include "gameplay/GameStage.h"
#include <SFML/Graphics.hpp>

namespace st
{
    class VanguardStage : public GameStage
    {
      public:
        VanguardStage(World *owningWorld);
        virtual void StartStage() override;

      private:
        virtual void StageFinished() override;
        void SpawnVanguard();
        void SwitchRow();

        float mSpawnInterval;
        float mSwitchInterval;
        float mSpawnDistanceToEdge;

        sf::Vector2f mLeftSpawnLoc;
        sf::Vector2f mRightSpawnLoc;
        sf::Vector2f mSpawnLoc;

        TimerIndexHandle mSpawnTimerIndexHandle;
        TimerIndexHandle mSwitchTimerIndexHandle;

        int mRowsToSpawn;
        int mRowSpawnCount;

        int mVanguardsPerRow;
        int mCurrentRowVanguardCount;
    };
} // namespace st