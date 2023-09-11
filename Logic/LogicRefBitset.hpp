#ifndef Logic_LogicRefBitset_HPP
#define Logic_LogicRefBitset_HPP
#include "refcount_ptr.hpp"
#include "VariableData.hpp"
#include "LogicString.hpp"
#include "LogicObject.hpp"
namespace LogicCode
{
	struct LogicRefBitset
	{
		std::refcount_ptr<VariableData> scope;
		LogicString name;
		Object::refcount_ptr_elem GetValue()
		{
			return scope->GetValue(name.txt);
		}
		void SetValue(Object::refcount_ptr_elem& v,bool checkparent = false)
		{
			scope->SetVar(name.txt,v, checkparent);
		}
		static LogicRefBitset* FromObject(LogicCode::Object& _this) {
            return FromObject(&_this);
        }
		static LogicRefBitset* FromObject(LogicCode::Object* _this) {
            return (_this->type == ObjectType::RefBitset ? _this->ptr<LogicRefBitset>() : nullptr);
		}
		static LogicRefBitset* FromObject(Object::refcount_ptr_elem& _this) {
			return FromObject(_this.get());
		}
		static LogicRefBitset* FromObject(Object::refcount_ptr_elem&& _this) {
			return FromObject(_this.get());
		}
	};
}
#endif