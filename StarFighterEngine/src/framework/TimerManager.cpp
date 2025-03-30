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
        if (Expired()) return;

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

    bool Timer::Expired() const
    {
        // If timer is expired || weak pointer is expired || 'Object' pending for destroy
        return mIsExpired || mListener.first.expired() || mListener.first.lock()->IsPendingDestroy(); 
    }

    void Timer::SetExpired()
    {
        mIsExpired = true;
    }


    // Variable 'timerManager' is static, 
    // so it needs to have starting value to be compiled.
    // If not, you'll get a link error.
    unique<TimerManager> TimerManager::timerManager{ nullptr };

    TimerManager::TimerManager()
        : mTimers{}
    {
    }

    void TimerManager::UpdateTimer(float deltaTime)
    {
        for (Timer& timer : mTimers)
        {
            timer.TickTime(deltaTime);
        }
    }

    TimerManager& TimerManager::Get()
    {
        if (!timerManager) {
            timerManager = std::move( unique<TimerManager>( new TimerManager{} ));
        }

        return *timerManager;
    }
}