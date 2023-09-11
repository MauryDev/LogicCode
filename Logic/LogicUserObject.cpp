#include "LogicUserObject.h"

size_t LogicCode::LogicUserObject::GetMemorySize(size_t len)
{
    return sizeof(LogicUserObject) + len;
}

LogicCode::LogicUserObject* LogicCode::LogicUserObject::FromObject(LogicCode::Object& _this)
{
    {
        return FromObject(&_this);
    }
}

LogicCode::LogicUserObject* LogicCode::LogicUserObject::FromObject(LogicCode::Object* _this)
{
    return (_this != nullptr && _this->type == ObjectType::UserObject ? _this->ptr<LogicUserObject>() : nullptr);

}

LogicCode::LogicUserObject* LogicCode::LogicUserObject::FromObject(Object::refcount_ptr_elem& _this)
{
    return FromObject(_this.get());
}

LogicCode::LogicUserObject* LogicCode::LogicUserObject::FromObject(Object::refcount_ptr_elem&& _this)
{
    return FromObject(_this.get());
}
