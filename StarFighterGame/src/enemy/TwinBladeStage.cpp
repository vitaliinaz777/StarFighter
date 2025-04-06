#include "enemy/TwinBlade.h"
#include "enemy/TwinBladeStage.h"
#include "framework/World.h"

namespace st
{
    TwinBladeStage::TwinBladeStage(World* owningWorld)
        : GameStage{ owningWorld },
        mSpawnInterval{1.5f},
        mSpawnDistanceToCenter{100.f},
        mLeftSpawnLoc{ owningWorld->GetWindowSize().x/2.f - mSpawnDistanceToCenter, -100.f},
        mRightSpawnLoc{ owningWorld->GetWindowSize().x/2.f + mSpawnDistanceToCenter, -100.f },
        mSpawnLoc{ mLeftSpawnLoc },
        mSpawnAmount{10},
        mCurrentSpawnCount{0}
    {
    }

    void TwinBladeStage::StartStage()
    {
        mSpawnTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &TwinBladeStage::SpawnTwinBlade,
                                                         mSpawnInterval, true );
    }

    void TwinBladeStage::SpawnTwinBlade()
    {
        weak<TwinBlade> newTwinBlade = GetWorld()->SpawnActor<TwinBlade>();
        newTwinBlade.lock()->SetActorLocation(mSpawnLoc);

        // Swap location: left <|> right
        if (mSpawnLoc == mLeftSpawnLoc) {
            mSpawnLoc = mRightSpawnLoc;
        } else {
            mSpawnLoc = mLeftSpawnLoc;
        }

        ++mCurrentSpawnCount;
        if (mCurrentSpawnCount == mSpawnAmount) {
            FinishStage();
        }
    }

    void TwinBladeStage::StageFinished()
    {
        TimerManager::Get().ClearTimer(mSpawnTimerHandle);
    }
}