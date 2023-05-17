#include "LogicCodeHelper.h"
#include "LogicCodeSTD.h"
#include <iostream>
#include <memory>

std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic> LogicCode::Helper::ToBitSet(LogicCodeState* state, Light::CommandResult& command)
{
	if (command.resultType == Light::ResultType::Number)
	{
		auto number = command.str;
		auto numberlen = number->size();
		auto v = std::bitsetdynamic::Make(numberlen);
		for (size_t i = 0; i < numberlen; i++)
		{
			v->set(i, number->at(i) != '0');
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
			return GetValue(state, exp->at(0));
		}
	}
	return {};
}


std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic> LogicCode::Helper::GetValue(LogicCodeState* state, Light::List& current)
{
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
							Light::List values(instructionsize - 2, &current.at(2));
							for (size_t i = 2; i < instructionsize; i++)
							{
								values.Add(current[i]);
							}
							auto v2 = GetValue(state, values);
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
								VariableData vd;

								LogicCodeState currentstate;
								currentstate.ret = false;
								currentstate.vd.parent = &parent->vd;

								auto& args = getfn->get_runtimefn().argsname;
								auto expressionlen = args.size();

								for (size_t i = 0; i < expressionlen; i++)
								{
									vd.SetConst(args[i], GetValue(state, expression->at(i)));
								}
								ExecuteExpression(&currentstate, *getfn->get_runtimefn().body);
								return  currentstate.vd.ret;
							}
							else if (getfn->type == FunctionData::FunctionType::Native)
							{
								auto expressionlen = expression->get_Count();
								auto oldoffset = statestack.get_Offset();
								statestack.set_Offset(statestack.size());
								for (size_t i = 0; i < expressionlen; i++)
								{

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

std::refcount_ptr<LogicCodeState> LogicCode::Helper::IntrepreterLogic(Light::Expression& token)
{
	auto state = std::refcount_ptr<LogicCodeState>::make();
	
	state->vd.parent = NULL;
	state->ret = false;
	Std::__Init(state.get());

	ExecuteExpression(state.get(), token);
	return state;
}

void LogicCode::Helper::ExecuteExpression(LogicCodeState* state, Light::Expression& expression)
{
	auto count = expression.get_Count();

	for (size_t i = 0; i < count; i++)
	{
		if (state->ret)
		{
			break;
		}
		auto& current = expression[i];

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
