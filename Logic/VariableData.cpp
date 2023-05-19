#include "VariableData.h"
#include <iostream>
VariableData::VariableData()
{
    parent = NULL;
    ret = {};
}

VariableData::~VariableData()
{
    
    
}

std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic> VariableData::GetValue(std::string& str)
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
    if (parent != NULL)
    {
        return parent->GetValue(str);
    }
    return std::bitsetdynamic::refcount_ptr_elem();
}

std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic> VariableData::GetValue(std::string&& str)
{
    return GetValue(str);
}

std::refcount_ptr<FunctionData, FunctionData> VariableData::GetFunction(std::string& str, bool findfromparent)
{
    auto infunctions = functions.find(str);
    if (infunctions != functions.end())
    {
        return infunctions->second;
    }
    if (findfromparent && parent != NULL)
    {
        return parent->GetFunction(str);
    }
    return {};
}

std::refcount_ptr<FunctionData, FunctionData> VariableData::GetFunction(std::string&& str, bool findfromparent)
{
    return GetFunction(str,findfromparent);
}

void VariableData::SetFunction(std::string&& str, std::refcount_ptr<FunctionData, FunctionData>&& value)
{
    SetFunction(str, std::move(value));
}

void VariableData::SetFunction(std::string&& str, std::refcount_ptr<FunctionData, FunctionData>& value)
{
    SetFunction(str, std::move(value));
}

void VariableData::SetFunction(std::string& str, std::refcount_ptr<FunctionData, FunctionData>&& value)
{
    functions[str] = value;
}

void VariableData::SetFunction(std::string& str, std::refcount_ptr<FunctionData, FunctionData>& value)
{
    SetFunction(str, std::move(value));
}

bool VariableData::Exists(std::string& str, bool checkparent)
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

    auto infunctions = functions.find(str);
    if (infunctions != functions.end())
    {
        return true;
    }
    if (checkparent,parent != NULL)
    {
        return parent->Exists(str);
    }
    return false;
}

bool VariableData::Exists(std::string&& str, bool checkparent)
{
    return Exists(str,checkparent);
}

VariableData::VarType VariableData::GetTypeVariable(std::string& str, bool checkparent)
{
    auto invars = vars.find(str);
    if (invars != vars.end())
    {
        return VarType::Var;
    }
    auto inconsts = consts.find(str);
    if (inconsts != consts.end())
    {
        return VarType::Const;
    }
    auto infunctions = functions.find(str);
    if (infunctions != functions.end())
    {
        return VarType::Function;
    }
    if (checkparent && parent != NULL)
    {
        return parent->GetTypeVariable(str);
    }
    return VarType::None;
}

VariableData::VarType VariableData::GetTypeVariable(std::string&& str, bool checkparent)
{
    return GetTypeVariable(str,checkparent);
}

void VariableData::SetConst(std::string& str, std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic>&& v, bool checkparent)
{
    if (!Exists(str,checkparent))
    {
        consts[str] = v;
    }
}

void VariableData::SetConst(std::string& str, std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic>& v, bool checkparent)
{
    SetConst(str, std::move(v), checkparent);
}

void VariableData::SetConst(std::string&& str, std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic>&& v, bool checkparent)
{
    SetConst(str,std::move(v), checkparent);
}

void VariableData::SetConst(std::string&& str, std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic>& v, bool checkparent)
{
    SetConst(str, std::move(v), checkparent);
}

void VariableData::SetVar(std::string& str, std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic>&& v, bool checkparent)
{
    if (!Exists(str, checkparent) || GetTypeVariable(str, checkparent) == VarType::Var)
    {
        vars[str] = v;

    }
   
}

void VariableData::SetVar(std::string& str, std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic>& v, bool checkparent)
{
    SetVar(str, std::move(v), checkparent);
}

void VariableData::SetVar(std::string&& str, std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic>&& v, bool checkparent)
{
    SetVar(str, std::move(v), checkparent);
}

void VariableData::SetVar(std::string&& str, std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic>& v, bool checkparent)
{
    SetVar(str, std::move(v),checkparent);
}

void VariableData::SetRet(std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic>&& v)
{
    SetRet(v);
}

void VariableData::SetRet(std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic>& v)
{
    ret = v;

}

LogicCodeState::LogicCodeState()
{
    ret = false;
    error = NULL;
}

bool LogicCodeState::CanRun()
{
    return error == nullptr && !ret;
}

bool LogicCodeState::IsError()
{
    return error != NULL;
}
