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
	
	static void Free(FunctionData* fdata)
	{
		if (fdata->type == FunctionType::Runtime)
		{
			fdata->get_runtimefn().argsname.~vector();
		}
	}

	
};


#endif