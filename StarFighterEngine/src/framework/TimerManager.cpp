#include "framework/TimerManager.h"

namespace st
{
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


    // Variables 'timerManager' and 'timerIndexCounter' are static, 
    // so they need to have starting value to be compiled.
    // If not, you'll get a link error.
    unique<TimerManager> TimerManager::timerManager{ nullptr };
    unsigned int TimerManager::timerIndexCounter = 0;

    TimerManager::TimerManager()
        : mTimers{}
    {
    }

    TimerManager& TimerManager::Get()
    {
        if (!timerManager) {
            timerManager = std::move(unique<TimerManager>(new TimerManager{}));
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

    void TimerManager::ClearTimer(unsigned int timerIndex)
    {
        auto iter = mTimers.find(timerIndex);
        if (iter != mTimers.end()) {
            iter->second.SetExpired();
        }
    }
}