#include "framework/TimerManager.h"

namespace st
{
    // Variable 'timerManager' is static, 
    // so it needs to have starting value to be compiled.
    // If not, you'll get a link error.
    unique<TimerManager> TimerManager::timerManager{ nullptr };

    TimerManager::TimerManager()
    {
    }

    TimerManager& TimerManager::Get()
    {
        if (!timerManager) {
            timerManager = std::move( unique<TimerManager>( new TimerManager{} ));
        }

        return *timerManager;
    }
}