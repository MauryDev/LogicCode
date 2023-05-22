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
	int And(FunctionData* __this, LogicCodeState* state);
	int Or(FunctionData* __this, LogicCodeState* state);
	int Not(FunctionData* __this, LogicCodeState* state);
	int Xor(FunctionData* __this, LogicCodeState* state);
	int Nand(FunctionData* __this, LogicCodeState* state);
	int Xnor(FunctionData* __this, LogicCodeState* state);
	int Nor(FunctionData* __this, LogicCodeState* state);
	int Xnor(FunctionData* __this, LogicCodeState* state);
	int If(LogicCodeState* state,Light::List& current);
	int While(LogicCodeState* state, Light::List& current);
	int Fun(LogicCodeState* state, Light::List& current);
	int Return(LogicCodeState* state, Light::List& current);
	int Print(FunctionData* __this, LogicCodeState* state);
	int Const(LogicCodeState* state, Light::List& current);
	int Var(LogicCodeState* state, Light::List& current);
	int Case(LogicCodeState* state, Light::List& current);
	int Buffer(FunctionData* __this, LogicCodeState* state);
	int Zero(FunctionData* __this, LogicCodeState* state);
	int One(FunctionData* __this, LogicCodeState* state);
	int i8(LogicCodeState* state, Light::List& current);
	int Ref(LogicCodeState* state, Light::List& current);
	int Mux(FunctionData* __this, LogicCodeState* state);
	int Demux(FunctionData* __this, LogicCodeState* state);
	int Decoder(FunctionData* __this, LogicCodeState* state);
	int BitSelector(FunctionData* __this, LogicCodeState* state);
	int Add(FunctionData* __this, LogicCodeState* state);
	int Sub(FunctionData* __this, LogicCodeState* state);
	int Mul(FunctionData* __this, LogicCodeState* state);
	int Div(FunctionData* __this, LogicCodeState* state);
	int TruthTable(LogicCodeState* state, Light::List& current);

	void __Inc(std::bitsetdynamic::refcount_ptr_elem& v);

	int8_t __Toi8(std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic>& v);
	bool __ToBool(std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic>& v);

	void __Init(LogicCodeState* state);
	int _Error(LogicCodeState* state,const char* v);
};

