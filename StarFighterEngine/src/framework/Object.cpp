#include "framework/Object.h"
#include "framework/Core.h"

namespace st
{
    Object::Object()
        : mIsPendingDestory{ false }
    {
    }

    Object::~Object()
    {
        LOG("Object Destoryed");
    }

    void Object::Destory()
    {
        mIsPendingDestory = true;
    }
}