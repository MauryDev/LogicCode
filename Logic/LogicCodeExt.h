#pragma once
#include "VariableData.hpp"
#include "LogicStructs.hpp"
namespace LogicCodeExt
{
    // scope
    void logic_scope_setvar_fnnative(LogicCodeState* L,const char* name,FunctionData::Fun fn);
    void logic_scope_setvar_integer(LogicCodeState* L, const char* name, LogicCode::LogicInteger val);
    void logic_scope_setvar_number(LogicCodeState* L, const char* name, LogicCode::LogicNumber val);
    // stack
    size_t logic_stack_len(LogicCodeState* L);

};

