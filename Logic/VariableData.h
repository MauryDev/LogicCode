#pragma once
#include <unordered_map>
#include <Light.h>
#include "FunctionData.h"
struct VariableData
{

	enum class VarType
	{
		None,
		Const,
		Var,
		Function
	};
	VariableData* parent;
	std::unordered_map<std::string, bool> vars;
	std::unordered_map<std::string, bool> consts;
	std::unordered_map<std::string, FunctionData> functions;

	bool ret;
	bool GetValue(std::string& str);
	bool GetValue(std::string&& str);

	FunctionData GetFunction(std::string& str);
	FunctionData GetFunction(std::string&& str);


	void SetFunction(std::string&& str, FunctionData& value);
	void SetFunction(std::string& str, FunctionData& value);

	bool Exists(std::string& str);
	bool Exists(std::string&& str);

	VarType GetTypeVariable(std::string& str);
	VarType GetTypeVariable(std::string&& str);

	void SetConst(std::string& str,bool v);
	void SetConst(std::string&& str, bool v);
	void SetVar(std::string& str, bool v);
	void SetVar(std::string&& str, bool v);
};

