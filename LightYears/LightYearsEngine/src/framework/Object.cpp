#include"framework/Object.h"

namespace ly
{
    Object::Object()
        :mIsPendingDestroy(false)
    {

    }
    Object::~Object()
    {
        LOG("Object Destroyed");
    }
    void Object::Destroy()
    {
        mIsPendingDestroy = true;
    }
}