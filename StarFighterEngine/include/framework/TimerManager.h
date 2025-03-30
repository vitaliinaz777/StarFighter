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
        bool Expired() const; // timer reached or 'Object' destroyd
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
        void SetTimer(weak<Object> weakRef, void(ClassName::*callback)(), float duration, bool repeat = false)
        {
            mTimers.push_back(
                Timer( weakRef, 
                      [=] {(static_cast<ClassName*>(weakRef.lock().get())->*callback)(); }, // this lambda passes in pair 'mListener' to 'std::function<void()> callback'
                      duration,
                      repeat
                )
            );
        }

        void UpdateTimer(float deltaTime);

    protected:
        TimerManager();

    private:
        static unique<TimerManager> timerManager;
        List<Timer> mTimers;
    };
}