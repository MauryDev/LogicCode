#ifndef Logic_LogicObjectView_HPP
#define Logic_LogicObjectView_HPP

#include "LogicObject.hpp"
namespace LogicCode
{
	template<typename T>
	struct ObjectView
	{
		Object::refcount_ptr_elem v;
		T* operator->() {
			return v->ptr<T>();
		}
		T& operator*() {
			return v->data<T>();
		}
		operator Object::refcount_ptr_elem&()
		{
			return v;
		}
		/*operator Object::refcount_ptr_elem& ()
		{
			return v;
		}*/
	};
}

#endif