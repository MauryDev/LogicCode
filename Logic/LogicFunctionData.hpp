#ifndef Logic_LogicFunctionData_H
#define Logic_LogicFunctionData_H
struct VariableData;

#include "LogicState.hpp"

struct FunctionData
{

	enum class FunctionType
	{
		None,
		Runtime,
		Native
	};
	typedef int(*Fun)(FunctionData* __this, LogicCodeState* state);
	struct FunctionRuntime
	{
		std::vector<std::string> argsname;
		Light::Instruction* body;
	};
	struct FunctionNative
	{
		Fun callback;
	};

	std::refcount_ptr<VariableData> parentscope;
	FunctionType type;
	FunctionRuntime& get_runtimefn()
	{
		return *(FunctionRuntime*)(this + 1);
	}
	FunctionNative& get_nativefn()
	{
		return *(FunctionNative*)(this + 1);
	}
	FunctionData()
	{
		parentscope = {};
		type = FunctionType::None;
	}
	using refcount_elem = std::RefCount<FunctionData>;
	using refcount_ptr_elem = std::refcount_ptr<FunctionData, FunctionData>;

	static refcount_elem* New(LogicCodeState* state, FunctionNative&& native)
	{
		auto refcountlen = sizeof(refcount_elem) + sizeof(FunctionNative);
		auto refcount = std::malloc_t<refcount_elem>(refcountlen);
		memset(refcount, 0, refcountlen);

		refcount->count = 0;
		refcount->obj.type = FunctionType::Native;
		refcount->obj.parentscope = state->scope;

		refcount->obj.get_nativefn() = native;
		return refcount;
	}
	static refcount_elem* New(LogicCodeState* state, FunctionRuntime&& runtime)
	{
		auto refcountlen = sizeof(refcount_elem) + sizeof(FunctionRuntime);

		auto refcount = std::malloc_t<refcount_elem>(refcountlen);
		memset(refcount, 0, refcountlen);

		refcount->count = 0;
		refcount->obj.type = FunctionType::Runtime;
		refcount->obj.parentscope = state->scope;
		memset(&refcount->obj.get_runtimefn(), 0, sizeof(FunctionRuntime));
		refcount->obj.get_runtimefn() = runtime;
		return refcount;
	}
	static void Free(refcount_elem* __this)
	{
		if (__this->obj.type == FunctionType::Runtime)
		{
			__this->obj.get_runtimefn().argsname.~vector();
		}
		free(__this);
	}
	static refcount_ptr_elem Make(LogicCodeState* state, FunctionRuntime&& runtime)
	{
		return refcount_ptr_elem::make<LogicCodeState*, FunctionRuntime&&>(state, std::forward<FunctionRuntime&&>(runtime));
	}
	static refcount_ptr_elem Make(LogicCodeState* state, FunctionNative&& native)
	{
		return refcount_ptr_elem::make<LogicCodeState*, FunctionNative&&>(state, std::forward<FunctionNative&&>(native));
	}
};


#endif