#include "framework/TimerManager.h"

namespace st
{
    // Variable 'timerKeyCounter' is static, 
    // so it need to have starting value to be compiled.
    // If not, you'll get a link error.
    unsigned int TimerIndexHandle::timerKeyCounter = 0;

    TimerIndexHandle::TimerIndexHandle()
        : mTimerKey{ GenerateNextTimerKey() }
    {
    }

    bool operator==(const TimerIndexHandle& lhs, const TimerIndexHandle& rhs)
    {
        return lhs.GetTimerKey() == rhs.GetTimerKey();
    }

    Timer::Timer(weak<Object> weakRef, std::function<void()> callback, float duration, bool repeat)
        : mListener{ weakRef , callback },
        mDuration{ duration },
        mRepeat{ repeat },
        mTimeCounter{0.f},
        mIsExpired{false}
    {
    }

    void Timer::TickTime(float deltaTime)
    {
        if (IsExpired()) return;

        mTimeCounter += deltaTime;
        if (mTimeCounter >= mDuration) {
            mListener.second(); // call lambda (callback function)

            if (mRepeat) {
                mTimeCounter = 0.f;
            } else {
                SetExpired();
            }
        }
    }

    bool Timer::IsExpired() const
    {
        // If timer is expired || weak pointer is expired || 'Object' pending for destroy
        return mIsExpired || mListener.first.expired() || mListener.first.lock()->IsPendingDestroy(); 
    }

    void Timer::SetExpired()
    {
        mIsExpired = true;
    }


    // Variable 'timerManager' is static, 
    // so it need to have starting value to be compiled.
    // If not, you'll get a link error.
    unique<TimerManager> TimerManager::timerManager{ nullptr };

    TimerManager::TimerManager()
        : mTimers{}
    {
    }

    TimerManager& TimerManager::Get()
    {
        if (!timerManager) {
            timerManager = unique<TimerManager>(new TimerManager{});
        }

        return *timerManager;
    }

    void TimerManager::UpdateTimer(float deltaTime)
    {
        for (auto iter = mTimers.begin(); iter != mTimers.end(); ) {
            if (iter->second.IsExpired()) {
                iter = mTimers.erase(iter); // clean mTimers if expired automaticly
            } else {
                iter->second.TickTime(deltaTime);
                ++iter;
            }
        }
    }

    void TimerManager::ClearTimer(TimerIndexHandle timerIndexHandle)
    {
        auto iter = mTimers.find(timerIndexHandle);
        if (iter != mTimers.end()) {
            iter->second.SetExpired();
        }
    }
}