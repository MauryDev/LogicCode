
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

	
    struct DataVar {
        bool isConst;
        LogicCode::Object::refcount_ptr_elem val;
    };
	std::refcount_ptr<VariableData> parent;
    std::unordered_map<std::string, DataVar> datavar;

	VariableData() {
		parent = {};
	}
	~VariableData() {}

	LogicCode::Object::refcount_ptr_elem GetValue(std::string& str)
	{
        auto variable = datavar.find(str);
        if (variable != datavar.end())
        {
            return variable->second.val;
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
        auto variable = datavar.find(str);
        if (variable != datavar.end())
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
        auto variable = datavar.find(str);
        if (variable != datavar.end())
        {
            return variable->second.isConst ? 
                LogicCode::VarType::Const :
                LogicCode::VarType::Var;            
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

	void SetConst(std::string& str, LogicCode::Object::refcount_ptr_elem&& v)
	{
		SetConst(str, v);
	}
	void SetConst(std::string& str, LogicCode::Object::refcount_ptr_elem& v)
	{
		if (!Exists(str, false))
		{
            datavar[str] = {true, v };
		}
	}
	void SetConst(std::string&& str, LogicCode::Object::refcount_ptr_elem&& v)
	{
		SetConst(str, v);
	}
	void SetConst(std::string&& str, LogicCode::Object::refcount_ptr_elem& v)
	{
		SetConst(str, v);
	}

	void SetVar(std::string& str, LogicCode::Object::refcount_ptr_elem&& v, bool checkparent = true)
	{
		SetVar(str, v, checkparent);
	}
	void SetVar(std::string& str, LogicCode::Object::refcount_ptr_elem& v, bool checkparent = true)
	{
        auto test = GetTypeVariable(str, false);
        if (test == LogicCode::VarType::Var || test == LogicCode::VarType::None)
        {
            datavar[str] = { false, v };

        }
        if (checkparent && parent)
        {
            parent->SetVar(str, v, checkparent);
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