#ifndef Logic_LogicObject_HPP
#define Logic_LogicObject_HPP
#include <cinttypes>
#include "refcount_ptr.hpp"
#include "bitsetdynamic.hpp"
#include "LogicStructs.hpp"
#include "LogicString.hpp"
namespace LogicCode
{

	struct Object 
	{
		using refcount_elem = std::RefCount<LogicCode::Object>;
		using refcount_ptr_elem = std::refcount_ptr<Object, Object>;
		ObjectType type;	

		Object()
		{
			this->type = ObjectType::None;
		}

		template <typename T>
		T& data()
		{
			return *(T*)(this + 1);
		}
		template <typename T>
		T* ptr()
		{
			return (T*)(this + 1);
		}

		static refcount_elem* New()
		{
			auto lenmalloc = sizeof(refcount_elem);
			auto ret = std::malloc_t<refcount_elem>(lenmalloc);
			ret->count = 0;
			ret->obj.type = ObjectType::None;

			return ret;
		}

		static refcount_elem* New(size_t len)
		{
			auto lenmalloc = sizeof(refcount_elem) + len;
			auto ret = std::malloc_t<refcount_elem>(lenmalloc);
			ret->count = 0;
			ret->obj.type = ObjectType::None;

			return ret;
		}
		
		
		bool CheckType(ObjectType type)
		{
			return this->type == type;
		}
		bool IsNone()
		{
			return type == ObjectType::None;
		}

		std::bitsetdynamic* GetBitset()
		{
			return (CheckType(ObjectType::Bitset) ? ptr<std::bitsetdynamic>() : nullptr);
		}
		LogicNumber GetNumber()
		{
			if (type == ObjectType::Number)
			{
				return data<LogicNumber>();
			}
			if (type == ObjectType::Integer)
			{
				return (LogicNumber)data<LogicInteger>();
			}
			return 0;
		}
		LogicInteger GetInteger()
		{
			if (type == ObjectType::Number)
			{
				return (LogicInteger)data<LogicNumber>();
			}
			if (type == ObjectType::Integer)
			{
				return data<LogicInteger>();
			}
			return 0;
		}
		LogicString* GetString()
		{
			return (type == ObjectType::String ? ptr<LogicString>() : nullptr);
		}
		

		static void Free(refcount_elem* _this)
		{
			if (_this != NULL)
			{
				//auto vtype = _this->obj.type;
				free(_this);
			}
		}
		
	};
}

#endif

