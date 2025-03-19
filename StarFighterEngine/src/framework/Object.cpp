#include "framework/Object.h"
#include "framework/Core.h"

namespace st {
    Object::Object()
        : mIsPendingDestroy{ false }
    {
    }
    Object::~Object()
    {
        LOG("Object destroyed");
    }
    void Object::Destroy()
    {
        mIsPendingDestroy = true;
    }
    weak<Object> Object::GetWeakRef()
    {
        return weak_from_this();
    }
    weak<const Object> Object::GetWeakRef() const
    {
        return weak_from_this();
    }
}
