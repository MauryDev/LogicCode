#pragma once
#include "VariableData.h"
#include <memory>
#include "refcount_ptr.h"
namespace LogicCode::Helper
{
	
	std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic> ToBitSet(LogicCodeState* state,Light::CommandResult& command);
	std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic> GetValue(LogicCodeState* state,Light::List& current);
	std::refcount_ptr<LogicCodeState> IntrepreterLogic(Light::Instruction& token);
	void ExecuteInstruction(LogicCodeState* state,Light::Instruction& instruction);
	void ExecuteInstuctionShared(LogicCodeState* state, Light::Instruction& instruction);

};

