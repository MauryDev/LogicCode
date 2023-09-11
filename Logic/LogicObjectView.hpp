#ifndef Logic_LogicObjectView_HPP
#define Logic_LogicObjectView_HPP

#include "LogicObject.hpp"



namespace LogicCode
{
    template<typename T>
    struct ObjectView : Object::refcount_ptr_elem
    {
        T* operator->() {
            auto obj = this->get();
            if (obj != NULL)
            {
                return obj->ptr<T>();
            }
            return NULL;
        }
        T& operator*() {

            return get()->data<T>();
        }
        ObjectType get_type()
        {
            return get()->type;
        }
        void set_type(ObjectType newvalue)
        {
            get()->type = newvalue;
        }
        T* ToPtr()
        {
            auto obj = this->get();
            if (obj != NULL)
            {
                return obj->ptr<T>();
            }
            return NULL;
        }
    };
}

#endif