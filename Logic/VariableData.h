#pragma once
#include <unordered_map>
#include <Light.h>
#include "Stack.h"
#include "refcount_ptr.h"

struct FunctionData;
struct VariableData
{

	enum class VarType
	{
		None,
		Const,
		Var,
		Function
	};
	VariableData* parent;
	std::unordered_map<std::string, std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic>> vars;
	std::unordered_map<std::string, std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic>> consts;
	std::unordered_map<std::string, std::refcount_ptr<FunctionData, FunctionData>> functions;
	std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic> ret;
	VariableData();
	~VariableData();

	std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic> GetValue(std::string& str);
	std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic> GetValue(std::string&& str);

	std::refcount_ptr<FunctionData, FunctionData> GetFunction(std::string& str);
	std::refcount_ptr<FunctionData, FunctionData> GetFunction(std::string&& str);


	void SetFunction(std::string&& str, std::refcount_ptr<FunctionData, FunctionData>&& value);
	void SetFunction(std::string&& str, std::refcount_ptr<FunctionData, FunctionData>& value);
	void SetFunction(std::string& str, std::refcount_ptr<FunctionData, FunctionData>&& value);
	void SetFunction(std::string& str, std::refcount_ptr<FunctionData, FunctionData>& value);

	bool Exists(std::string& str);
	bool Exists(std::string&& str);

	VarType GetTypeVariable(std::string& str);
	VarType GetTypeVariable(std::string&& str);

	void SetConst(std::string& str, std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic>&& v);
	void SetConst(std::string& str, std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic>& v);
	void SetConst(std::string&& str, std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic>&& v);
	void SetConst(std::string&& str, std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic>& v);


	void SetVar(std::string& str, std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic>&& v);
	void SetVar(std::string& str, std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic>& v);
	void SetVar(std::string&& str, std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic>&& v);
	void SetVar(std::string&& str, std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic>& v);

	void SetRet(std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic>&& v);
	void SetRet(std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic>& v);

};
struct LogicCodeState
{
	VariableData vd;
	bool ret;
	StackBitset stack;
	
};
struct FunctionData
{

	enum class FunctionType
	{
		None,
		Runtime,
		Native
	};
	typedef void(*Fun)(FunctionData* __this, LogicCodeState* state);
	struct FunctionRuntime
	{
		std::vector<std::string> argsname;
		Light::Instruction* body;
	};
	struct FunctionNative
	{
		Fun callback;
	};

	LogicCodeState* state;
	FunctionType type;
	inline FunctionRuntime& get_runtimefn()
	{
		return *(FunctionRuntime*)(this + 1);
	}
	inline FunctionNative& get_nativefn()
	{
		return *(FunctionNative*)(this + 1);
	}
	FunctionData()
	{
		state = NULL;
		type = FunctionType::None;
	}
	using refcount_elem = std::RefCount<FunctionData>;
	using refcount_ptr_elem = std::refcount_ptr<FunctionData, FunctionData>;
	static refcount_elem* New(LogicCodeState* state, FunctionNative&& native)
	{
		auto refcount = std::malloc_t<refcount_elem>(sizeof(refcount_elem) +sizeof(FunctionNative));
		refcount->count = 0;
		refcount->obj.type = FunctionType::Native;
		refcount->obj.state = state;
		refcount->obj.get_nativefn() = native;
		return refcount;
	}
	static refcount_elem* New(LogicCodeState* state, FunctionRuntime&& runtime)
	{
		auto refcount = std::malloc_t<refcount_elem>(sizeof(refcount_elem) + sizeof(FunctionRuntime));
		refcount->count = 0;
		refcount->obj.type = FunctionType::Native;
		refcount->obj.state = state;
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


