#include "LogicCodeHelper.h"
#include "LogicCodeSTD.h"
#include <iostream>
#include <memory>
#include "LogicObjectHelper.hpp"
#include "LogicFunctionData.hpp"
LogicCode::Object::refcount_ptr_elem LogicCode::Helper::ToBitSetFromCommand(LogicCodeState* state, Light::CommandResult& command)
{

	if (!state->CanRun())
	{
		return {};
	}
	auto v = PushCommand(state, command);
	if (v > 0)
	{

		auto toremove = v;
		auto valueindex = state->stack.sizeoffset() - v;
		auto ret = state->stack.get(valueindex);
		for (size_t i = 0; i < toremove; i++)
		{
			state->stack.pop();
		}
		return ret;
	}
	else
	{
		return {};
	}
}

int LogicCode::Helper::PushCommand(LogicCodeState* state, Light::CommandResult& command)
{
	if (!state->CanRun())
	{
		return 0;
	}
	if (command.resultType == Light::ResultType::Number)
	{
		auto number = command.str;
		auto numberlen = number->size();
		auto v = LogicCode::ObjectHelper::NewBitset(numberlen);
		int ir = numberlen - 1;
		for (size_t i = 0; i < numberlen; i++)
		{
			v->set(ir, number->at(i) != '0');
			ir--;
		}
		state->stack.push(v);
		return 1;
	}
	else if (command.resultType == Light::ResultType::Label)
	{
		auto str = command.str;

		if (str->Equals("true") || str->Equals("TRUE"))
		{
			auto bitset = ObjectHelper::NewBitset((size_t)1);
			bitset->set(0, true);
			state->stack.push(bitset);

			return 1;
		}
		else if (str->Equals("false") || str->Equals("FALSE"))
		{
			auto bitset = ObjectHelper::NewBitset((size_t)1);
			bitset->set(0, false);
			state->stack.push(bitset);
			return 1;
		}
		else
		{
			state->stack.push(state->scope->GetValue(str->data()));

			return 1;
		}
	}
	else if (command.resultType == Light::ResultType::String)
	{
		auto str = command.str;

		state->stack.push(ObjectHelper::NewString(str->data()));
	}
	else if (command.resultType == Light::ResultType::Expression)
	{
		auto& exp = command.expression;
		if (exp->get_Count() == 1)
		{
			auto len = PushList(state, exp->at(0));
			if (!state->CanRun())
			{
				if (!state->IsError())
				{
					state->error = "Don't use return in expression";
				}
				return 0;
			}
			return len;
		}
	}
	else if (command.resultType == Light::ResultType::Instruction)
	{
		auto len = ExecuteInstuctionShared(state, *command.instruction);

		return len;
	}
	return 0;
}


LogicCode::Object::refcount_ptr_elem LogicCode::Helper::ToBitSetFromList(LogicCodeState* state, Light::List& current)
{
	if (!state->CanRun())
	{
		return {};
	}
	auto v = PushList(state, current);
	if (v > 0)
	{
		auto toremove = v;
		auto valueindex = state->stack.sizeoffset() - toremove;
		auto ret = state->stack.get(valueindex);

		for (size_t i = 0; i < toremove; i++)
		{
			state->stack.pop();
		}
		return ret;
	}
	else
	{
		return {};
	}

}

LogicCode::ObjectView<std::bitsetdynamic> LogicCode::Helper::ToBitSet(LogicCodeState* state)
{
	if (!state->CanRun())
	{
		return {};
	}
	auto v = state->stack.sizeoffset();
	if (v > 0)
	{
		auto toremove = v;
		auto valueindex = state->stack.sizeoffset() - toremove;
		auto ret = state->stack.get(valueindex);

		for (size_t i = 0; i < toremove; i++)
		{
			state->stack.pop();
		}
		return { ret };
	}
	else
	{
		return {};
	}
}

int LogicCode::Helper::PushList(LogicCodeState* state, Light::List& current)
{
	if (!state->CanRun())
	{
		return {};
	}
	auto instructionsize = current.get_Count();
	auto& statestack = state->stack;
	auto& statevd = state->scope;
	if (instructionsize > 0)
	{
		auto typeexpr = current[0];

		if (typeexpr.resultType == Light::ResultType::Label)
		{
			auto& currentopcode = typeexpr.str;
			if (currentopcode->Equals("if"))
			{
				return Std::If(state, current);
			}
			else if (currentopcode->Equals("while"))
			{
				return Std::While(state, current);

			}
			else if (currentopcode->Equals("fun"))
			{
				return Std::Fun(state, current);
			}
			else if (currentopcode->Equals("return"))
			{
				return Std::Return(state, current);
			}

			else if (currentopcode->Equals("const"))
			{
				return Std::Const(state, current);
			}
			else if (currentopcode->Equals("var"))
			{
				return Std::Var(state, current);
			}
			else if (currentopcode->Equals("case"))
			{
				return Std::Case(state, current);
			}
			else if (currentopcode->Equals("int"))
			{
				return Std::Intv(state, current);
			}
			else if (currentopcode->Equals("num"))
			{
				return Std::Numv(state, current);
			}
			else if (currentopcode->Equals("ref"))
			{
				return Std::Ref(state, current);
			}
			else if (currentopcode->Equals("truthtable"))
			{
				return Std::TruthTable(state, current);
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
							Light::List values(lenargs, lenargs, &current.at(2));

							auto v2 = ToBitSetFromList(state, values);
							if (!state->CanRun())
							{
								if (!state->IsError())
								{
									state->error = "Don't use return in expression";
								}
								return {};
							}
							statevd->SetVar(currentopcode->data(), v2);
							return 0;
						}
					}
				}
				else if (instructionsize == 2)
				{
					auto type = current[1];
					if (type.resultType == Light::ResultType::Expression)
					{
						auto expression = type.expression;
						auto stack_obj = statevd->GetValue(currentopcode->data());
						auto getfn1 = LogicFunctionObject::FromObject(stack_obj);

						if (getfn1 != NULL)
						{

							auto getfn = getfn1->data();
							if (getfn->type == FunctionData::FunctionType::Runtime)
							{
								auto& parent = getfn->parentscope;

								auto oldscope = state->scope;

								auto newscope = std::refcount_ptr<VariableData>::make();
								newscope->parent = parent;

								auto& args = getfn->get_runtimefn().argsname;
								auto expressionlen = args.size();

								for (size_t i = 0; i < expressionlen; i++)
								{
									auto arg = ToBitSetFromList(state, expression->at(i));
									if (!state->CanRun())
									{

										if (!state->IsError())
										{
											state->error = "Don't use return in expression";
										}
										return 0;
									}
									newscope->SetConst(args[i], arg, false);
								}
								state->scope = newscope;

								auto len = ExecuteInstruction(state, *getfn->get_runtimefn().body);

								state->scope = oldscope;

								state->ret = false;
								return len;
							}
							else if (getfn->type == FunctionData::FunctionType::Native)
							{
								auto getfn = getfn1->data();

								auto expressionlen = expression->get_Count();
								auto oldoffset = statestack.get_Offset();
								statestack.set_Offset(statestack.size());
								for (size_t i = 0; i < expressionlen; i++)
								{
									PushList(state, expression->at(i));
									if (!state->CanRun())
									{
										if (!state->IsError())
										{
											state->error = "Don't use return in expression";
										}
										return 0;
									}
								}
								auto lenret = getfn->get_nativefn().callback(getfn, state);
								auto toremove = statestack.sizeoffset() - lenret;
								for (size_t i = 0; i < toremove; i++)
								{
									state->stack.remove(0);
								}
								statestack.set_Offset(oldoffset);

								return lenret;
							}
						}
					}
				}
			}



		}

		if (instructionsize == 1)
		{
			return PushCommand(state, current[0]);
		}

	}
	return 0;
}

std::refcount_ptr<LogicCodeState> LogicCode::Helper::IntrepreterLogic(Light::Instruction& token)
{
	auto state = std::refcount_ptr<LogicCodeState>::make();
	
	
	Std::__Init(state.get());

	ExecuteInstruction(state.get(), token);
	return state;
}

int LogicCode::Helper::ExecuteInstruction(LogicCodeState* state, Light::Instruction& instruction)
{
	if (!state->CanRun())
	{
		return 0;
	}
	int ret = 0;
	auto count = instruction.get_Count();

	for (size_t i = 0; i < count; i++)
	{
		
		auto& current = instruction[i];

		auto oldoffset = state->stack.get_Offset();
		state->stack.set_Offset(state->stack.size());

		auto lenstack = PushList(state, current);
		auto iserror = state->IsError();
		if (!state->CanRun()) {
			if (iserror)
			{
				auto toremove = state->stack.sizeoffset();
				for (size_t i = 0; i < toremove; i++)
				{
					state->stack.pop();
				}
				state->stack.set_Offset(oldoffset);
			}
			else
			{
				auto toremove = state->stack.sizeoffset() - lenstack;
				for (size_t i = 0; i < toremove; i++)
				{
					state->stack.pop();
				}
				state->stack.set_Offset(oldoffset);
				ret = lenstack;
			}
			break;
		}
		else
		{
			auto toremove = state->stack.sizeoffset();
			for (size_t i = 0; i < toremove; i++)
			{
				state->stack.pop();
			}
			state->stack.set_Offset(oldoffset);
		}
	}
	return ret;
}

int LogicCode::Helper::ExecuteInstuctionShared(LogicCodeState* state, Light::Instruction& instruction)
{
	if (!state->CanRun())
	{
		return 0;
	}
	auto oldscope = state->scope;
	auto newscope = std::refcount_ptr<VariableData>::make();
	newscope->parent = oldscope;
	state->scope = newscope;

	
	auto len = ExecuteInstruction(state, instruction);

	state->scope = oldscope;
	return len;
}
