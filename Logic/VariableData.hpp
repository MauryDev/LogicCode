
#ifndef Logic_VariableData_HPP
#define Logic_VariableData_HPP
struct FunctionData;
#include <unordered_map>
#include <Light.h>
#include "refcount_ptr.hpp"
#include "StackObject.h"
#include "LogicStructs.hpp"
#include "LogicString.hpp"
#include "LogicFunctionData.hpp"

struct VariableData
{

	

	std::refcount_ptr<VariableData> parent;
	std::unordered_map<std::string, LogicCode::Object::refcount_ptr_elem> vars;
	std::unordered_map<std::string, LogicCode::Object::refcount_ptr_elem> consts;
	VariableData() {
		parent = {};
	}
	~VariableData() {}

	LogicCode::Object::refcount_ptr_elem GetValue(std::string& str)
	{
		auto invars = vars.find(str);
		if (invars != vars.end())
		{
			return invars->second;
		}
		auto inconsts = consts.find(str);
		if (inconsts != consts.end())
		{
			return inconsts->second;
		}
		if (parent)
		{
			return parent->GetValue(str);
		}
		return LogicCode::Object::refcount_ptr_elem();
	}
	LogicCode::Object::refcount_ptr_elem GetValue(std::string&& str)
	{
		return GetValue(str);
	}

	

	

	bool Exists(std::string& str, bool checkparent = true)
	{
		auto invars = vars.find(str);
		if (invars != vars.end())
		{
			return true;
		}
		auto inconsts = consts.find(str);
		if (inconsts != consts.end())
		{
			return true;
		}
		if (checkparent && parent)
		{
			return parent->Exists(str);
		}
		return false;
	}
	bool Exists(std::string&& str, bool checkparent = true)
	{
		return Exists(str, checkparent);
	}

	LogicCode::VarType GetTypeVariable(std::string& str, bool checkparent = true)
	{
		auto invars = vars.find(str);
		if (invars != vars.end())
		{
			return LogicCode::VarType::Var;
		}
		auto inconsts = consts.find(str);
		if (inconsts != consts.end())
		{
			return LogicCode::VarType::Const;
		}
		
		if (checkparent && parent)
		{
			return parent->GetTypeVariable(str);
		}
		return LogicCode::VarType::None;
	}
	LogicCode::VarType GetTypeVariable(std::string&& str, bool checkparent = true)
	{
		return GetTypeVariable(str, checkparent);
	}

	void SetConst(std::string& str, LogicCode::Object::refcount_ptr_elem&& v, bool checkparent = true)
	{
		SetConst(str, v, checkparent);
	}
	void SetConst(std::string& str, LogicCode::Object::refcount_ptr_elem& v, bool checkparent = true)
	{
		if (!Exists(str, checkparent))
		{
			consts[str] = v;
		}
	}
	void SetConst(std::string&& str, LogicCode::Object::refcount_ptr_elem&& v, bool checkparent = true)
	{
		SetConst(str, v, checkparent);
	}
	void SetConst(std::string&& str, LogicCode::Object::refcount_ptr_elem& v, bool checkparent = true)
	{
		SetConst(str, v, checkparent);
	}

	void SetVar(std::string& str, LogicCode::Object::refcount_ptr_elem&& v, bool checkparent = true)
	{
		SetVar(str, v, checkparent);
	}
	void SetVar(std::string& str, LogicCode::Object::refcount_ptr_elem& v, bool checkparent = true)
	{
		auto containsval = Exists(str, checkparent);
		
		if (containsval && GetTypeVariable(str,checkparent) == LogicCode::VarType::Var)
		{
			if (GetTypeVariable(str, checkparent) == LogicCode::VarType::Var)
			{
				auto invars = vars.find(str);
				if (invars != vars.end())
				{
					invars->second = v;
				}

				if (checkparent && parent)
				{
					parent->SetVar(str, v, checkparent);
				}
				
			}
		}
		else
		{
			vars[str] = v;
		}
		
	}
	void SetVar(std::string&& str, LogicCode::Object::refcount_ptr_elem&& v, bool checkparent = true)
	{
		SetVar(str, v, checkparent);
	}
	void SetVar(std::string&& str, LogicCode::Object::refcount_ptr_elem& v, bool checkparent = true)
	{
		SetVar(str, v, checkparent);
	}
};


#endif