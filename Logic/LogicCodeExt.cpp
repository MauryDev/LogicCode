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
    return stack.size();
}
