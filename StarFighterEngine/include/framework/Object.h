#pragma once
#include <memory>
#include "framework/Core.h"
#include "framework/Delegate.h"

namespace st {
    // Base class for all objects in the game
    class Object : public std::enable_shared_from_this<Object>
    {
    public:
        Object();
        virtual ~Object();

        virtual void Destroy();
        bool IsPendingDestroy() const { return mIsPendingDestroy; }

        weak<Object> GetWeakRef();
        weak<const Object> GetWeakRef() const;

        // TODO: complete onDestroy functionality
        Delegate<Object*> onDestroyDelegate;

    private:
        bool mIsPendingDestroy;
    };
}