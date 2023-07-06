#pragma once
#include "VariableData.hpp"
#include <memory>
#include "refcount_ptr.hpp"
#include "LogicObject.hpp"
#include "LogicState.hpp"

namespace LogicCode::Helper
{
	
	LogicCode::Object::refcount_ptr_elem ToBitSetFromCommand(LogicCodeState* state,Light::CommandResult& command);
	int PushCommand(LogicCodeState* state, Light::CommandResult& command);

	LogicCode::Object::refcount_ptr_elem ToBitSetFromList(LogicCodeState* state,Light::List& current);
	
	LogicCode::ObjectView<std::bitsetdynamic> ToBitSet(LogicCodeState* state);
	int PushList(LogicCodeState* state, Light::List& current);

	
	std::refcount_ptr<LogicCodeState> IntrepreterLogic(Light::Instruction& token);
	int ExecuteInstruction(LogicCodeState* state,Light::Instruction& instruction);
	int ExecuteInstuctionShared(LogicCodeState* state, Light::Instruction& instruction);

};

