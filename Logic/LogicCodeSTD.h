#pragma once
#include <Light.h>
#include "VariableData.h"
#include "bitsetdynamic.h"

namespace LogicCode::Std
{
	bool And(Light::List& current, VariableData& vars, bool& ret);
	bool Or(Light::List& current, VariableData& vars, bool& ret);
	bool Not(Light::List& current, VariableData& vars, bool& ret);
	bool Xor(Light::List& current, VariableData& vars, bool& ret);
	bool Nand(Light::List& current, VariableData& vars, bool& ret);
	bool Nor(Light::List& current, VariableData& vars, bool& ret);
	bool Xnor(Light::List& current, VariableData& vars, bool& ret);
	void If(Light::List& current, VariableData& vars, bool& ret);
	void While(Light::List& current, VariableData& vars, bool& ret);
	void Fun(Light::List& current, VariableData& vars, bool& ret);
	void Return(Light::List& current, VariableData& vars, bool& ret);
	void Print(Light::List& current, VariableData& vars, bool& ret);
	void Const(Light::List& current, VariableData& vars, bool& ret);
	bool Case(Light::List& current, VariableData& vars, bool& ret);
	
	void _AddBitArray(std::bitsetdynamic& bitset);
	void TruthTable(Light::List& current, VariableData& vars, bool& ret);

};

