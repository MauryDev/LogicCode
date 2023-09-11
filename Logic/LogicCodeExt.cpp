#include "LogicCodeExt.h"
#include "LogicObjectHelper.hpp"
using namespace LogicCode;
void LogicCodeExt::logic_scope_setvar_fnnative(LogicCodeState* L, const char* name, FunctionData::Fun fn)
{
    auto& vd = L->scope;
    vd->SetVar(name, ObjectHelper::NewFunctionNative(L, { fn }));
}

void LogicCodeExt::logic_scope_setvar_integer(LogicCodeState* L, const char* name, LogicInteger val)
{
    auto& vd = L->scope;
    vd->SetVar(name, ObjectHelper::NewInteger(val));
}

void LogicCodeExt::logic_scope_setvar_number(LogicCodeState* L, const char* name, LogicCode::LogicNumber val)
{
    auto& vd = L->scope;
    vd->SetVar(name, ObjectHelper::NewNumber(val));
}

size_t LogicCodeExt::logic_stack_len(LogicCodeState* L)
{
    auto& stack = L->stack;
    return stack.sizeoffset();
}

std::bitsetdynamic* LogicCodeExt::logic_stack_get_bitset(LogicCodeState* L, size_t idx)
{
    auto& stack = L->stack;
    auto& firststack = stack.get(idx);
    auto first = firststack ? firststack->GetBitset() : NULL;
    return first;
}

bool LogicCodeExt::logic_stack_get_bool(LogicCodeState* L, size_t idx)
{
    auto bitset = logic_stack_get_bitset(L, idx);
    return (bitset != NULL && bitset->size() > (size_t)0) ? bitset->get(0) : false;
}

LogicCode::LogicRefBitset* LogicCodeExt::logic_stack_get_refbitset(LogicCodeState* L, size_t idx)
{
    auto& stack = L->stack;
    auto& firststack = stack.get(idx);
    auto first = firststack ? LogicRefBitset::FromObject(firststack) : NULL;
    return first;
}

LogicCode::LogicInteger LogicCodeExt::logic_stack_get_integer(LogicCodeState* L, size_t idx)
{
    auto& stack = L->stack;
    auto& firststack = stack.get(idx);
    auto first = firststack ? firststack->GetInteger() : 0;
    return first;
}

LogicCode::LogicNumber LogicCodeExt::logic_stack_get_number(LogicCodeState* L, size_t idx)
{
    auto& stack = L->stack;
    auto& firststack = stack.get(idx);
    auto first = firststack ? firststack->GetNumber() : 0;
    return first;
}

LogicCode::LogicFunctionObject* LogicCodeExt::logic_stack_get_function(LogicCodeState* L, size_t idx)
{
    
    auto& stack = L->stack;
    auto& firststack = stack.get(idx);
    auto first = firststack ? LogicFunctionObject::FromObject(firststack) : NULL;
    
    return first;
}

LogicCode::LogicString* LogicCodeExt::logic_stack_get_string(LogicCodeState* L, size_t idx)
{
    auto& stack = L->stack;
    auto& firststack = stack.get(idx);
    auto first = firststack ? firststack->GetString() : NULL;
    return first;
}

LogicCode::LogicPointer LogicCodeExt::logic_stack_get_pointer(LogicCodeState* L, size_t idx)
{
    auto& stack = L->stack;
    auto& firststack = stack.get(idx);
    auto first = firststack ? firststack->GetPointer() : nullptr;
    return first;
}

LogicCode::LogicUserObject* LogicCodeExt::logic_stack_get_userobject(LogicCodeState* L, size_t idx)
{
    auto& stack = L->stack;
    auto& firststack = stack.get(idx);
    return LogicCode::LogicUserObject::FromObject(firststack);
    
}

void LogicCodeExt::logic_stack_copy(LogicCodeState* L, size_t idx)
{
    auto& stack = L->stack;
    auto& firststack = stack.get(idx);
    stack.push(firststack);
}

void LogicCodeExt::logic_stack_push_integer(LogicCodeState* L, LogicCode::LogicInteger val)
{
    auto& stack = L->stack;
    stack.push(ObjectHelper::NewInteger(val));
}

void LogicCodeExt::logic_stack_push_bool(LogicCodeState* L, bool val)
{
    auto& stack = L->stack;

    stack.push(ObjectHelper::NewBitset(val));

}

void LogicCodeExt::logic_stack_push_string(LogicCodeState* L, const char* val)
{
    auto& stack = L->stack;

    stack.push(ObjectHelper::NewString(val));
}

void LogicCodeExt::logic_stack_push_number(LogicCodeState* L, LogicCode::LogicNumber val)
{
    auto& stack = L->stack;

    stack.push(ObjectHelper::NewNumber(val));
}

void LogicCodeExt::logic_stack_push_none(LogicCodeState* L)
{
    auto& stack = L->stack;

    stack.push(ObjectHelper::New());

}


