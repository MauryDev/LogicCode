#pragma once
#include <Light.h>
#include "VariableData.hpp"
#include "bitsetdynamic.hpp"
#include "LogicCodeHelper.h"
namespace LogicCode::Std
{	

    int If(LogicCodeState* state, Light::List& current);
    int While(LogicCodeState* state, Light::List& current);
    int Fun(LogicCodeState* state, Light::List& current);
    int Return(LogicCodeState* state, Light::List& current);
    int Const(LogicCodeState* state, Light::List& current);
    int Var(LogicCodeState* state, Light::List& current);
    int Case(LogicCodeState* state, Light::List& current);
    int Intv(LogicCodeState* state, Light::List& current);
    int Numv(LogicCodeState* state, Light::List& current);
    int Ref(LogicCodeState* state, Light::List& current);
   


	int And(LogicCodeState* state);
	int Or(LogicCodeState* state);
	int Not(LogicCodeState* state);
	int Xor(LogicCodeState* state);
	int Nand(LogicCodeState* state);
	int Xnor(LogicCodeState* state);
	int Nor(LogicCodeState* state);
	int Xnor(LogicCodeState* state);
    int Buffer(LogicCodeState* state);
	int ControlledBuffer(LogicCodeState* state);
	int ControlledInverter(LogicCodeState* state);
	int OddParity(LogicCodeState* state);
	int EvenParity(LogicCodeState* state);

    int Mux(LogicCodeState* L);
    int Demux(LogicCodeState* L);
    int Decoder(LogicCodeState* L);
    int BitSelector(LogicCodeState* L);
    int PriorityDecoder(LogicCodeState* L);

    int Add(LogicCodeState* L);
    int Sub(LogicCodeState* L);
    int Mul(LogicCodeState* L);
    int Div(LogicCodeState* L);
    int Negator(LogicCodeState* L);

    int GetType(LogicCodeState* state);
    int IsNone(LogicCodeState* L);
    int Argslen(LogicCodeState* L);
    int Zero(LogicCodeState* state);
    int One(LogicCodeState* state);
    int TruthTable(LogicCodeState* state);



    int Print(LogicCodeState* state);
    void _Print(Object::refcount_ptr_elem& obj);
    void _Debug_Log(Object::refcount_ptr_elem& obj);
    int Debug_Log(LogicCodeState* state);
    int Debug_Clear(LogicCodeState* state);

	int function_isNative(LogicCodeState* state);
	int function_isRuntime(LogicCodeState* state);
	int function_argslen(LogicCodeState* state);
	int function_getargname(LogicCodeState* state);

	int refbitset_get(LogicCodeState* state);
	int refbitset_set(LogicCodeState* state);

	int integer_Abs(LogicCodeState* state);
	int integer_Equals(LogicCodeState* state);
	int integer_Clamp(LogicCodeState* state);
	int integer_IsNegative(LogicCodeState* state);
	int integer_IsPositive(LogicCodeState* state);
	int integer_Max(LogicCodeState* state);
	int integer_Min(LogicCodeState* state);
	int integer_Parse(LogicCodeState* state);
	int integer_Sign(LogicCodeState* state);
	int integer_ToString(LogicCodeState* state);

	int number_Abs(LogicCodeState* state);
	int number_Clamp(LogicCodeState* state);
	int number_Equals(LogicCodeState* state);
	int number_IsFinite(LogicCodeState* state);
	int number_IsInfinity(LogicCodeState* state);
	int number_IsNaN(LogicCodeState* state);
	int number_IsNegative(LogicCodeState* state);
	int number_IsNegativeInfinity(LogicCodeState* state);
	int number_IsPositive(LogicCodeState* state);
	int number_IsPositiveInfinity(LogicCodeState* state);
	int number_Max(LogicCodeState* state);
	int number_Min(LogicCodeState* state);
	int number_Parse(LogicCodeState* state);
	int number_ToString(LogicCodeState* state);

	int string_byte(LogicCodeState* state);
	int string_char(LogicCodeState* state);
	int string_len(LogicCodeState* state);
	int string_reverse(LogicCodeState* state);
	int string_lower(LogicCodeState* state);
	int string_upper(LogicCodeState* state);

	int bitset_tostring(LogicCodeState* state);
	int bitset_parse(LogicCodeState* state);
	int bitset_len(LogicCodeState* state);
    int bitset_concat(LogicCodeState* L);
    int bitset_slice(LogicCodeState* L);
    int bitset_reverse(LogicCodeState* L);

	void __Inc(std::bitsetdynamic* v);
    void __Dec(std::bitsetdynamic* v);

	void __Init(LogicCodeState* state);
	int _Error(LogicCodeState* state,const char* v);
};

