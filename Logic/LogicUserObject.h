#pragma once
#include "LogicObject.hpp"
namespace LogicCode
{
    struct LogicUserObject;
    struct LogicUserClass
    {
        typedef void(*__GC)(LogicUserObject* __this);
        __GC __gc;

    };
    struct LogicUserObject
    {
        LogicUserClass* klass;

        static size_t GetMemorySize(size_t len);
        template<typename T>
        T& obj()
        {
            return *(T*)(this + 1);
        }
        template<typename T>
        T* ptr()
        {
            return (T*)(this + 1);
        }
        static LogicUserObject* FromObject(LogicCode::Object& _this);
        static LogicUserObject* FromObject(LogicCode::Object* _this);
        static LogicUserObject* FromObject(Object::refcount_ptr_elem& _this);
        static LogicUserObject* FromObject(Object::refcount_ptr_elem&& _this);
    };
    template <typename T>
    struct TLogicUserObject : LogicUserObject
    {
        static size_t GetMemorySize()
        {
            return sizeof(LogicUserObject) + sizeof(T);
        }
        T& obj()
        {
            return *(T*)(this + 1);
        }
        T* ptr()
        {
            return (T*)(this + 1);
        }

    };


}

