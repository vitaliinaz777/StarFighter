#pragma once
#include <functional>
#include "framework/Core.h"

namespace st 
{
    // forward declaration
    class Object;

    template<typename... Args>
    class Delegate
    {
    public:
        // Accepts(bind) a callback function
        template<typename ClassName>
        void BindAction(weak<Object> obj, void(ClassName::*callback)(Args...)) // obj listen to this delegate
        {
            // Wrapper std::function
            std::function<bool (Args...)> callbackFunc = 
                // Lambda
                [obj, callback](Args... args)->bool // return bool
                {
                    if (!obj.expired()) {
                        (static_cast<ClassName*>(obj.lock().get())->*callback)(args...);
                        return true;
                        /*/ 
                        Call member function stored in '*calback' on an object stored in 'obj'
                        obj -> *calback() 
                        i.e.
                        Spaceship.OnHealthChanged()
                        
                        cast from pointer 'Object*' to actual pointer (e.g. 'Spaceship*)
                        'static_cast<ClassName*>(obj.lock().get())->'   means 'Spaceship'
                        '*callback'   means 'OnHealthChanged()'
                        /*/
                    } else {
                        LOG("Error: Attempting to bind action to an expired object.");
                        return false;
                    }

                };

            mCallbacks.push_back(callbackFunc);
        }

        void Broadcast(Args... args) 
        {
            for (auto iter = mCallbacks.begin(); iter != mCallbacks.end();)
            {
                if ((*iter)(args...)) {
                    ++iter;
                }
                else {
                    iter = mCallbacks.erase(iter);
                }
            }
        }

        void Clear() 
        {
            // TODO: check correctness
            mCallbacks.clear();
        }

    private:
        List<std::function<bool(Args...)>> mCallbacks; // if bool 'false' remove function from callbacks
    };
}

/*
    Callback is a function that is passed as an argument to another function. 
In C++, we cannot directly use the function name to pass them as a callback. 
We use function pointers to pass callbacks to other functions, 
then store these pointers in data structures, and invoke them later.

    Wrapper class 'std::function' is a template class in C++ 
that is used to wrap a particular function
or any other callable object such as a lambda, or function object. 
It is generally used to write generic code where we need to pass functions as arguments 
in another function (callbacks). 
It avoids the creation of extra overloads of the function 
that may take similar callback functions as arguments.

    Also we use exactly 'std::function' not an odinary function pointer, 
because we want Lambda to catch external parameters like 'obj' and '*calback'.
If we will use insted of 'std::function' a function pointer, like this:
From:
    std::function<bool (Args...)> callbackFunc = LAMBDA
To:
    bool (*callbackFunc)(Args...) = LAMBDA

It won't let us capture an external value of 'obj' and '*calback'.
Because a captureles Lambda will be converted implicitly or explicitly to
a function poiner.
*/