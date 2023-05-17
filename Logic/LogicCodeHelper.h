#pragma once
#include "VariableData.h"
#include <memory>
#include "refcount_ptr.h"
namespace LogicCode::Helper
{
	
	std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic> ToBitSet(LogicCodeState* state,Light::CommandResult& command);
	std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic> GetValue(LogicCodeState* state,Light::List& current);
	std::refcount_ptr<LogicCodeState> IntrepreterLogic(Light::Expression& token);
	void ExecuteExpression(LogicCodeState* state,Light::Expression& expression);
	 
};

