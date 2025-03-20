#pragma once
#include "framework/Core.h"
#include "framework/Object.h"

namespace st {
    template<typename... Args>
    class Delegate
    {
    public:
        // Function that accepts(bind) a callback
        template<typename ClassName>
        void BindAction(weak<Object> obj, void(ClassName::*callback)(Args...)) // obj listen to this delegate
        {
            *callback();
        }
    };
}