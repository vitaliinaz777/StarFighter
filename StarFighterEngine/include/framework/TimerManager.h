#pragma once
#include <functional>
#include "framework/Core.h"
#include "framework/Object.h"

namespace st
{
    struct TimerIndexHandle
    {
    public:
        TimerIndexHandle();
        unsigned int GetTimerKey() const { return mTimerKey; }

    private:
        static unsigned int GetNextTimerKey() { return ++timerKeyCounter; }

        static unsigned int timerKeyCounter;
        unsigned int mTimerKey;
    };


    // used as third argument(hash function) in Dictionary
    struct TimerIndexHandleHashFunction
    {
    public:
        std::size_t operator()(const TimerIndexHandle& timerIndexHandle) const
        {
            return timerIndexHandle.GetTimerKey();
        }
    };


    // Akso used in Dictionary for comparing two 'TimerIndexHandle'
    bool operator==(const TimerIndexHandle& lhs, const TimerIndexHandle& rhs);


    // Struct represent different types of timers
    struct Timer
    {
    public:
        Timer(weak<Object> weakRef, std::function<void()> callback, float duration, bool repeat);
        void TickTime(float deltaTime);
        bool IsExpired() const; // timer reached or 'Object' destroyd
        void SetExpired();

    private:
        std::pair<weak<Object>, std::function<void()>> mListener;
        float mDuration;
        bool mRepeat;
        float mTimeCounter;
        bool mIsExpired;
    };

    // Singelton class manages structs 'Timer'
    class TimerManager
    {
    public:
        static TimerManager& Get();

        template <typename ClassName>
        TimerIndexHandle SetTimer(weak<Object> weakRef, void(ClassName::*callback)(), float duration, bool repeat = false)
        {
            TimerIndexHandle newHandle{};
            mTimers.insert({ newHandle,
                           Timer(weakRef,
                                [=] {(static_cast<ClassName*>(weakRef.lock().get())->*callback)(); }, // this lambda passes in pair 'mListener' to 'std::function<void()> callback'
                                duration,
                                repeat
                                )
                           });
            
            return newHandle;
        }

        void UpdateTimer(float deltaTime);

        void ClearTimer(TimerIndexHandle timerIndexHandle);

    protected:
        TimerManager();

    private:
        static unique<TimerManager> timerManager;

        Dictionary<TimerIndexHandle, Timer, TimerIndexHandleHashFunction> mTimers;
    };
}