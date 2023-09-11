#pragma once
#include "VariableData.hpp"
#include "LogicStructs.hpp"
#include "bitsetdynamic.hpp"
#include "LogicRefBitset.hpp"
#include "LogicFunctionObject.hpp"
#include "LogicUserObject.h"
namespace LogicCodeExt
{
    // scope
    void logic_scope_setvar_fnnative(LogicCodeState* L,const char* name,FunctionData::Fun fn);
    void logic_scope_setvar_integer(LogicCodeState* L, const char* name, LogicCode::LogicInteger val);
    void logic_scope_setvar_number(LogicCodeState* L, const char* name, LogicCode::LogicNumber val);
    // stack
    size_t logic_stack_len(LogicCodeState* L);

    std::bitsetdynamic* logic_stack_get_bitset(LogicCodeState* L, size_t idx);
    bool logic_stack_get_bool(LogicCodeState* L, size_t idx);
    LogicCode::LogicRefBitset* logic_stack_get_refbitset(LogicCodeState* L, size_t idx);
    LogicCode::LogicInteger logic_stack_get_integer(LogicCodeState* L, size_t idx);
    LogicCode::LogicNumber logic_stack_get_number(LogicCodeState* L, size_t idx);
    LogicCode::LogicFunctionObject* logic_stack_get_function(LogicCodeState* L, size_t idx);
    LogicCode::LogicString* logic_stack_get_string(LogicCodeState* L, size_t idx);
    LogicCode::LogicPointer logic_stack_get_pointer(LogicCodeState* L, size_t idx);
    LogicCode::LogicUserObject* logic_stack_get_userobject(LogicCodeState* L, size_t idx);

    void logic_stack_copy(LogicCodeState* L, size_t idx);

    void logic_stack_push_integer(LogicCodeState* L, LogicCode::LogicInteger val);
    void logic_stack_push_bool(LogicCodeState* L, bool val);
    void logic_stack_push_string(LogicCodeState* L, const char* val);
    void logic_stack_push_number(LogicCodeState* L, LogicCode::LogicNumber val);
    void logic_stack_push_none(LogicCodeState* L);

};

