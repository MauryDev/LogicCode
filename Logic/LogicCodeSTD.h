#pragma once
#include <Light.h>
#include "VariableData.h"
#include "bitsetdynamic.h"
#include "LogicCodeHelper.h"
namespace LogicCode::Std
{
	struct RefValue
	{
		LogicCodeState* state;

		const char* str();
		static std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic> NewBitSet(LogicCodeState* state,Light::string_view& str);
	};
	void And(FunctionData* __this, LogicCodeState* state);
	void Or(FunctionData* __this, LogicCodeState* state);
	void Not(FunctionData* __this, LogicCodeState* state);
	void Xor(FunctionData* __this, LogicCodeState* state);
	void Nand(FunctionData* __this, LogicCodeState* state);
	void Xnor(FunctionData* __this, LogicCodeState* state);
	void Nor(FunctionData* __this, LogicCodeState* state);
	void Xnor(FunctionData* __this, LogicCodeState* state);
	void If(LogicCodeState* state,Light::List& current);
	void While(LogicCodeState* state, Light::List& current);
	void Fun(LogicCodeState* state, Light::List& current);
	void Return(LogicCodeState* state, Light::List& current);
	void Print(FunctionData* __this, LogicCodeState* state);
	void Const(LogicCodeState* state, Light::List& current);
	void Case(LogicCodeState* state, Light::List& current);
	void Buffer(FunctionData* __this, LogicCodeState* state);
	void Zero(FunctionData* __this, LogicCodeState* state);
	void One(FunctionData* __this, LogicCodeState* state);
	std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic> i8(LogicCodeState* state, Light::List& current);
	std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic> Ref(LogicCodeState* state, Light::List& current);
	void Mux(FunctionData* __this, LogicCodeState* state);
	void Demux(FunctionData* __this, LogicCodeState* state);

	// Decoder,SelectBit,Add,Sub,Mul,Div
	void __Init(LogicCodeState* state);

};

