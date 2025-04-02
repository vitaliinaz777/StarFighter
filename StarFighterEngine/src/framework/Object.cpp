#include "framework/Object.h"
#include "framework/Core.h"

namespace st {
    Object::Object()
        : mIsPendingDestroy{ false }
    {
    }
    
    Object::~Object()
    {
        //LOG("Object destroyed");
    }
    
    void Object::Destroy()
    {
        onDestroyDelegate.Broadcast(this);
        mIsPendingDestroy = true;
    }
    
    // Instance implementing 'Object' should be stored as shared pointer,
    // in the frirst palce, to be able to get a weak reference from there.
    weak<Object> Object::GetWeakRef()
    {
        return shared_from_this();
    }
    
    weak<const Object> Object::GetWeakRef() const
    {
        return shared_from_this();
    }
}
