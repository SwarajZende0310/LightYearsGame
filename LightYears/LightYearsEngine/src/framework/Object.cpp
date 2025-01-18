#include"framework/Object.h"

namespace ly
{
    Object::Object()
        :mIsPendingDestroy(false)
    {

    }
    Object::~Object()
    {
        // LOG("Object Destroyed");
    }
    void Object::Destroy()
    {
        onDestroy.Broadcast(this);
        mIsPendingDestroy = true;
    }

    weak<Object> Object::GetWeakRef()
    {
        return weak_from_this();
    }

    weak<const Object> ly::Object::GetWeakRef() const
    {
        return weak_from_this();
    }
}