#pragma once

namespace st {
    // Base class for all objects in the game
    class Object {
    public:
        Object();
        virtual ~Object();

        virtual void Destroy();
        bool IsPendingDestroy() const { return mIsPendingDestroy; }

    private:
        bool mIsPendingDestroy;
    };
}