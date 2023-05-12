#pragma once
#include "VariableData.h"
namespace LogicCode::Helper
{
	
	const char* ToStr(bool v);
	const char* ToStr2(bool v);

	bool ToBool(Light::CommandResult& command, VariableData& vars, bool& ret);
	bool GetValue(Light::List& current, VariableData& vars, bool& ret);
	VariableData IntrepreterLogic(Light::Expression& token);
	void ExecuteExpression(Light::Expression& expression, VariableData& vars, bool& ret);
};

