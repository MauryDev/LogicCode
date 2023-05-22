#pragma once
#include "VariableData.h"
#include <memory>
#include "refcount_ptr.h"
namespace LogicCode::Helper
{
	
	std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic> ToBitSetFromCommand(LogicCodeState* state,Light::CommandResult& command);
	int PushCommand(LogicCodeState* state, Light::CommandResult& command);

	std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic> ToBitSetFromList(LogicCodeState* state,Light::List& current);
	
	std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic> ToBitSet(LogicCodeState* state);
	int PushList(LogicCodeState* state, Light::List& current);

	
	std::refcount_ptr<LogicCodeState> IntrepreterLogic(Light::Instruction& token);
	int ExecuteInstruction(LogicCodeState* state,Light::Instruction& instruction);
	int ExecuteInstuctionShared(LogicCodeState* state, Light::Instruction& instruction);

};

