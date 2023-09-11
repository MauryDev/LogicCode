#ifndef Logic_LogicFunctionObject_HPP
#define Logic_LogicFunctionObject_HPP
#include "refcount_ptr.hpp"
#include "LogicObject.hpp"
#include "LogicFunctionData.hpp"
namespace LogicCode
{
	struct LogicFunctionObject: FunctionData
	{

		
		static LogicFunctionObject* FromObject(LogicCode::Object& _this) {
            return FromObject(&_this);
        }
		static LogicFunctionObject* FromObject(LogicCode::Object* _this) {
            return (_this != nullptr && _this->type == ObjectType::Function ? _this->ptr<LogicFunctionObject>() : nullptr);

		}
		static LogicFunctionObject* FromObject(Object::refcount_ptr_elem& _this) {
			return FromObject(_this.get());
		}
		static LogicFunctionObject* FromObject(Object::refcount_ptr_elem&& _this) {
			return FromObject(_this.get());
		}
		static size_t GetMemorySize(FunctionData::FunctionType functiontype)
		{
			if (functiontype == FunctionData::FunctionType::Native)
			{
				return sizeof(FunctionData) + sizeof(FunctionData::FunctionNative);
			}
			if (functiontype == FunctionData::FunctionType::Runtime)
			{
				return sizeof(FunctionData) + sizeof(FunctionData::FunctionRuntime);
			}
			return 0;
		}
		void Free()
		{
			FunctionData::Free(this);
		}
	};
}
#endif