#include "LogicCodeHelper.h"
#include "LogicCodeSTD.h"
#include <iostream>
#include <memory>

std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic> LogicCode::Helper::ToBitSet(LogicCodeState* state, Light::CommandResult& command)
{

	if (!state->CanRun())
	{
		return {};
	}
	if (command.resultType == Light::ResultType::Number)
	{
		auto number = command.str;
		auto numberlen = number->size();
		auto v = std::bitsetdynamic::Make(numberlen);
		int ir = numberlen - 1;
		for (size_t i = 0; i < numberlen; i++)
		{
			v->set(ir, number->at(i) != '0');
			ir--;
		}
		return v;
	}
	else if (command.resultType == Light::ResultType::Label)
	{
		auto str = command.str;

		if (str->Equals("true") || str->Equals("TRUE"))
		{
			return std::bitsetdynamic::Make(true);
		}
		else if (str->Equals("false") || str->Equals("FALSE"))
		{
			return std::bitsetdynamic::Make(false);
		}
		else
		{
			return state->vd.GetValue(str->data());
		}
	}
	else if (command.resultType == Light::ResultType::Expression)
	{
		auto& exp = command.expression;
		if (exp->get_Count() == 1)
		{
			auto arg = GetValue(state, exp->at(0));
			if (!state->CanRun())
			{
				if (!state->IsError())
				{
					state->error = "Don't use return in expression";
				}
				return {};
			}
			return arg;
		}
	}
	else if (command.resultType == Light::ResultType::Instruction)
	{
		ExecuteInstuctionShared(state, *command.instruction);

		return {};
	}
	return {};
}


std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic> LogicCode::Helper::GetValue(LogicCodeState* state, Light::List& current)
{
	if (!state->CanRun())
	{
		return {};
	}
	auto instructionsize = current.get_Count();
	auto& statestack = state->stack;
	auto& statevd = state->vd;
	if (instructionsize > 0)
	{
		auto typeexpr = current[0];

		if (typeexpr.resultType == Light::ResultType::Label)
		{
			auto& currentopcode = typeexpr.str;
			if (currentopcode->Equals("if"))
			{
				Std::If(state, current);
			}
			else if (currentopcode->Equals("while"))
			{
				Std::While(state, current);

			}
			else if (currentopcode->Equals("fun"))
			{
				Std::Fun(state, current);
			}
			else if (currentopcode->Equals("return"))
			{
				Std::Return(state, current);
			}

			else if (currentopcode->Equals("const"))
			{
				Std::Const(state, current);
			}
			else if (currentopcode->Equals("var"))
			{
				Std::Var(state, current);
			}
			else if (currentopcode->Equals("case"))
			{
				Std::Case(state, current);
			}
			else if (currentopcode->Equals("i8"))
			{
				return Std::i8(state, current);
			}
			else if (currentopcode->Equals("ref"))
			{
				return Std::Ref(state, current);
			}
			else
			{
				if (instructionsize >= 3)
				{
					auto type = current[1];

					if (type.resultType == Light::ResultType::Operador)
					{
						if (*type.coperator == Light::COperator::Set)
						{
							auto lenargs = instructionsize - 2;
							Light::List values(lenargs,lenargs, &current.at(2));
							
							auto v2 = GetValue(state, values);
							if (!state->CanRun())
							{
								if (!state->IsError())
								{
									state->error = "Don't use return in expression";
								}
								return {};
							}
							statevd.SetVar(currentopcode->data(), v2);

						}
					}
				}
				else if (instructionsize == 2)
				{
					auto type = current[1];
					if (type.resultType == Light::ResultType::Expression)
					{
						auto expression = type.expression;
						auto getfn = statevd.GetFunction(currentopcode->data());

						if (getfn->type != FunctionData::FunctionType::None)
						{


							if (getfn->type == FunctionData::FunctionType::Runtime)
							{
								auto parent = getfn->state;

								LogicCodeState currentstate;
								currentstate.ret = false;
								currentstate.vd.parent = &parent->vd;
								VariableData& vd = currentstate.vd;

								auto& args = getfn->get_runtimefn().argsname;
								auto expressionlen = args.size();

								for (size_t i = 0; i < expressionlen; i++)
								{
									auto arg = GetValue(state, expression->at(i));
									if (!state->CanRun())
									{
										if (!state->IsError())
										{
											state->error = "Don't use return in expression";
										}
										return {};
									}
									vd.SetConst(args[i], arg,false);
								}
								ExecuteInstruction(&currentstate, *getfn->get_runtimefn().body);
								return currentstate.vd.ret;
							}
							else if (getfn->type == FunctionData::FunctionType::Native)
							{
								auto expressionlen = expression->get_Count();
								auto oldoffset = statestack.get_Offset();
								statestack.set_Offset(statestack.size());
								for (size_t i = 0; i < expressionlen; i++)
								{
									auto arg = GetValue(state, expression->at(i));
									if (!state->CanRun())
									{
										if (!state->IsError())
										{
											state->error = "Don't use return in expression";
										}
										return {};
									}
									statestack.push(GetValue(state, expression->at(i)));
								}
								getfn->get_nativefn().callback(getfn.get(), state);
								auto toremove = statestack.sizeoffset();
								for (size_t i = 0; i < toremove; i++)
								{
									state->stack.pop();
								}
								statestack.set_Offset(oldoffset);

								return statevd.ret;
							}
						}
					}
				}
			}


			
		}
		if (instructionsize == 1)
		{
			return ToBitSet(state, current[0]);
		}

	}
	return {};

}

std::refcount_ptr<LogicCodeState> LogicCode::Helper::IntrepreterLogic(Light::Instruction& token)
{
	auto state = std::refcount_ptr<LogicCodeState>::make();
	
	
	Std::__Init(state.get());

	ExecuteInstruction(state.get(), token);
	return state;
}

void LogicCode::Helper::ExecuteInstruction(LogicCodeState* state, Light::Instruction& instruction)
{
	if (!state->CanRun())
	{
		return;
	}

	auto count = instruction.get_Count();

	for (size_t i = 0; i < count; i++)
	{
		if (!state->CanRun())
		{
			if (!state->IsError())
			{
				std::cout << state->error << std::endl;
			}
			break;
		}
		auto& current = instruction[i];

		auto oldoffset = state->stack.get_Offset();
		state->stack.set_Offset(state->stack.size());

		GetValue(state, current);

		auto toremove = state->stack.sizeoffset();
		for (size_t i = 0; i < toremove; i++)
		{
			state->stack.pop();
		}
		state->stack.set_Offset(oldoffset);
	}
}

void LogicCode::Helper::ExecuteInstuctionShared(LogicCodeState* state, Light::Instruction& instruction)
{
	if (!state->CanRun())
	{
		return;
	}

	LogicCodeState currentstate;
	currentstate.ret = false;
	currentstate.vd.parent = &state->vd;
	VariableData& vd = currentstate.vd;

	vd.ret = state->vd.ret;
	ExecuteInstruction(&currentstate, instruction);

	state->vd.ret = vd.ret;
	state->ret = currentstate.ret;
	state->error = currentstate.error;
}
