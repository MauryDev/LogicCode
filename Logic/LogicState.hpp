#ifndef Logic_LogicState_H
#define Logic_LogicState_H
#include "VariableData.hpp"
#include "StackObject.h"
struct LogicCodeState
{
	std::refcount_ptr<VariableData> scope;
	bool ret;
	StackObject stack;
	const char* error;
	LogicCodeState()
	{
		scope = std::refcount_ptr<VariableData>::make();
		ret = false;
		error = NULL;
	}
	bool CanRun()
	{
		return error == nullptr && !ret;
	}
	bool IsError()
	{
		return error != NULL;
	}
};


#endif