#include "LogicCodeSTD.h"
#include "LogicCodeHelper.h"
#include <iostream>
#include <iomanip>
#include "refcount_ptr.hpp"
#include <cmath>
#include "LogicObjectHelper.hpp"
#include "LogicFunctionData.hpp"
int LogicCode::Std::And(FunctionData* __this, LogicCodeState* state)
{
	auto& stack = state->stack;
	auto& scope = state->scope;
	auto len = stack.sizeoffset();
	if (len > 0)
	{
		auto first = stack.get(0)->GetBitset();
		auto retv = ObjectHelper::NewBitset(first->size());
		auto sizeinput = retv->size();

		for (size_t i = 1; i < len; i++)
		{
			auto current = stack.get(i)->GetBitset();
			if (current->size() == sizeinput)
			{
				for (size_t i = 0; i < sizeinput; i++)
				{
					retv->set(i, first->get(i) && current->get(i));
				}
			}
			else
			{
				return 0;
			}
		}
		state->stack.push(retv);
		return 1;
	}
	return 0;
}

int LogicCode::Std::Or(FunctionData* __this, LogicCodeState* state)
{
	auto& stack = state->stack;
	auto& scope = state->scope;
	auto len = stack.sizeoffset();
	if (len > 0)
	{
		auto first = stack.get(0)->GetBitset();
		auto firstparam = ObjectHelper::NewBitset(first->size());
		auto sizeinput = firstparam->size();

		for (size_t i = 1; i < len; i++)
		{
			auto current = stack.get(i)->GetBitset();
			if (current->size() == sizeinput)
			{
				for (size_t i = 0; i < sizeinput; i++)
				{
					firstparam->set(i, first->get(i) || current->get(i));
				}
			}
			else
			{
				return 0;
			}
		}
		stack.push(firstparam);
		return 1;

	}
	return 0;

}


int LogicCode::Std::Not(FunctionData* __this, LogicCodeState* state)
{
	auto& stack = state->stack;
	auto& scope = state->scope;
	auto len = stack.sizeoffset();
	if (len == 1)
	{

		auto first = stack.get(0)->GetBitset();
		auto retv = ObjectHelper::NewBitset(first->size());

		auto sizeinput = retv->size();

		for (size_t i = 0; i < sizeinput; i++)
		{
			retv->set(i, !first->get(i));
		}
		stack.push(retv);
		return 1;

	}
	return 0;
}

int LogicCode::Std::Xor(FunctionData* __this, LogicCodeState* state)
{
	auto& stack = state->stack;
	auto& scope = state->scope;
	auto len = stack.sizeoffset();
	if (len > 0)
	{
		auto first = stack.get(0)->GetBitset();
		auto firstparam = ObjectHelper::NewBitset(first->size());

		auto sizeinput = firstparam->size();

		for (size_t i = 1; i < len; i++)
		{
			auto current = stack.get(i)->GetBitset();
			if (current->size() == sizeinput)
			{
				for (size_t i = 0; i < sizeinput; i++)
				{
					firstparam->set(i, first->get(i) ^ current->get(i));
				}
			}
			else
			{
				return 0;
			}
		}
		stack.push(firstparam);
		return 1;

	}
	return 0;
}

int LogicCode::Std::Nand(FunctionData* __this, LogicCodeState* state)
{
	auto& stack = state->stack;
	auto& scope = state->scope;
	auto len = stack.sizeoffset();
	if (len > 0)
	{
		auto first = stack.get(0)->GetBitset();
		auto firstparam = ObjectHelper::NewBitset(first->size());

		auto sizeinput = firstparam->size();

		for (size_t i = 1; i < len; i++)
		{
			auto current = stack.get(i)->GetBitset();
			if (current->size() == sizeinput)
			{
				for (size_t i = 0; i < sizeinput; i++)
				{
					firstparam->set(i, first->get(i) && current->get(i));
				}
			}
			else
			{
				return 0;
			}
		}
		for (size_t i = 0; i < sizeinput; i++)
		{
			firstparam->set(i, !firstparam->get(i));
		}
		stack.push(firstparam);
		return 1;


	}
	return 0;
}

int LogicCode::Std::Nor(FunctionData* __this, LogicCodeState* state)
{
	auto& stack = state->stack;
	auto& scope = state->scope;
	auto len = stack.sizeoffset();
	if (len > 0)
	{

		auto first = stack.getasview<std::bitsetdynamic>(0);
		auto firstparam = ObjectHelper::NewBitset(first->size());

		auto sizeinput = firstparam->size();

		for (size_t i = 1; i < len; i++)
		{
			auto current = stack.getasview<std::bitsetdynamic>(i);
			if (current->size() == sizeinput)
			{
				for (size_t i = 0; i < sizeinput; i++)
				{
					firstparam->set(i, first->get(i) || current->get(i));
				}
			}
			else
			{
				return 0;
			}
		}
		for (size_t i = 0; i < sizeinput; i++)
		{
			firstparam->set(i, !firstparam->get(i));
		}
		stack.push(firstparam);
		return 1;


	}
	return 0;
}

int LogicCode::Std::Xnor(FunctionData* __this, LogicCodeState* state)
{
	auto& stack = state->stack;
	auto& scope = state->scope;
	auto len = stack.sizeoffset();
	if (len > 0)
	{

		auto first = stack.getasview<std::bitsetdynamic>(0);
		auto firstparam = ObjectHelper::NewBitset(first->size());

		auto sizeinput = firstparam->size();

		for (size_t i = 1; i < len; i++)
		{
			auto current = stack.getasview<std::bitsetdynamic>(i);
			if (current->size() == sizeinput)
			{
				for (size_t i = 0; i < sizeinput; i++)
				{
					firstparam->set(i, first->get(i) ^ current->get(i));
				}
			}
			else
			{
				return 0;
			}
		}
		for (size_t i = 0; i < sizeinput; i++)
		{
			firstparam->set(i, !firstparam->get(i));
		}
		stack.push(firstparam);
		return 1;


	}
	return 0;
}

int LogicCode::Std::If(LogicCodeState* state, Light::List& current)
{
	auto instructionsize = current.get_Count();

	if (instructionsize == 3)
	{

		auto arg1 = Helper::ToBitSetFromCommand(state, current[1]);
		auto arg1bitset = arg1->GetBitset();
		if (!state->CanRun())
		{
			if (!state->IsError())
			{
				return _Error(state, "Don't use return in 'if'");
			}
			else {
				return 0;
			}
		}
		if (!arg1 || arg1bitset->size() == 0)
		{
			return _Error(state, "NULL Value or size == 0");
		}
		auto condition = arg1bitset->get(0);

		auto exp = current[2].expression;
		if (condition)
		{
			return Helper::ExecuteInstuctionShared(state, *exp);
		}


	}
	else if (instructionsize == 5)
	{


		auto arg1 = Helper::ToBitSetFromCommand(state, current[1]);
		auto arg1bitset = arg1->GetBitset();
		if (!state->CanRun())
		{
			if (!state->IsError())
			{
				return _Error(state, "Don't use return in 'if'");
			}
			else
			{
				return 0;
			}
		}
		if (!arg1 || arg1bitset->size() == 0)
		{
			return _Error(state, "NULL Value or size == 0");
		}

		auto exp = current[2].instruction;
		auto _else = current[3].str;
		auto exp2 = current[4].instruction;
		if (_else->Equals("else"))
		{
			auto condition = arg1bitset->get(0);
			if (condition)
			{
				return Helper::ExecuteInstuctionShared(state, *exp);
			}
			else
			{
				return Helper::ExecuteInstuctionShared(state, *exp2);

			}
		}
		else
		{
			return _Error(state, "Expected 'else'");
		}

	}
	else
	{
		return _Error(state, "Syntax error: arguments don't match");
	}
}

int LogicCode::Std::While(LogicCodeState* state, Light::List& current)
{
	auto instructionsize = current.get_Count();

	if (instructionsize == 3)
	{
		auto arg1 = Helper::ToBitSetFromCommand(state, current[1]);
		auto arg1bitset = arg1->GetBitset();
		if (!state->CanRun())
		{
			if (!state->IsError())
			{
				_Error(state, "Don't use return in 'while'");
			}
			else
			{
				return 0;
			}
		}
		if (!arg1 || arg1bitset->size() == 0)
		{
			return _Error(state, "NULL Value or size == 0");
		}
		auto exp = current[2].instruction;

		auto condition = arg1bitset->get(0);
		int len = 0;
		while (condition)
		{
			len = Helper::ExecuteInstuctionShared(state, *exp);
			if (state->ret)
			{
				return len;
			}
			arg1 = Helper::ToBitSetFromCommand(state, current[1]);
			arg1bitset = arg1->GetBitset();
			if (!arg1|| arg1bitset->size() == 0)
			{
				return _Error(state, "NULL Value or size == 0");
			}
			condition = arg1bitset->get(0);

		}
		return 0;
	}

	else
	{
		return _Error(state, "Syntax error: arguments don't match");
	}
}

int LogicCode::Std::Fun(LogicCodeState* state, Light::List& current)
{
	auto instructionsize = current.get_Count();

	if (instructionsize == 4)
	{
		auto fnname = current[1].str;

		auto argsname = current[2].expression;
		auto argscount = argsname->get_Count();

		auto fnobj = ObjectHelper::NewFunctionRuntime(state, {});
		auto& fruntime = fnobj->data()->get_runtimefn();

		fruntime.body = current[3].instruction;

		for (size_t i = 0; i < argscount; i++)
		{
			fruntime.argsname.push_back(argsname->at(i)[0].str->data());
		}

		state->scope->SetVar(fnname->data(), fnobj.v);
	}
	return 0;
}

int LogicCode::Std::Return(LogicCodeState* state, Light::List& current)
{
	auto instructionsize = current.get_Count();
	if (instructionsize >= 2)
	{
		auto lenlist = instructionsize - 1;
		Light::List values(lenlist, lenlist, &current.at(1));

		auto v2 = Helper::PushList(state, values);
		if (!state->CanRun())
		{
			if (!state->IsError())
			{
				state->error = "Don't use return in 'return'";
			}
			else
			{
				return 0;
			}
			return 0;
		}

		state->ret = true;
		return v2;
	}
	else
	{
		return 0;

	}
}

int LogicCode::Std::Print(FunctionData* __this, LogicCodeState* state)
{
	auto& stack = state->stack;
	auto& scope = state->scope;
	auto len = stack.sizeoffset();

	if (len >= 1)
	{

		for (size_t i = 0; i < len; i++)
		{
			if (i > 0)
			{
				std::cout << " ";

			}
			_Print(stack.get(i));
			
		}

		std::cout << std::endl;

	}
	return 0;
}

void LogicCode::Std::_Print(Object::refcount_ptr_elem& obj)
{
	if (!obj || obj->CheckType(ObjectType::None))
	{
		std::cout << "None";
	}
	else if (obj->CheckType(ObjectType::Bitset))
	{
		auto result = obj->GetBitset();
		std::cout << result->to_string();
	}
	else if (obj->CheckType(ObjectType::Integer))
	{
		auto result = obj->GetInteger();
		std::cout << result;
	}
	else if (obj->CheckType(ObjectType::Number))
	{
		auto result = obj->GetNumber();
		std::cout << result;
	}
	else if (obj->CheckType(ObjectType::RefBitset))
	{
		
		std::cout << "Reference: " << obj.get();
	}
	else if (obj->CheckType(ObjectType::String))
	{
		auto result = obj->GetString();
		std::cout.write(result->txt, result->size);
	}
}

int LogicCode::Std::Const(LogicCodeState* state, Light::List& current)
{
	auto instructionsize = current.get_Count();

	if (instructionsize >= 4)
	{
		auto name = current[1].str;
		auto type = current[2];

		if (type.resultType == Light::ResultType::Operador)
		{
			if (*type.coperator == Light::COperator::Set)
			{
				auto lenlist = instructionsize - 3;
				Light::List values(lenlist, lenlist, &current.at(3));
				auto v2 = Helper::ToBitSetFromList(state, values);
				if (!state->CanRun())
				{
					if (!state->IsError())
					{
						state->error = "Don't use return in 'const'";
					}
					else
					{
						return 0;
					}
					return 0;
				}
				state->scope->SetConst(name->data(), v2, false);
			}
		}
	}
	return 0;
}

int LogicCode::Std::Var(LogicCodeState* state, Light::List& current)
{
	auto instructionsize = current.get_Count();

	if (instructionsize >= 4)
	{
		auto name = current[1].str;
		auto type = current[2];

		if (type.resultType == Light::ResultType::Operador)
		{
			if (*type.coperator == Light::COperator::Set)
			{
				auto lenlist = instructionsize - 3;
				Light::List values(lenlist, lenlist, &current.at(3));
				auto v2 = Helper::ToBitSetFromList(state, values);
				if (!state->CanRun())
				{
					if (!state->IsError())
					{
						state->error = "Don't use return in 'var'";
					}
					else
					{
						return 0;
					}
					return 0;
				}
				state->scope->SetVar(name->data(), v2, false);
			}
		}
	}
	return 0;
}

int LogicCode::Std::Case(LogicCodeState* state, Light::List& current)
{
	auto instructionsize = current.get_Count();

	if (instructionsize == 3)
	{
		auto bits = Helper::ToBitSetFromCommand(state, current[1]);
		auto bits_ = bits->GetBitset();
		if (!state->CanRun())
		{
			if (!state->IsError())
			{
				_Error(state, "Don't use return in 'case'");
			}
			else
			{
				return 0;
			}
			return 0;
		}
		if (!bits || bits_->size() == 0)
		{
			return _Error(state, "NULL or zero size");
		}
		auto condition = bits_->get(0);
		if (condition)
		{
			return Helper::PushCommand(state, current[2]);
		}
		else
		{
			return Helper::PushCommand(state, current[3]);
		}


	}
	return 0;
}

int LogicCode::Std::Buffer(FunctionData* __this, LogicCodeState* state)
{
	auto& stack = state->stack;
	auto& scope = state->scope;
	auto len = stack.sizeoffset();
	if (len == 1)
	{

		auto first = stack.get(0)->GetBitset();
		auto firstparam = ObjectHelper::NewBitset(first->size());
		auto firstlen = first->size();
		for (size_t i = 0; i < firstlen; i++)
		{
			firstparam->set(i, first->get(i));
		}
		stack.push(firstparam);
		return 1;

	}
	return 0;
}

int LogicCode::Std::Zero(FunctionData* __this, LogicCodeState* state)
{
	auto& stack = state->stack;
	auto& scope = state->scope;
	auto len = stack.sizeoffset();
	if (len == 1)
	{

		auto first = stack.get(0)->GetInteger();
		auto ret = ObjectHelper::NewBitset((size_t)first);
		for (uint8_t i = 0; i < first; i++)
		{
			ret->set(i, false);
		}
		stack.push(ret);
		return 1;

	}
	return 0;
}

int LogicCode::Std::One(FunctionData* __this, LogicCodeState* state)
{
	auto& stack = state->stack;
	auto& scope = state->scope;
	auto len = stack.sizeoffset();
	if (len == 1)
	{

		auto first = stack.get(0)->GetInteger();
		auto ret = ObjectHelper::NewBitset((size_t)first);
		for (LogicInteger i = 0; i < first; i++)
		{
			ret->set(i, true);
		}
		stack.push(ret);
		return 1;

	}
	return 0;
}


int LogicCode::Std::Intv(LogicCodeState* state, Light::List& current)
{
	auto instructionsize = current.get_Count();

	if (instructionsize == 2)
	{
		auto numi8 = current[1].str;

		LogicInteger num = (LogicInteger)std::strtoll(numi8->data(), nullptr, 10);
		auto val = ObjectHelper::NewInteger(num);
		state->stack.push(val);
		return 1;
	}
	return 0;
}

int LogicCode::Std::Numv(LogicCodeState* state, Light::List& current)
{
	auto instructionsize = current.get_Count();

	if (instructionsize == 2)
	{
		auto numi8 = current[1].str;
		LogicNumber num = (LogicNumber)strtod(numi8->data(), nullptr);
		auto val = ObjectHelper::NewNumber(num);
		state->stack.push(val);
		return 1;
	}
	return 0;
}

int LogicCode::Std::Ref(LogicCodeState* state, Light::List& current)
{
	auto instructionsize = current.get_Count();

	if (instructionsize == 2)
	{
		auto bits = current[1].str;
	
		auto v = ObjectHelper::NewRefBitset(bits->data(), state->scope);
		state->stack.push(v);

		return 1;
	}
	return 0;
}

int LogicCode::Std::Mux(FunctionData* __this, LogicCodeState* state)
{
	auto& stack = state->stack;
	auto& scope = state->scope;
	auto len = stack.sizeoffset();
	if (len >= 2)
	{

		auto selectbits = stack.get(0)->GetInteger();

		auto lenargs = len - 1;
		if (selectbits < lenargs)
		{
			auto selected = stack.get(selectbits + 1);
			stack.push(selected);
			return 1;
		}

	}
	return 0;
}

int LogicCode::Std::Demux(FunctionData* __this, LogicCodeState* state)
{
	auto& stack = state->stack;
	auto& scope = state->scope;
	auto len = stack.sizeoffset();
	if (len >= 3)
	{

		auto selectbits = stack.get(0)->GetInteger();
		auto value = stack.get(1);


		auto lenargs = len - 2;
		if (selectbits < lenargs)
		{

			auto value_selected = stack.get(selectbits + 2).get();
			auto refbitset = LogicRefBitset::FromObject(value_selected);
			refbitset->SetValue(value);
			return 0;
		}

	}
	return 0;
}

int LogicCode::Std::Decoder(FunctionData* __this, LogicCodeState* state)
{
	auto& stack = state->stack;
	auto& scope = state->scope;
	auto len = stack.sizeoffset();
	if (len >= 2)
	{

		auto selectbits = stack.get(0)->GetInteger();


		auto lenargs = len - 1;
		if (selectbits < lenargs)
		{

			auto ret = ObjectHelper::NewBitset(true);

			auto value_selected = stack.get(selectbits + 1).get();
			auto refbitset = LogicRefBitset::FromObject(value_selected);
			refbitset->SetValue(ret.v);

			refbitset->scope->SetVar(refbitset->name.txt, ret.v);
			return 0;
		}

	}
	return 0;
}

int LogicCode::Std::BitSelector(FunctionData* __this, LogicCodeState* state)
{
	auto& stack = state->stack;
	auto& scope = state->scope;
	auto len = stack.sizeoffset();
	if (len == 2)
	{
		auto bits = stack.get(0)->GetBitset();

		auto selectbits = stack.get(1)->GetInteger();

		auto bitssize = bits->size();
		if (selectbits < bitssize)
		{
			auto newbit = ObjectHelper::NewBitset(bits->get(selectbits));
			stack.push(newbit);
			return 1;
		}

	}
	return 0;
}

int LogicCode::Std::Add(FunctionData* __this, LogicCodeState* state)
{
	auto& stack = state->stack;
	auto& scope = state->scope;
	auto len = stack.sizeoffset();
	if (len == 2)
	{
		auto value1 = stack.get(0)->GetBitset();
		auto value2 = stack.get(1)->GetBitset();
		auto value1size = value1->size();
		auto value2size = value2->size();
		if (value1size == value2size)
		{
			auto result = ObjectHelper::NewBitset(value1size);

			auto CarryIn = false;
			for (size_t i = 0; i < value1size; i++)
			{
				auto A = value1->get(i);
				auto B = value2->get(i);
				auto CarryOut = A && B || CarryIn && B || CarryIn && A;
				auto C = !CarryIn && !A && B || !CarryIn && A && !B || CarryIn && !A && !B || CarryIn && A && B;


				result->set(i, C);
				CarryIn = CarryOut;

			}

			stack.push(result);
			return 1;
		}

	}

	return 0;


}

int LogicCode::Std::Sub(FunctionData* __this, LogicCodeState* state)
{
	auto& stack = state->stack;
	auto& scope = state->scope;
	auto len = stack.sizeoffset();
	if (len == 2)
	{
		auto value1 = stack.get(0)->GetBitset();
		auto value2 = stack.get(1)->GetBitset();
		auto value1size = value1->size();
		auto value2size = value2->size();
		if (value1size == value2size)
		{
			auto result = ObjectHelper::NewBitset(value1size);


			auto BorrowIn = false;
			for (size_t i = 0; i < value1size; i++)
			{
				auto A = value1->get(i);
				auto B = value2->get(i);
				auto C = !BorrowIn && !A && B || !BorrowIn && A && !B || BorrowIn && !A && !B || BorrowIn && A && B;
				auto BorrowOut = !A && B || BorrowIn && !A || BorrowIn && B;
				result->set(i, C);

				BorrowIn = BorrowOut;
			}

			stack.push(result);
			return 1;
		}

	}

	return 0;
}

int LogicCode::Std::Mul(FunctionData* __this, LogicCodeState* state)
{
	auto& stack = state->stack;
	auto& scope = state->scope;
	auto len = stack.sizeoffset();
	if (len == 2)
	{
		auto value1 = stack.get(0)->GetBitset();
		auto value2 = stack.get(1)->GetBitset();
		auto value1size = value1->size();
		auto value2size = value2->size();
		if (value1size == value2size)
		{
			auto mulresult = value1size * 2;
			auto result = ObjectHelper::NewBitset(mulresult);
			auto temp = ObjectHelper::NewBitset(value1size);
			for (size_t i = 0; i < value1size; i++)
			{
				auto bitcurrent2 = value2->get(i);
				for (size_t i2 = 0; i2 < value1size; i2++)
				{
					auto bitcurrent1 = value1->get(i2);
					temp->set(i2, bitcurrent2 && bitcurrent1);
				}
				auto CarryIn = false;

				for (size_t i2 = 0; i2 < value1size; i2++)
				{
					auto A = temp->get(i2);
					auto B = result->get(i2 + i);
					result->set(i2 + i, !A && !B && CarryIn ||
						!A && B && !CarryIn ||
						A && !B && !CarryIn ||
						A && B && CarryIn);

					CarryIn = B && CarryIn ||
						A && CarryIn ||
						A && B;

				}
				result->set(i + value1size, CarryIn);

			}
			stack.push(result);
			return 1;
		}
	}
	return 0;
}

int LogicCode::Std::Div(FunctionData* __this, LogicCodeState* state)
{
	auto& stack = state->stack;
	auto& scope = state->scope;
	auto len = stack.sizeoffset();
	if (len >= 2)
	{
		auto value1 = stack.get(0)->GetBitset();
		auto value2 = stack.get(1)->GetBitset();
		auto value1size = value1->size();
		auto value2size = value2->size();
		if (value1size == value2size)
		{
			int sizev1 = 0, sizev2 = 0;
			for (size_t i = 0; i < value1size; i++)
			{
				auto currentvalue1 = value1->get(i);
				auto currentvalue2 = value2->get(i);

				if (currentvalue1)
				{
					sizev1 = i + 1;
				}
				if (currentvalue2)
				{
					sizev2 = i + 1;
				}

			}
			if (sizev2 != 0)
			{
				if (sizev1 == 0 || sizev2 > sizev1)
				{
					auto retv = ObjectHelper::NewBitset(value1size);
					stack.push(retv);
					return 1;
				}

				auto equalsdivsize = sizev2 == sizev1;
				auto remainder = ObjectHelper::NewBitset(value1size);
				auto quotient = ObjectHelper::NewBitset(value1size);
				auto tempsize = equalsdivsize ? (size_t)sizev2 : (size_t)sizev2 + 1;
				auto temp = std::bitsetdynamic::Make(tempsize);

				size_t i = (equalsdivsize ? 0 : sizev1 - sizev2) + 1;

				auto copyv = equalsdivsize ? tempsize : tempsize - 1;
				auto startbound = equalsdivsize ? 0 : sizev1 - sizev2;
				for (size_t i2 = 0; i2 < copyv; i2++)
				{
					remainder->set(i2, value1->get(startbound + i2));
				}
				
				while (i > 0)
				{
					auto iv = i - 1;
					bool BorrowIn = false;
					for (size_t i2 = 0; i2 < tempsize; i2++)
					{
						auto A = remainder->get(i2);
						auto B = value2->get(i2);
						auto C = !BorrowIn && !A && B || !BorrowIn && A && !B || BorrowIn && !A && !B || BorrowIn && A && B;
						auto BorrowOut = !A && B || BorrowIn && !A || BorrowIn && B;
						temp->set(i2, C);

						BorrowIn = BorrowOut;


					}

					if (!BorrowIn)
					{
						for (size_t i2 = 0; i2 < tempsize; i2++)
						{
							remainder->set(i2, temp->get(i2));
						}
					}


					for (size_t i2 = value1size; i2 > 1; i2--)
					{
						quotient->set(i2 - 1, quotient->get(i2 - 2));
					}
					quotient->set(0, !BorrowIn);
					if (i > 1)
					{
						for (size_t i2 = tempsize; i2 > 1; i2--)
						{
							remainder->set(i2 - 1, remainder->get(i2 - 2));
						}
						remainder->set(0, value1->get(iv - 1));
					}
					i--;

				}

				if (len >= 3)
				{
					auto value_selected = stack.get(2).get();
					auto refbitsett = LogicRefBitset::FromObject(value_selected);
					refbitsett->SetValue(remainder.v);
				}
				stack.push(quotient);
				return 1;
			}


			return _Error(state, "Division by zero");
		}

	}
	return 0;
}

int LogicCode::Std::TruthTable(LogicCodeState* state, Light::List& current)
{
	auto instructionsize = current.get_Count();
	if (instructionsize == 3)
	{
		auto expression = current.at(1).expression;
		auto instruction = current.at(2).instruction;
		auto expressionlen = expression->get_Count();
		auto looplen = expressionlen * 2;
		std::vector<std::string> argsname;
		auto inputs = std::bitsetdynamic::Make((size_t)expressionlen);
		auto totalWidth = 7;
		for (size_t i = 0; i < expressionlen; i++)
		{
			auto str = expression->at(i).at(0).str;
			auto str_size = str->size();
			argsname.push_back(str->data());
			if (str_size + 1 > totalWidth)
			{
				totalWidth = str_size + 1;
			}
		}
		

		bool first = true;
		for (auto& element : argsname)
		{
			std::cout << std::setw(totalWidth) << std::left << element;

		}
		std::cout << "| ";
		std::cout << std::setw(totalWidth) << std::left << "result";
		std::cout << std::endl;
		for (size_t i = 0; i < looplen; i++)
		{
			auto oldoffset = state->stack.get_Offset();
			state->stack.set_Offset(oldoffset);

			auto oldscope = state->scope;

			auto newscope = std::refcount_ptr<VariableData>::make();
			newscope->parent = oldscope;
			state->scope = newscope;

			for (size_t i2 = 0; i2 < expressionlen; i2++)
			{
				auto currentv = inputs->get(i2);
				std::cout << std::setw(totalWidth) << std::left << currentv;
				auto v_bitset = ObjectHelper::NewBitset(currentv);
				newscope->SetConst(argsname.at(i2), v_bitset.v,false);
			}
			Helper::ExecuteInstruction(state, *instruction);

			state->scope = oldscope;

			state->ret = false;
			state->stack.set_Offset(oldoffset);

			auto returnv = Helper::ToBitSet(state)->get(0);


			std::cout << "| " << std::setw(totalWidth) << std::left << returnv << std::endl;

			__Inc(inputs);
		}
		
	}
	return 0;
}

void LogicCode::Std::__Inc(std::bitsetdynamic::refcount_ptr_elem& v)
{
	auto size = v->size();
	auto CarryIn = false;
	for (size_t i = 0; i < size; i++)
	{
		auto A = v->get(i);
		auto B = i == 0;
		auto CarryOut = A && B || CarryIn && B || CarryIn && A;
		auto C = !CarryIn && !A && B || !CarryIn && A && !B || CarryIn && !A && !B || CarryIn && A && B;


		v->set(i, C);
		CarryIn = CarryOut;

	}
}

int8_t LogicCode::Std::__Toi8(std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic>& v)
{
	auto sizev = v->size();
	auto len = sizev < 8 ? 0 : sizev - 8;
	int8_t value = 0;

	for (size_t i = 0; i < sizev; i++)
	{
		value <<= 1;
		value |= (int8_t)v->get(sizev - i - 1);
	}
	return value;
}

bool LogicCode::Std::__ToBool(std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic>& v)
{
	auto size = v->size();
	if (size > 0)
	{
		return v->get(0);
	}
	return false;
}




void LogicCode::Std::__Init(LogicCodeState* state)
{
	auto scope = state->scope;
	scope->SetVar("and", ObjectHelper::NewFunctionNative(state, { And }).v);
	scope->SetVar("or", ObjectHelper::NewFunctionNative(state, { Or }).v);
	scope->SetVar("not", ObjectHelper::NewFunctionNative(state, { Not }).v);

	
	scope->SetVar("xor", ObjectHelper::NewFunctionNative(state, { Xor }).v);
	scope->SetVar("nand", ObjectHelper::NewFunctionNative(state, { Nand }).v);
	scope->SetVar("nor", ObjectHelper::NewFunctionNative(state, { Nor }).v);
	scope->SetVar("xnor", ObjectHelper::NewFunctionNative(state, { Xnor }).v);
	scope->SetVar("print", ObjectHelper::NewFunctionNative(state, { Print }).v);
	scope->SetVar("buffer", ObjectHelper::NewFunctionNative(state, { Buffer }).v);
	scope->SetVar("zero", ObjectHelper::NewFunctionNative(state, { Zero }).v);
	scope->SetVar("one", ObjectHelper::NewFunctionNative(state, { One }).v);
	scope->SetVar("mux", ObjectHelper::NewFunctionNative(state, { Mux }).v);
	scope->SetVar("demux", ObjectHelper::NewFunctionNative(state, { Demux }).v);
	scope->SetVar("decoder", ObjectHelper::NewFunctionNative(state, { Decoder }).v);
	scope->SetVar("bitselector", ObjectHelper::NewFunctionNative(state, { BitSelector }).v);
	scope->SetVar("add", ObjectHelper::NewFunctionNative(state, { Add }).v);
	scope->SetVar("sub", ObjectHelper::NewFunctionNative(state, { Sub }).v);
	scope->SetVar("mul", ObjectHelper::NewFunctionNative(state, { Mul }).v);
	scope->SetVar("div", ObjectHelper::NewFunctionNative(state, { Div }).v);

}

int LogicCode::Std::_Error(LogicCodeState* state, const char* v)
{
	state->error = v;
	return 0;
}
