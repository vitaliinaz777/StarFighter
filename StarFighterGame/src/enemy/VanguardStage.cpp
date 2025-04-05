#include "enemy/Vanguard.h"
#include "enemy/VanguardStage.h"
#include "framework/World.h"

namespace st
{
VanguardStage::VanguardStage(World *owningWorld)
    : GameStage(owningWorld),
    mSpawnInterval{1.5f},
    mSwitchInterval{4.f},
    mSpawnDistanceToEdge{100.f},
    mLeftSpawnLoc{0.0f, 0.0f},
    mRightSpawnLoc{0.0f, 0.0f},
    mSpawnLoc{0.0f, 0.0f},
    mRowsToSpawn{3},
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
    TimerManager::Get().ClearTimer(mSpawnTimerIndexHandle);
    TimerManager::Get().ClearTimer(mSwitchTimerIndexHandle);
}

void VanguardStage::SpawnVanguard()
{
    weak<Vanguard> newVanguard = GetWorld()->SpawnActor<Vanguard>();
    newVanguard.lock()->SetActorLocation(mSpawnLoc);
    ++mCurrentRowVanguardCount;
    if (mCurrentRowVanguardCount == mVanguardsPerRow) {
        TimerManager::Get().ClearTimer(mSpawnTimerIndexHandle);
        mSwitchTimerIndexHandle = TimerManager::Get().SetTimer(GetWeakRef(), &VanguardStage::SwitchRow, mSwitchInterval, false);
        mCurrentRowVanguardCount = 0;
    }
}

void VanguardStage::SwitchRow()
{
    LOG("VanguardStage::SwitchRow()");
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
    mSpawnTimerIndexHandle = TimerManager::Get().SetTimer(GetWeakRef(), &VanguardStage::SpawnVanguard, mSpawnInterval, true);

    ++mRowSpawnCount;
}
} // namespace st