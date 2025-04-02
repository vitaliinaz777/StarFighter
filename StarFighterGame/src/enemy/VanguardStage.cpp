#include "enemy/VanguardStage.h"
#include "framework/World.h"

namespace st
{
VanguardStage::VanguardStage(World *owningWorld)
    : GameStage(owningWorld),
    mSpawnInterval{2.f},
    mSwitchInterval{5.f},
    mSpawnDistanceToEdge{100.f},
    mLeftSpawnLoc{0.0f, 0.0f},
    mRightSpawnLoc{0.0f, 0.0f},
    mSpawnLoc{0.0f, 0.0f},
    mRowsToSpawn{4},
    mRowSpawnCount{0},
    mVanguardsPerRow{5},
    mCurrentRowVanguardCount{0}
{
}

void VanguardStage::StartStage()
{
    auto windowSize = GetWorld()->GetWindowSize();
    mLeftSpawnLoc = sf::Vector2f{mSpawnDistanceToEdge, -100.f};
    mRightSpawnLoc = sf::Vector2f{windowSize.x - mSpawnDistanceToEdge, -100.f};

    SwitchRow();
}

void VanguardStage::StageFinished()
{
}

void VanguardStage::SpawnVanguard()
{
}

void VanguardStage::SwitchRow()
{
    if (mRowSpawnCount == mRowsToSpawn) {
        FinishStage();
        return;
    }

    if (mSpawnLoc == mLeftSpawnLoc) {
        mSpawnLoc = mRightSpawnLoc;
    }
    else {
        mSpawnLoc = mLeftSpawnLoc;
    }

    // Start a timer that periodically call SpawnVanguard()
    mSpawnTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &VanguardStage::SpawnVanguard, mSpawnInterval, true);

    ++mRowSpawnCount;
}
} // namespace st