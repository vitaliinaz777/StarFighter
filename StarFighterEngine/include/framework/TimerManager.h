#include <functional>
#include "framework/Core.h"
#include "framework/Object.h"

namespace st
{
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
        unsigned int SetTimer(weak<Object> weakRef, void(ClassName::*callback)(), float duration, bool repeat = false)
        {
            ++timerIndexCounter;
            mTimers.insert({ timerIndexCounter,
                           Timer(weakRef,
                                [=] {(static_cast<ClassName*>(weakRef.lock().get())->*callback)(); }, // this lambda passes in pair 'mListener' to 'std::function<void()> callback'
                                duration,
                                repeat
                                )
                           });
            
            return timerIndexCounter;
        }

        void UpdateTimer(float deltaTime);

        void ClearTimer(unsigned int timerIndex);

    protected:
        TimerManager();

    private:
        static unique<TimerManager> timerManager;
        static unsigned int timerIndexCounter;
        Dictionary<unsigned int, Timer> mTimers;
    };
}