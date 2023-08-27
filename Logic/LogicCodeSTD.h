#pragma once
#include <Light.h>
#include "VariableData.hpp"
#include "bitsetdynamic.hpp"
#include "LogicCodeHelper.h"
namespace LogicCode::Std
{	

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
	void _Print(Object::refcount_ptr_elem& obj);

	int Const(LogicCodeState* state, Light::List& current);
	int Var(LogicCodeState* state, Light::List& current);
	int Case(LogicCodeState* state, Light::List& current);
	int Buffer(FunctionData* __this, LogicCodeState* state);
	int Zero(FunctionData* __this, LogicCodeState* state);
	int One(FunctionData* __this, LogicCodeState* state);
	int Intv(LogicCodeState* state, Light::List& current);
	int Numv(LogicCodeState* state, Light::List& current);

	int Ref(LogicCodeState* state, Light::List& current);
	int Mux(FunctionData* __this, LogicCodeState* state);
	int Demux(FunctionData* __this, LogicCodeState* state);
	int Decoder(FunctionData* __this, LogicCodeState* state);
	int BitSelector(FunctionData* __this, LogicCodeState* state);
	int Add(FunctionData* __this, LogicCodeState* state);
	int Sub(FunctionData* __this, LogicCodeState* state);
	int Mul(FunctionData* __this, LogicCodeState* state);
	int Div(FunctionData* __this, LogicCodeState* state);
	int GetType(FunctionData* __this, LogicCodeState* state);
	int TruthTable(FunctionData* __this, LogicCodeState* state);

	int function_isNative(FunctionData* __this, LogicCodeState* state);
	int function_isRuntime(FunctionData* __this, LogicCodeState* state);
	int function_argslen(FunctionData* __this, LogicCodeState* state);
	int function_getargname(FunctionData* __this, LogicCodeState* state);

	int refbitset_get(FunctionData* __this, LogicCodeState* state);
	int refbitset_set(FunctionData* __this, LogicCodeState* state);

	int integer_Abs(FunctionData* __this, LogicCodeState* state);
	int integer_Equals(FunctionData* __this, LogicCodeState* state);
	int integer_Clamp(FunctionData* __this, LogicCodeState* state);
	int integer_IsNegative(FunctionData* __this, LogicCodeState* state);
	int integer_IsPositive(FunctionData* __this, LogicCodeState* state);
	int integer_Max(FunctionData* __this, LogicCodeState* state);
	int integer_Min(FunctionData* __this, LogicCodeState* state);
	int integer_Parse(FunctionData* __this, LogicCodeState* state);
	int integer_Sign(FunctionData* __this, LogicCodeState* state);
	int integer_ToString(FunctionData* __this, LogicCodeState* state);

	int number_Abs(FunctionData* __this, LogicCodeState* state);
	int number_Clamp(FunctionData* __this, LogicCodeState* state);
	int number_Equals(FunctionData* __this, LogicCodeState* state);
	int number_IsFinite(FunctionData* __this, LogicCodeState* state);
	int number_IsInfinity(FunctionData* __this, LogicCodeState* state);
	int number_IsNaN(FunctionData* __this, LogicCodeState* state);
	int number_IsNegative(FunctionData* __this, LogicCodeState* state);
	int number_IsNegativeInfinity(FunctionData* __this, LogicCodeState* state);
	int number_IsPositive(FunctionData* __this, LogicCodeState* state);
	int number_IsPositiveInfinity(FunctionData* __this, LogicCodeState* state);
	int number_Max(FunctionData* __this, LogicCodeState* state);
	int number_Min(FunctionData* __this, LogicCodeState* state);
	int number_Parse(FunctionData* __this, LogicCodeState* state);
	int number_ToString(FunctionData* __this, LogicCodeState* state);

	int string_byte(FunctionData* __this, LogicCodeState* state);
	int string_char(FunctionData* __this, LogicCodeState* state);
	int string_len(FunctionData* __this, LogicCodeState* state);
	int string_reverse(FunctionData* __this, LogicCodeState* state);
	int string_lower(FunctionData* __this, LogicCodeState* state);
	int string_upper(FunctionData* __this, LogicCodeState* state);

	int bitset_tostring(FunctionData* __this, LogicCodeState* state);
	int bitset_parse(FunctionData* __this, LogicCodeState* state);

	void __Inc(std::bitsetdynamic::refcount_ptr_elem& v);

	void __Init(LogicCodeState* state);
	int _Error(LogicCodeState* state,const char* v);
};

