#include"framework/Object.h"

namespace ly
{
    unsigned int Object::uniqueIDCounter = 0;
    Object::Object()
        :mIsPendingDestroy(false),
        mUniqueID{GetNextAvailableID()}
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

    unsigned int Object::GetNextAvailableID()
    {
        return uniqueIDCounter++;
    }
}