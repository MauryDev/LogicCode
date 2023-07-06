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
		static LogicRefBitset* FromObject(LogicCode::Object& _this) {
			return (_this.type == ObjectType::RefBitset ? _this.ptr<LogicRefBitset>() : nullptr);
		}
		static LogicRefBitset* FromObject(LogicCode::Object* _this) {
			return FromObject(*_this);
		}
	};
}
#endif