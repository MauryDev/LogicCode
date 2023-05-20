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
	std::refcount_ptr<VariableData> parent;
	std::unordered_map<std::string, std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic>> vars;
	std::unordered_map<std::string, std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic>> consts;
	std::unordered_map<std::string, std::refcount_ptr<FunctionData, FunctionData>> functions;
	std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic> ret;
	VariableData();
	~VariableData();

	std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic> GetValue(std::string& str);
	std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic> GetValue(std::string&& str);

	std::refcount_ptr<FunctionData, FunctionData> GetFunction(std::string& str,bool findfromparent = true);
	std::refcount_ptr<FunctionData, FunctionData> GetFunction(std::string&& str, bool findfromparent = true);


	void SetFunction(std::string&& str, std::refcount_ptr<FunctionData, FunctionData>&& value);
	void SetFunction(std::string&& str, std::refcount_ptr<FunctionData, FunctionData>& value);
	void SetFunction(std::string& str, std::refcount_ptr<FunctionData, FunctionData>&& value);
	void SetFunction(std::string& str, std::refcount_ptr<FunctionData, FunctionData>& value);

	bool Exists(std::string& str, bool checkparent = true);
	bool Exists(std::string&& str, bool checkparent = true);

	VarType GetTypeVariable(std::string& str, bool checkparent = true);
	VarType GetTypeVariable(std::string&& str, bool checkparent = true);

	void SetConst(std::string& str, std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic>&& v, bool checkparent = true);
	void SetConst(std::string& str, std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic>& v, bool checkparent = true);
	void SetConst(std::string&& str, std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic>&& v, bool checkparent = true);
	void SetConst(std::string&& str, std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic>& v, bool checkparent = true);

	void SetVar(std::string& str, std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic>&& v, bool checkparent = true);
	void SetVar(std::string& str, std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic>& v, bool checkparent = true);
	void SetVar(std::string&& str, std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic>&& v, bool checkparent = true);
	void SetVar(std::string&& str, std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic>& v, bool checkparent = true);

	void SetRet(std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic>&& v);
	void SetRet(std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic>& v);

};
struct LogicCodeState
{
	std::refcount_ptr<VariableData> scope;
	bool ret;
	StackBitset stack;
	const char* error;
	LogicCodeState();
	bool CanRun();
	bool IsError();
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

	std::refcount_ptr<VariableData> parentscope;
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


