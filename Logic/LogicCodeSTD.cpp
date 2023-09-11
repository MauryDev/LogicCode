#include "LogicCodeSTD.h"
#include "LogicCodeHelper.h"
#include <iostream>
#include <iomanip>
#include "refcount_ptr.hpp"
#include <cmath>
#include "LogicObjectHelper.hpp"
#include "LogicFunctionData.hpp"
#include "LogicCodeExt.h"
#include <Windows.h>
#include "LogicDebug.h"
#include <algorithm>
#include "BitExtenderConfig.h"
#include "Shifter.h"
#include "BitFinder.h"
#include "BitAdder.h"
#include "Comparator.h"

using namespace LogicCodeExt;

int LogicCode::Std::And(LogicCodeState* L)
{
    auto& stack = L->stack;
    auto& scope = L->scope;
    auto len = logic_stack_len(L);
    if (len > 0)
    {

        auto first = logic_stack_get_bitset(L, 0);
        if (first != NULL)
        {
            
            auto retv = ObjectHelper::CopyBitset(first);

            auto sizeinput = retv->size();

            for (size_t i = 1; i < len; i++)
            {
                auto current = logic_stack_get_bitset(L, i);
                if (current != NULL && current->size() == sizeinput)
                {
                    for (size_t i = 0; i < sizeinput; i++)
                    {
                        retv->set(i, retv->get(i) && current->get(i));
                    }
                }
                else
                {
                    return 0;
                }
            }
            L->stack.push(retv);
            return 1;
        }

    }
    return 0;
}

int LogicCode::Std::Or(LogicCodeState* L)
{
    auto& stack = L->stack;
    auto& scope = L->scope;
    auto len = logic_stack_len(L);
    if (len > 0)
    {
        auto first = logic_stack_get_bitset(L, 0);
        if (first != NULL)
        {
            auto retv = ObjectHelper::CopyBitset(first);
            auto sizeinput = retv->size();

            for (size_t i = 1; i < len; i++)
            {
                auto current = logic_stack_get_bitset(L, i);
                if (current && current->size() == sizeinput)
                {
                    for (size_t i = 0; i < sizeinput; i++)
                    {
                        retv->set(i, retv->get(i) || current->get(i));
                    }
                }
                else
                {
                    return 0;
                }
            }
            stack.push(retv);
            return 1;
        }


    }
    return 0;

}


int LogicCode::Std::Not(LogicCodeState* L)
{
    auto& stack = L->stack;
    auto& scope = L->scope;
    auto len = logic_stack_len(L);
    if (len == 1)
    {

        auto first = logic_stack_get_bitset(L, 0);
        if (first != NULL)
        {
            auto retv = ObjectHelper::CopyBitset(first);

            auto sizeinput = retv->size();

            for (size_t i = 0; i < sizeinput; i++)
            {
                retv->set(i, !retv->get(i));
            }
            stack.push(retv);
            return 1;
        }


    }
    return 0;
}

int LogicCode::Std::Xor(LogicCodeState* L)
{
    auto& stack = L->stack;
    auto& scope = L->scope;
    auto len = logic_stack_len(L);
    if (len > 0)
    {
        auto first = logic_stack_get_bitset(L, 0);
        if (first != NULL)
        {
            auto retv = ObjectHelper::CopyBitset(first);

            auto sizeinput = retv->size();

            for (size_t i = 1; i < len; i++)
            {
                auto current = logic_stack_get_bitset(L, i);
                if (current != NULL && current->size() == sizeinput)
                {
                    for (size_t i = 0; i < sizeinput; i++)
                    {
                        retv->set(i, retv->get(i) != current->get(i));
                    }
                }
                else
                {
                    return 0;
                }
            }
            stack.push(retv);
            return 1;
        }


    }
    return 0;
}

int LogicCode::Std::Nand(LogicCodeState* L)
{
    auto& stack = L->stack;
    auto& scope = L->scope;
    auto len = logic_stack_len(L);
    if (len > 0)
    {
        auto first = logic_stack_get_bitset(L, 0);
        if (first != NULL)
        {
            auto retv = ObjectHelper::CopyBitset(first);

            auto sizeinput = retv->size();

            for (size_t i = 1; i < len; i++)
            {
                auto current = logic_stack_get_bitset(L, i);
                if (current != NULL && current->size() == sizeinput)
                {
                    for (size_t i = 0; i < sizeinput; i++)
                    {
                        retv->set(i, retv->get(i) && current->get(i));
                    }
                }
                else
                {
                    return 0;
                }
            }
            for (size_t i = 0; i < sizeinput; i++)
            {
                retv->set(i, !retv->get(i));
            }
            stack.push(retv);
            return 1;


        }

    }
    return 0;
}

int LogicCode::Std::Nor(LogicCodeState* L)
{
    auto& stack = L->stack;
    auto& scope = L->scope;
    auto len = logic_stack_len(L);
    if (len > 0)
    {

        auto first = logic_stack_get_bitset(L, 0);
        if (first != NULL)
        {
            auto retv = ObjectHelper::CopyBitset(first);

            auto sizeinput = retv->size();

            for (size_t i = 1; i < len; i++)
            {
                auto current = logic_stack_get_bitset(L, i);
                if (current->size() == sizeinput)
                {
                    for (size_t i = 0; i < sizeinput; i++)
                    {
                        retv->set((int)i, retv->get(i) || current->get(i));
                    }
                }
                else
                {
                    return 0;
                }
            }
            for (size_t i = 0; i < sizeinput; i++)
            {
                retv->set(i, !retv->get(i));
            }
            stack.push(retv);
            return 1;
        }



    }
    return 0;
}

int LogicCode::Std::Xnor(LogicCodeState* L)
{
    auto& stack = L->stack;
    auto& scope = L->scope;
    auto len = logic_stack_len(L);
    if (len > 0)
    {

        auto first = logic_stack_get_bitset(L, 0);
        if (first != NULL)
        {
            auto retv = ObjectHelper::CopyBitset(first);

            auto sizeinput = retv->size();

            for (size_t i = 1; i < len; i++)
            {
                auto current = logic_stack_get_bitset(L, i);
                if (current->size() == sizeinput)
                {
                    for (size_t i = 0; i < sizeinput; i++)
                    {
                        retv->set(i, retv->get(i) != current->get(i));
                    }
                }
                else
                {
                    return 0;
                }
            }
            for (size_t i = 0; i < sizeinput; i++)
            {
                retv->set(i, !retv->get(i));
            }
            stack.push(retv);
            return 1;
        }



    }
    return 0;
}

int LogicCode::Std::If(LogicCodeState* L, Light::List& current)
{
    auto instructionsize = current.get_Count();

    if (instructionsize == 3)
    {

        auto arg1 = Helper::ToObjectFromCommand(L, current[1]);
        auto arg1bitset = arg1->GetBitset();
        if (!L->CanRun())
        {
            if (!L->IsError())
            {
                return _Error(L, "Don't use return in 'if'");
            }
            else {
                return 0;
            }
        }
        if (!arg1 || arg1bitset->size() == 0)
        {
            return _Error(L, "NULL Value or size == 0");
        }
        auto condition = arg1bitset->get(0);

        auto exp = current[2].expression;
        if (condition)
        {
            return Helper::ExecuteInstuctionShared(L, *exp);
        }
        else
        {
            return 0;
        }


    }
    else if (instructionsize == 5)
    {


        auto arg1 = Helper::ToObjectFromCommand(L, current[1]);
        auto arg1bitset = arg1->GetBitset();
        if (!L->CanRun())
        {
            if (!L->IsError())
            {
                return _Error(L, "Don't use return in 'if'");
            }
            else
            {
                return 0;
            }
        }
        if (!arg1 || arg1bitset->size() == 0)
        {
            return _Error(L, "NULL Value or size == 0");
        }

        auto exp = current[2].instruction;
        auto _else = current[3].str;
        auto exp2 = current[4].instruction;
        if (_else->Equals("else"))
        {
            auto condition = arg1bitset->get(0);
            if (condition)
            {
                return Helper::ExecuteInstuctionShared(L, *exp);
            }
            else
            {
                return Helper::ExecuteInstuctionShared(L, *exp2);

            }
        }
        else
        {
            return _Error(L, "Expected 'else'");
        }

    }
    else
    {
        return _Error(L, "Syntax error: arguments don't match");
    }
}

int LogicCode::Std::While(LogicCodeState* L, Light::List& current)
{
    auto instructionsize = current.get_Count();

    if (instructionsize == 3)
    {
        auto arg1 = Helper::ToObjectFromCommand(L, current[1]);
        auto arg1bitset = arg1->GetBitset();
        if (!L->CanRun())
        {
            if (!L->IsError())
            {
                _Error(L, "Don't use return in 'while'");
            }
            else
            {
                return 0;
            }
        }
        if (!arg1 || arg1bitset->size() == 0)
        {
            return _Error(L, "NULL Value or size == 0");
        }
        auto exp = current[2].instruction;

        auto condition = arg1bitset->get(0);
        int len = 0;
        while (condition)
        {
            len = Helper::ExecuteInstuctionShared(L, *exp);
            if (L->ret)
            {
                return len;
            }
            arg1 = Helper::ToObjectFromCommand(L, current[1]);
            arg1bitset = arg1->GetBitset();
            if (!arg1 || arg1bitset->size() == 0)
            {
                return _Error(L, "NULL Value or size == 0");
            }
            condition = arg1bitset->get(0);

        }
        return 0;
    }

    else
    {
        return _Error(L, "Syntax error: arguments don't match");
    }
}

int LogicCode::Std::Fun(LogicCodeState* L, Light::List& current)
{
    auto instructionsize = current.get_Count();
    if (instructionsize == 4)
    {
        auto fnname = current[1].str;

        auto argsname = current[2].expression;
        auto argscount = argsname->get_Count();

        auto fnobj = ObjectHelper::NewFunctionRuntime(L, {});
        auto& fruntime = fnobj.ToPtr()->get_runtimefn();

        fruntime.body = current[3].instruction;

        for (size_t i = 0; i < argscount; i++)
        {
            fruntime.argsname.push_back(argsname->at(i)[0].str->data());
        }

        L->scope->SetVar(fnname->data(), fnobj);
        return 0;
    }
    // fun <expression> <instruction>
    else if (instructionsize == 3)
    {
        auto argsname = current[1].expression;
        auto argscount = argsname->get_Count();

        auto fnobj = ObjectHelper::NewFunctionRuntime(L, {});
        auto& fruntime = fnobj.ToPtr()->get_runtimefn();

        fruntime.body = current[2].instruction;

        for (size_t i = 0; i < argscount; i++)
        {
            fruntime.argsname.push_back(argsname->at(i)[0].str->data());
        }
        L->stack.push(fnobj);
        return 1;
    }
    return 0;
}

int LogicCode::Std::Return(LogicCodeState* L, Light::List& current)
{
    auto instructionsize = current.get_Count();
    if (instructionsize >= 2)
    {
        auto lenlist = instructionsize - 1;
        Light::List values(lenlist, lenlist, &current.at(1));

        auto v2 = Helper::PushList(L, values);
        if (!L->CanRun())
        {
            if (!L->IsError())
            {
                L->error = "Don't use return in 'return'";
            }
            else
            {
                return 0;
            }
            return 0;
        }

        L->ret = true;
        return v2;
    }
    else
    {
        return 0;

    }
}

int LogicCode::Std::Print(LogicCodeState* L)
{
    auto& stack = L->stack;
    auto& scope = L->scope;
    auto len = logic_stack_len(L);

    if (len >= 1)
    {

        for (size_t i = 0; i < len; i++)
        {
            if (i > 0)
            {
                std::cout << " ";

            }
            _Print(stack.get(i));

        }

        std::cout << std::endl;

    }
    return 0;
}

void LogicCode::Std::_Print(Object::refcount_ptr_elem& obj)
{
    if (!obj || obj->CheckType(ObjectType::None))
    {
        std::cout << "None";
    }
    else if (obj->CheckType(ObjectType::Bitset))
    {
        auto result = obj->GetBitset();
        std::cout << result->to_string();
    }
    else if (obj->CheckType(ObjectType::Integer))
    {
        auto result = obj->GetInteger();
        std::cout << result;
    }
    else if (obj->CheckType(ObjectType::Number))
    {
        auto result = obj->GetNumber();
        std::cout << result;
    }
    else if (obj->CheckType(ObjectType::RefBitset))
    {

        std::cout << "Reference: " << obj.get();
    }
    else if (obj->CheckType(ObjectType::String))
    {
        auto result = obj->GetString();
        std::cout.write(result->txt, result->size);
    }
    else if (obj->CheckType(ObjectType::Function))
    {

        std::cout << "Function: " << obj.get();
    }
    else if (obj->CheckType(ObjectType::UserObject))
    {

        std::cout << "UserObject: " << obj.get();
    }
    else if (obj->CheckType(ObjectType::Pointer))
    {

        std::cout << obj->GetPointer();
    }
}

void LogicCode::Std::_Debug_Log(Object::refcount_ptr_elem& obj)
{
    if (!obj || obj->CheckType(ObjectType::None))
    {
        LogicDebug::Log("None");
    }
    else if (obj->CheckType(ObjectType::Bitset))
    {
        auto result = obj->GetBitset();

        auto str = result->to_string();
        LogicDebug::Log(str.c_str());


    }
    else if (obj->CheckType(ObjectType::Integer))
    {
        auto result = obj->GetInteger();
        std::string varAsString = std::to_string(result);
        LogicDebug::Log(varAsString.c_str());

    }
    else if (obj->CheckType(ObjectType::Number))
    {
        auto result = obj->GetNumber();

        std::string varAsString = std::to_string(result);
        LogicDebug::Log(varAsString.c_str());


    }
    else if (obj->CheckType(ObjectType::RefBitset))
    {
        char str[30] = {};
        auto num = (LogicInteger)obj.get();
        _i64toa_s(num, str, 30, 16);

        LogicDebug::Log("Reference: ");
        LogicDebug::Log(str);

    }
    else if (obj->CheckType(ObjectType::String))
    {
        auto result = obj->GetString();
        LogicDebug::Log(result->txt);
    }
    else if (obj->CheckType(ObjectType::Function))
    {
        char str[21] = {};
        auto num = (LogicInteger)obj.get();
        _i64toa_s(num, str, 21, 16);

        LogicDebug::Log("Function: ");
        LogicDebug::Log(str);
    }
    else if (obj->CheckType(ObjectType::UserObject))
    {

        char str[21] = {};
        auto num = (LogicInteger)obj.get();
        _i64toa_s(num, str, 21, 16);

        LogicDebug::Log("UserObject: ");
        LogicDebug::Log(str);
    }
    else if (obj->CheckType(ObjectType::Pointer))
    {
        char str[21] = {};
        auto num = (LogicInteger)obj->GetPointer();
        _i64toa_s(num, str, 21, 16);
        LogicDebug::Log(str);

    }
}

int LogicCode::Std::Debug_Log(LogicCodeState* L)
{
    auto& stack = L->stack;
    auto& scope = L->scope;
    auto len = logic_stack_len(L);

    if (len >= 1)
    {

        for (size_t i = 0; i < len; i++)
        {
            if (i > 0)
            {
                LogicDebug::Log(" ");

            }
            _Debug_Log(stack.get(i));

        }
        LogicDebug::Log("\n");
    }
    return 0;
}

int LogicCode::Std::Debug_Clear(LogicCodeState* state)
{
    LogicDebug::Clear();
    return 0;
}


int LogicCode::Std::Const(LogicCodeState* L, Light::List& current)
{
    auto instructionsize = current.get_Count();

    if (instructionsize >= 4)
    {
        auto name = current[1].str;
        auto& type = current[2];

        if (type.resultType == Light::ResultType::Operador)
        {
            if (*type.coperator == Light::COperator::Set)
            {
                auto lenlist = instructionsize - 3;
                Light::List values(lenlist, lenlist, &current.at(3));
                auto v2 = Helper::ToBitSetFromList(L, values);
                if (!L->CanRun())
                {
                    if (!L->IsError())
                    {
                        L->error = "Don't use return in 'const'";
                    }
                    else
                    {
                        return 0;
                    }
                    return 0;
                }
                L->scope->SetConst(name->data(), v2);
            }
        }
    }
    return 0;
}

int LogicCode::Std::Var(LogicCodeState* L, Light::List& current)
{
    auto instructionsize = current.get_Count();

    if (instructionsize >= 4)
    {
        auto name = current[1].str;
        auto& type = current[2];

        if (type.resultType == Light::ResultType::Operador)
        {
            if (*type.coperator == Light::COperator::Set)
            {
                auto lenlist = instructionsize - 3;
                Light::List values(lenlist, lenlist, &current.at(3));
                auto v2 = Helper::ToBitSetFromList(L, values);
                if (!L->CanRun())
                {
                    if (!L->IsError())
                    {
                        L->error = "Don't use return in 'var'";
                    }
                    else
                    {
                        return 0;
                    }
                    return 0;
                }
                L->scope->SetVar(name->data(), v2, false);
            }
        }
    }
    return 0;
}

int LogicCode::Std::Case(LogicCodeState* L, Light::List& current)
{
    auto instructionsize = current.get_Count();

    if (instructionsize == 4)
    {
        auto bits = Helper::ToObjectFromCommand(L, current[1]);
        auto bits_ = bits->GetBitset();
        if (!L->CanRun())
        {
            if (!L->IsError())
            {
                _Error(L, "Don't use return in 'case'");
            }
            else
            {
                return 0;
            }
            return 0;
        }
        if (!bits || bits_->size() == 0)
        {
            return _Error(L, "NULL or zero size");
        }
        auto condition = bits_->get(0);
        if (condition)
        {
            return Helper::PushCommand(L, current[2]);
        }
        else
        {
            return Helper::PushCommand(L, current[3]);
        }


    }
    return 0;
}

int LogicCode::Std::Buffer(LogicCodeState* L)
{
    auto& stack = L->stack;
    auto& scope = L->scope;
    auto len = logic_stack_len(L);
    if (len == 1)
    {
        auto first = logic_stack_get_bitset(L, 0);
        if (first != NULL)
        {
            auto bitset = ObjectHelper::CopyBitset(first);
            stack.push(bitset);

        }

        return 1;

    }
    return 0;
}

int LogicCode::Std::Zero(LogicCodeState* L)
{
    auto& stack = L->stack;
    auto& scope = L->scope;
    auto len = logic_stack_len(L);
    if (len == 1)
    {

        auto first = logic_stack_get_integer(L, 0);
        auto ret = ObjectHelper::NewBitset((size_t)first);
        for (uint8_t i = 0; i < first; i++)
        {
            ret->set(i, false);
        }
        stack.push(ret);
        return 1;

    }
    return 0;
}

int LogicCode::Std::One(LogicCodeState* L)
{
    auto& stack = L->stack;
    auto& scope = L->scope;
    auto len = logic_stack_len(L);
    if (len == 1)
    {

        auto first = logic_stack_get_integer(L, 0);
        auto ret = ObjectHelper::NewBitset((size_t)first);
        for (LogicInteger i = 0; i < first; i++)
        {
            ret->set(i, true);
        }
        stack.push(ret);
        return 1;

    }
    return 0;
}


int LogicCode::Std::Intv(LogicCodeState* L, Light::List& current)
{
    auto instructionsize = current.get_Count();

    if (instructionsize == 2)
    {
        auto numi8 = current[1].str;

        LogicInteger num = (LogicInteger)std::strtoll(numi8->data(), nullptr, 10);
        auto val = ObjectHelper::NewInteger(num);
        L->stack.push(val);
        return 1;
    }
    return 0;
}

int LogicCode::Std::Numv(LogicCodeState* L, Light::List& current)
{
    auto instructionsize = current.get_Count();

    if (instructionsize == 2)
    {
        auto numi8 = current[1].str;
        LogicNumber num = (LogicNumber)strtod(numi8->data(), nullptr);
        auto val = ObjectHelper::NewNumber(num);
        L->stack.push(val);
        return 1;
    }
    return 0;
}

int LogicCode::Std::Ref(LogicCodeState* L, Light::List& current)
{
    auto instructionsize = current.get_Count();

    if (instructionsize == 2)
    {
        auto bits = current[1].str;

        auto v = ObjectHelper::NewRefBitset(bits->data(), L->scope);
        L->stack.push(v);

        return 1;
    }
    return 0;
}


int LogicCode::Std::Mux(LogicCodeState* L)
{
    auto& stack = L->stack;
    auto& scope = L->scope;
    auto len = logic_stack_len(L);
    if (len >= 2)
    {

        auto selectbitset = logic_stack_get_integer(L, 0);

        auto lenargs = len - 1;
        if (selectbitset < lenargs)
        {
            auto& selected = stack.get(selectbitset + 1);
            stack.push(selected);
            return 1;
        }

    }
    return 0;
}

int LogicCode::Std::Demux(LogicCodeState* L)
{
    auto& stack = L->stack;
    auto& scope = L->scope;
    auto len = logic_stack_len(L);
    if (len >= 3)
    {

        auto selectbitset = logic_stack_get_integer(L, 0);

        auto& value = stack.get(1);


        auto lenargs = len - 2;
        if (selectbitset < lenargs)
        {
            auto refbitset = logic_stack_get_refbitset(L, selectbitset + 2);
            if (refbitset != NULL) {
                refbitset->SetValue(value);
            }
            return 0;
        }

    }
    return 0;
}

int LogicCode::Std::Decoder(LogicCodeState* L)
{
    auto& stack = L->stack;
    auto& scope = L->scope;
    auto len = logic_stack_len(L);
    if (len >= 2)
    {

        auto selectbits = logic_stack_get_integer(L, 0);


        auto lenargs = len - 1;
        if (selectbits < lenargs)
        {

            auto ret = ObjectHelper::NewBitset(true);

            auto refbitset = logic_stack_get_refbitset(L, selectbits + 1);
            if (refbitset != NULL)
            {
                refbitset->SetValue(ret);
            }

            return 0;
        }

    }
    return 0;
}

int LogicCode::Std::BitSelector(LogicCodeState* L)
{
    auto len = logic_stack_len(L);
    if (len == 2)
    {
        auto bits = logic_stack_get_bitset(L, 0);

        auto selectbits = logic_stack_get_integer(L, 1);

        if (bits != NULL)
        {
            auto bitssize = bits->size();
            if (selectbits < bitssize)
            {
                logic_stack_push_bool(L, bits->get(selectbits));
                return 1;
            }

        }

    }
    return 0;
}

int LogicCode::Std::PriorityDecoder(LogicCodeState* L)
{
    auto len = logic_stack_len(L);
    if (len >= 1)
    {
        auto selectbit = logic_stack_get_integer(L, 0);
        auto max = (size_t)std::pow(2, selectbit);
        auto argsprioprity = len - 1;
        size_t maxarg = std::clamp(argsprioprity, (size_t)0, max);
        auto restante = max - maxarg;
        bool okret = false;
        auto bitsetret = ObjectHelper::NewBitset((size_t)selectbit);
        for (size_t i = 0; i < selectbit; i++)
        {
            bitsetret->set(i, true);
        }
        for (size_t i = 0; i < restante; i++)
        {
            __Dec(bitsetret.ToPtr());
        }
        for (size_t i = maxarg; i > 0; i--)
        {
            auto enable = logic_stack_get_bool(L, i);
            if (enable)
            {
                okret = true;
                break;
            }
            __Dec(bitsetret.ToPtr());

        }
        if (okret)
        {
            L->stack.push(bitsetret);
            return 1;
        }
        
    }
    return 0;
}

int LogicCode::Std::Add(LogicCodeState* L)
{
    auto& stack = L->stack;
    auto& scope = L->scope;
    auto len = logic_stack_len(L);
    if (len == 2)
    {

        auto value1 = logic_stack_get_bitset(L, 0);
        auto value2 = logic_stack_get_bitset(L, 1);
        if (value1 != NULL && value2 != NULL) {
            auto value1size = value1->size();
            auto value2size = value2->size();
            if (value1size == value2size)
            {
                auto result = ObjectHelper::NewBitset(value1size);

                auto CarryIn = false;
                for (size_t i = 0; i < value1size; i++)
                {
                    auto A = value1->get(i);
                    auto B = value2->get(i);
                    auto CarryOut = A && B || CarryIn && B || CarryIn && A;
                    auto C = !CarryIn && !A && B || !CarryIn && A && !B || CarryIn && !A && !B || CarryIn && A && B;


                    result->set(i, C);
                    CarryIn = CarryOut;

                }

                stack.push(result);
                return 1;
            }
        }


    }

    return 0;


}

int LogicCode::Std::Sub(LogicCodeState* L)
{
    auto& stack = L->stack;
    auto& scope = L->scope;
    auto len = logic_stack_len(L);
    if (len == 2)
    {
        auto value1 = logic_stack_get_bitset(L, 0);
        auto value2 = logic_stack_get_bitset(L, 1);
        if (value1 != NULL && value2 != NULL)
        {
            auto value1size = value1->size();
            auto value2size = value2->size();
            if (value1size == value2size)
            {
                auto result = ObjectHelper::NewBitset(value1size);


                auto BorrowIn = false;
                for (size_t i = 0; i < value1size; i++)
                {
                    auto A = value1->get(i);
                    auto B = value2->get(i);
                    auto C = !BorrowIn && !A && B || !BorrowIn && A && !B || BorrowIn && !A && !B || BorrowIn && A && B;
                    auto BorrowOut = !A && B || BorrowIn && !A || BorrowIn && B;
                    result->set(i, C);

                    BorrowIn = BorrowOut;
                }

                stack.push(result);
                return 1;
            }
        }


    }

    return 0;
}

int LogicCode::Std::Mul(LogicCodeState* L)
{
    auto& stack = L->stack;
    auto& scope = L->scope;
    auto len = logic_stack_len(L);
    if (len == 2)
    {
        auto value1 = logic_stack_get_bitset(L, 0);
        auto value2 = logic_stack_get_bitset(L, 1);
        if (value1 != NULL && value2 != NULL)
        {
            auto value1size = value1->size();
            auto value2size = value2->size();
            if (value1size == value2size)
            {
                auto mulresult = value1size * 2;
                auto result = ObjectHelper::NewBitset(mulresult);
                auto temp = ObjectHelper::NewBitset(value1size);
                for (size_t i = 0; i < value1size; i++)
                {
                    auto bitcurrent2 = value2->get(i);
                    for (size_t i2 = 0; i2 < value1size; i2++)
                    {
                        auto bitcurrent1 = value1->get(i2);
                        temp->set(i2, bitcurrent2 && bitcurrent1);
                    }
                    auto CarryIn = false;

                    for (size_t i2 = 0; i2 < value1size; i2++)
                    {
                        auto A = temp->get(i2);
                        auto B = result->get(i2 + i);
                        result->set(i2 + i, !A && !B && CarryIn ||
                            !A && B && !CarryIn ||
                            A && !B && !CarryIn ||
                            A && B && CarryIn);

                        CarryIn = B && CarryIn ||
                            A && CarryIn ||
                            A && B;

                    }
                    result->set(i + value1size, CarryIn);

                }
                stack.push(result);
                return 1;
            }
        }
    }
    return 0;
}

int LogicCode::Std::Div(LogicCodeState* L)
{
    auto& stack = L->stack;
    auto& scope = L->scope;
    auto len = logic_stack_len(L);
    if (len >= 2)
    {
        auto value1 = logic_stack_get_bitset(L, 0);
        auto value2 = logic_stack_get_bitset(L, 1);
        if (value1 != NULL && value2 == NULL)
        {
            auto value1size = value1->size();
            auto value2size = value2->size();
            if (value1size == value2size)
            {
                int sizev1 = 0, sizev2 = 0;
                for (size_t i = 0; i < value1size; i++)
                {
                    auto currentvalue1 = value1->get(i);
                    auto currentvalue2 = value2->get(i);

                    if (currentvalue1)
                    {
                        sizev1 = i + 1;
                    }
                    if (currentvalue2)
                    {
                        sizev2 = i + 1;
                    }

                }
                if (sizev2 != 0)
                {
                    if (sizev1 == 0 || sizev2 > sizev1)
                    {
                        auto retv = ObjectHelper::NewBitset(value1size);
                        stack.push(retv);
                        return 1;
                    }

                    auto equalsdivsize = sizev2 == sizev1;
                    auto remainder = ObjectHelper::NewBitset(value1size);
                    auto quotient = ObjectHelper::NewBitset(value1size);
                    auto tempsize = equalsdivsize ? (size_t)sizev2 : (size_t)sizev2 + 1;
                    auto temp = std::bitsetdynamic::Make(tempsize);

                    size_t i = (equalsdivsize ? 0 : sizev1 - sizev2) + 1;

                    auto copyv = equalsdivsize ? tempsize : tempsize - 1;
                    auto startbound = equalsdivsize ? 0 : sizev1 - sizev2;
                    for (size_t i2 = 0; i2 < copyv; i2++)
                    {
                        remainder->set(i2, value1->get(startbound + i2));
                    }

                    while (i > 0)
                    {
                        auto iv = i - 1;
                        bool BorrowIn = false;
                        for (size_t i2 = 0; i2 < tempsize; i2++)
                        {
                            auto A = remainder->get(i2);
                            auto B = value2->get(i2);
                            auto C = !BorrowIn && !A && B || !BorrowIn && A && !B || BorrowIn && !A && !B || BorrowIn && A && B;
                            auto BorrowOut = !A && B || BorrowIn && !A || BorrowIn && B;
                            temp->set(i2, C);

                            BorrowIn = BorrowOut;


                        }

                        if (!BorrowIn)
                        {
                            for (size_t i2 = 0; i2 < tempsize; i2++)
                            {
                                remainder->set(i2, temp->get(i2));
                            }
                        }


                        for (size_t i2 = value1size; i2 > 1; i2--)
                        {
                            quotient->set(i2 - 1, quotient->get(i2 - 2));
                        }
                        quotient->set(0, !BorrowIn);
                        if (i > 1)
                        {
                            for (size_t i2 = tempsize; i2 > 1; i2--)
                            {
                                remainder->set(i2 - 1, remainder->get(i2 - 2));
                            }
                            remainder->set(0, value1->get(iv - 1));
                        }
                        i--;

                    }

                    if (len >= 3)
                    {
                        auto value_selected = stack.get(2).get();
                        auto refbitsett = LogicRefBitset::FromObject(value_selected);
                        refbitsett->SetValue(remainder);
                    }
                    stack.push(quotient);
                    return 1;
                }


                return _Error(L, "Division by zero");
            }
        }


    }
    return 0;
}

int LogicCode::Std::Negator(LogicCodeState* L)
{
    auto len = logic_stack_len(L);
    if (len == 1)
    {
        auto value1 = logic_stack_get_bitset(L, 0);
        if (value1 != NULL)
        {
            auto lenvalue = value1->size();
            auto vret = ObjectHelper::CopyBitset(value1);
            if (lenvalue > 1)
            {
                for (size_t i = 0; i < lenvalue; i++)
                {
                    vret->set(i, !vret->get(i));
                }
                __Inc(vret.ToPtr());
            }
            L->stack.push(vret);
            return 1;
        }
    }
    return 0;
}

int LogicCode::Std::GetType(LogicCodeState* L)
{
    auto& stack = L->stack;
    auto& scope = L->scope;
    auto len = logic_stack_len(L);
    if (len == 1)
    {
        auto& first = stack.get(0);
        const char* v = "None";
        switch (first->type)
        {
        case ObjectType::Bitset:
            v = "Bitset";
            break;
        case ObjectType::String:
            v = "String";
            break;
        case ObjectType::Number:
            v = "Number";
            break;
        case ObjectType::RefBitset:
            v = "RefBitset";
            break;
        case ObjectType::Integer:
            v = "Integer";
            break;
        case ObjectType::Function:
            v = "Function";
            break;
        }
        stack.push(ObjectHelper::NewString(v));
        return 1;
    }
    return 0;
}

int LogicCode::Std::IsNone(LogicCodeState* L)
{
    auto& stack = L->stack;
    auto& scope = L->scope;
    auto len = logic_stack_len(L);
    if (len == 1)
    {
        auto& first = stack.get(0);
        auto isnone = first ? first->type == ObjectType::None : true;
        logic_stack_push_bool(L, isnone);

        return 1;
    }
    return 0;
}

int LogicCode::Std::Argslen(LogicCodeState* L)
{
    logic_stack_push_integer(L, logic_stack_len(L));
    return 1;
}


int LogicCode::Std::TruthTable(LogicCodeState* L)
{
    auto len = logic_stack_len(L);
    if (len >= 2)
    {
        // 0 fun , 1 argslen
        auto fn = logic_stack_get_function(L, 0);
        auto lenargs = logic_stack_get_integer(L, 1);

        if (fn != NULL)
        {

            auto looplen = pow(2,lenargs);
            auto inputs = std::bitsetdynamic::Make((size_t)lenargs);




            for (size_t i = 0; i < looplen; i++)
            {
                for (size_t i2 = 0; i2 < lenargs; i2++)
                {
                    auto currentv = inputs->get(i2);
                    logic_stack_push_bool(L, currentv);

                }
                logic_stack_copy(L, 0);
                Helper::CallFunction(L, lenargs, 0);



                __Inc(inputs.get());

            }
        }
    }
    return 0;
}

int LogicCode::Std::ControlledBuffer(LogicCodeState* L)
{
    auto& stack = L->stack;
    auto& scope = L->scope;
    auto len = logic_stack_len(L);
    if (len >= 2)
    {
        auto bitset1 = logic_stack_get_bitset(L, 0);
        auto enable = logic_stack_get_bitset(L, 1);

        if (bitset1 != NULL && enable != NULL)
        {

            if (enable->get(0))
            {
                auto ret = ObjectHelper::CopyBitset(bitset1);

                stack.push(ret);
            }
            else
            {
                auto ret = ObjectHelper::New();
                stack.push(ret);

            }
            return 1;


        }
    }
    return 0;
}

int LogicCode::Std::ControlledInverter(LogicCodeState* L)
{
    auto& stack = L->stack;
    auto& scope = L->scope;
    auto len = logic_stack_len(L);
    if (len >= 2)
    {
        auto bitset1 = logic_stack_get_bitset(L, 0);
        auto enable = logic_stack_get_bitset(L, 1);

        if (bitset1 != NULL && enable != NULL)
        {

            if (enable->get(0))
            {
                auto size = bitset1->size();
                auto ret = ObjectHelper::NewBitset(size);
                for (size_t i = 0; i < size; i++)
                {
                    ret->set(i, !bitset1->get(i));
                }
                stack.push(ret);
            }
            else
            {
                auto ret = ObjectHelper::New();
                stack.push(ret);
            }
            return 1;


        }
    }
    return 0;
}

int LogicCode::Std::OddParity(LogicCodeState* L)
{
    auto& stack = L->stack;
    auto& scope = L->scope;
    auto len = logic_stack_len(L);
    if (len >= 1)
    {
        auto firstval = logic_stack_get_bitset(L, 0);

        if (firstval != NULL)
        {
            auto valsize = firstval->size();
            auto ret = ObjectHelper::CopyBitset(firstval);

            for (size_t i = 1; i < len; i++)
            {

                auto currentbitset = logic_stack_get_bitset(L, i);
                if (currentbitset != NULL)
                {
                    auto currentbitsetlen = currentbitset->size();
                    if (currentbitsetlen == valsize)
                    {
                        for (size_t i2 = 0; i2 < valsize; i2++)
                        {
                            auto old = ret->get(i2);
                            auto newvalue = old != currentbitset->get(i2);
                            ret->set(i2, newvalue);
                        }
                    }
                }
            }


            stack.push(ret);
            return 1;
        }
    }
    return 0;
}

int LogicCode::Std::EvenParity(LogicCodeState* L)
{
    auto& stack = L->stack;
    auto& scope = L->scope;
    auto len = logic_stack_len(L);
    if (len >= 1)
    {
        auto firstval = logic_stack_get_bitset(L, 0);


        if (firstval != NULL)
        {
            auto valsize = firstval->size();
            auto ret = ObjectHelper::NewBitset(valsize);
            for (size_t i = 0; i < valsize; i++)
            {
                ret->set(i, !firstval->get(i));
            }
            for (size_t i = 1; i < len; i++)
            {
                auto currentbitset = logic_stack_get_bitset(L, i);
                if (currentbitset != NULL)
                {
                    auto currentbitsetlen = currentbitset->size();
                    if (currentbitsetlen == valsize)
                    {
                        for (size_t i2 = 0; i2 < valsize; i2++)
                        {
                            auto old = ret->get(i2);
                            auto newvalue = old != currentbitset->get(i2);
                            ret->set(i2, newvalue);
                        }
                    }
                }
            }


            stack.push(ret);
            return 1;
        }
    }
    return 0;
}

int LogicCode::Std::function_isNative(LogicCodeState* L)
{
    auto len = logic_stack_len(L);
    if (len == 1)
    {
        auto fn = logic_stack_get_function(L, 0);

        if (fn != NULL)
        {
            auto isnative = fn->type == FunctionData::FunctionType::Native;
            logic_stack_push_bool(L, isnative);

            return 1;

        }
    }
    return 0;
}

int LogicCode::Std::function_isRuntime(LogicCodeState* L)
{
    auto len = logic_stack_len(L);
    if (len == 1)
    {
        auto fn = logic_stack_get_function(L, 0);
        if (fn != NULL)
        {
            auto isruntime = fn->type == FunctionData::FunctionType::Runtime;
            logic_stack_push_bool(L, isruntime);

            return 1;

        }
    }
    return 0;
}

int LogicCode::Std::function_argslen(LogicCodeState* L)
{
    auto len = logic_stack_len(L);
    if (len == 1)
    {
        auto fn = logic_stack_get_function(L, 0);
        if (fn != NULL)
        {

            auto isruntime = fn->type == FunctionData::FunctionType::Runtime;
            if (isruntime)
            {
                auto& fnruntime = fn->get_runtimefn();
                logic_stack_push_integer(L, fnruntime.argsname.size());

            }
            else
            {
                logic_stack_push_integer(L, -1);
            }
            return 1;

        }
    }
    return 0;
}

int LogicCode::Std::function_getargname(LogicCodeState* L)
{
    auto& stack = L->stack;
    auto& scope = L->scope;
    auto len = logic_stack_len(L);
    if (len == 2)
    {
        auto fn = logic_stack_get_function(L, 0);
        auto idx = logic_stack_get_integer(L, 1);
        if (fn != NULL)
        {

            auto isruntime = fn->type == FunctionData::FunctionType::Runtime;
            if (isruntime)
            {
                auto& fnruntime = fn->get_runtimefn();
                auto& argsname = fnruntime.argsname;
                if (idx >= 0 && idx < argsname.size())
                {
                    auto& str = fnruntime.argsname.at(idx);
                    
                    stack.push(ObjectHelper::NewString(str.c_str()));
                }
                else
                {
                    stack.push(ObjectHelper::NewString(""));
                }

            }
            else
            {
                stack.push(ObjectHelper::NewString(""));
            }
            return 1;

        }
    }
    return 0;
}

int LogicCode::Std::refbitset_get(LogicCodeState* L)
{
    auto& stack = L->stack;
    auto& scope = L->scope;
    auto len = logic_stack_len(L);
    if (len == 1)
    {
        auto refbit = logic_stack_get_refbitset(L, 0);
        if (refbit != NULL)
        {
            stack.push(refbit->GetValue());
            return 1;
        }
    }
    return 0;
}

int LogicCode::Std::refbitset_set(LogicCodeState* L)
{
    auto& stack = L->stack;
    auto& scope = L->scope;
    auto len = logic_stack_len(L);
    if (len == 2)
    {
        auto refbit = logic_stack_get_refbitset(L, 0);
        auto& value = stack.get(1);

        if (refbit != NULL)
        {

            refbit->SetValue(value);

        }
    }
    return 0;
}

int LogicCode::Std::integer_Abs(LogicCodeState* L)
{
    auto len = logic_stack_len(L);
    if (len == 1)
    {
        auto numv = logic_stack_get_integer(L, 0);
        logic_stack_push_integer(L, abs(numv));
        return 1;
    }
    return 0;
}

int LogicCode::Std::integer_Equals(LogicCodeState* L)
{
    auto len = logic_stack_len(L);
    if (len == 2)
    {
        auto num1 = logic_stack_get_integer(L, 0);
        auto num2 = logic_stack_get_integer(L, 1);

        logic_stack_push_bool(L, num1 == num2);
        return 1;
    }
    return 0;
}

int LogicCode::Std::integer_Clamp(LogicCodeState* L)
{
    auto len = logic_stack_len(L);
    if (len == 3)
    {
        auto v = logic_stack_get_integer(L, 0);
        auto lo = logic_stack_get_integer(L, 1);
        auto hi = logic_stack_get_integer(L, 2);

        auto vret = v > hi ? hi : (v < lo ? lo : v);
        logic_stack_push_integer(L, vret);

        return 1;
    }
    return 0;
}

int LogicCode::Std::integer_IsNegative(LogicCodeState* L)
{
    auto len = logic_stack_len(L);
    if (len == 1)
    {
        auto num = logic_stack_get_integer(L, 0);

        logic_stack_push_bool(L,num < 0);
        return 1;
    }
    return 0;
}

int LogicCode::Std::integer_IsPositive(LogicCodeState* L)
{
    auto len = logic_stack_len(L);
    if (len == 1)
    {
        auto num = logic_stack_get_integer(L, 0);

        logic_stack_push_bool(L,num > 0);
        return 1;
    }
    return 0;
}

int LogicCode::Std::integer_Max(LogicCodeState* L)
{
    auto len = logic_stack_len(L);
    if (len >= 1)
    {
        bool first = true;
        LogicInteger num = 0;
        for (size_t i = 0; i < len; i++)
        {
            auto currentv = logic_stack_get_integer(L, i);

            if (first)
            {
                num = currentv;
                first = false;
            }
            else
            {
                num = currentv > num ? currentv : num;

            }

        }
        logic_stack_push_integer(L, num);

        return 1;
    }
    return 0;
}

int LogicCode::Std::integer_Min(LogicCodeState* L)
{
    auto len = logic_stack_len(L);
    if (len >= 1)
    {
        bool first = true;
        LogicInteger num = 0;
        for (size_t i = 0; i < len; i++)
        {
            auto currentv = logic_stack_get_integer(L, i);

            if (first)
            {
                num = currentv;

                first = false;
            }
            else
            {
                num = currentv < num ? currentv : num;

            }

        }
        logic_stack_push_integer(L, num);

        return 1;
    }
    return 0;
}

int LogicCode::Std::integer_Parse(LogicCodeState* L)
{
    auto len = logic_stack_len(L);
    if (len == 1)
    {
        auto str = logic_stack_get_string(L, 0);
        if (str != NULL)
        {
            auto val = atoll(str->txt);
            logic_stack_push_integer(L, val);

            return 1;

        }
    }
    return 0;
}

int LogicCode::Std::integer_Sign(LogicCodeState* L)
{
    auto len = logic_stack_len(L);
    if (len == 1)
    {
        auto num = logic_stack_get_integer(L, 0);



        auto ret = num == 0 ? 0 : (num < 0 ? -1 : 1);

        logic_stack_push_integer(L, ret);

        return 1;

    }
    return 0;
}

int LogicCode::Std::integer_ToString(LogicCodeState* L)
{
    auto len = logic_stack_len(L);
    if (len == 1)
    {
        auto num = logic_stack_get_integer(L, 0);


        char str[20] = {};
        _i64toa_s(num, str, 20, 10);

        logic_stack_push_string(L,str);
        return 1;

    }
    return 0;
}

int LogicCode::Std::number_Abs(LogicCodeState* L)
{
    auto& stack = L->stack;
    auto& scope = L->scope;
    auto len = logic_stack_len(L);
    if (len == 1)
    {
        auto num = logic_stack_get_number(L, 0);

        auto newret = fabs(num);

        stack.push(ObjectHelper::NewNumber(newret));
        return 1;

    }
    return 0;
}

int LogicCode::Std::number_Clamp(LogicCodeState* L)
{
    auto len = logic_stack_len(L);
    if (len == 3)
    {
        auto num = logic_stack_get_number(L, 0);
        auto minnum = logic_stack_get_number(L, 1);
        auto maxnum = logic_stack_get_number(L, 2);

        auto newret = num > maxnum ? maxnum : num < minnum ? minnum : num;
        logic_stack_push_number(L,newret);
        return 1;
    }
    return 0;
}

int LogicCode::Std::number_Equals(LogicCodeState* L)
{
    auto len = logic_stack_len(L);
    if (len == 2)
    {
        auto v1 = logic_stack_get_number(L, 0);
        auto v2 = logic_stack_get_number(L, 1);

        auto newret = v1 == v2;

        logic_stack_push_number(L, newret);
        return 1;
    }
    return 0;
}

int LogicCode::Std::number_IsFinite(LogicCodeState* L)
{
    auto len = logic_stack_len(L);
    if (len == 1)
    {
        auto v1 = logic_stack_get_number(L, 0);

        auto newret = std::isfinite(v1);

        logic_stack_push_bool(L, newret);
        return 1;
    }
    return 0;
}

int LogicCode::Std::number_IsInfinity(LogicCodeState* L)
{
    auto len = logic_stack_len(L);
    if (len == 1)
    {
        auto v1 = logic_stack_get_number(L, 0);

        auto newret = std::isinf(v1);

        logic_stack_push_bool(L, newret);
        return 1;
    }
    return 0;
}

int LogicCode::Std::number_IsNaN(LogicCodeState* L)
{
    auto len = logic_stack_len(L);
    if (len == 1)
    {
        auto v1 = logic_stack_get_number(L, 0);

        auto newret = std::isnan(v1);
        logic_stack_push_bool(L, newret);

        return 1;
    }
    return 0;
}

int LogicCode::Std::number_IsNegative(LogicCodeState* L)
{
    auto len = logic_stack_len(L);
    if (len == 1)
    {
        auto v1 = logic_stack_get_number(L, 0);

        auto newret = ((*(LogicInteger*)(&v1)) & 0x7FFFFFFFFFFFFFFFL) > 0x7FF0000000000000L;
        
        logic_stack_push_bool(L, newret);
        return 1;
    }
    return 0;
}

int LogicCode::Std::number_IsNegativeInfinity(LogicCodeState* L)
{
    auto len = logic_stack_len(L);
    if (len == 1)
    {
        auto v1 = logic_stack_get_number(L, 0);

        auto newret = v1 == -std::numeric_limits<double>::infinity();
        logic_stack_push_bool(L, newret);
        return 1;
    }
    return 0;
}

int LogicCode::Std::number_IsPositive(LogicCodeState* L)
{
    auto len = logic_stack_len(L);
    if (len == 1)
    {
        auto v1 = logic_stack_get_number(L, 0);


        auto newret = ((*(LogicInteger*)(&v1)) & 0x7FFFFFFFFFFFFFFFL) > 0x7FF0000000000000L;
        logic_stack_push_bool(L, !newret);
        return 1;

    }
    return 0;
}

int LogicCode::Std::number_IsPositiveInfinity(LogicCodeState* L)
{
    auto len = logic_stack_len(L);
    if (len == 1)
    {
        auto v1 = logic_stack_get_number(L, 0);


        auto newret = v1 == std::numeric_limits<double>::infinity();
        logic_stack_push_bool(L, newret);
        return 1;

    }
    return 0;
}

int LogicCode::Std::number_Max(LogicCodeState* L)
{
    auto len = logic_stack_len(L);
    if (len >= 1)
    {
        auto v1 = logic_stack_get_number(L, 0);

        auto newret = v1;

        for (size_t i = 1; i < len; i++)
        {

            auto vcurrent = logic_stack_get_number(L, i);
            newret = vcurrent > newret ? vcurrent : newret;


        }
        logic_stack_push_number(L, newret);

        return 1;

    }
    return 0;
}

int LogicCode::Std::number_Min(LogicCodeState* L)
{
    auto len = logic_stack_len(L);
    if (len >= 1)
    {
        auto v1 = logic_stack_get_number(L, 0);


        auto newret = v1;

        for (size_t i = 1; i < len; i++)
        {
            auto vcurrent = logic_stack_get_number(L, i);


            newret = vcurrent < newret ? vcurrent : newret;

        }

        logic_stack_push_number(L, newret);

        return 1;

    }
    return 0;
}

int LogicCode::Std::number_Parse(LogicCodeState* L)
{
    auto len = logic_stack_len(L);
    if (len == 1)
    {
        auto v1 = logic_stack_get_string(L, 0);

        if (v1 != NULL)
        {
            auto newret = std::atof(v1->txt);
            logic_stack_push_number(L, newret);
            return 1;
        }


    }
    return 0;
}

int LogicCode::Std::number_ToString(LogicCodeState* L)
{
    auto len = logic_stack_len(L);
    if (len == 1)
    {
        auto v1 = logic_stack_get_number(L, 0);

        char str[20] = {};
        sprintf_s(&str[0], 20, "%f", v1);
        logic_stack_push_string(L, str);
        return 1;


    }
    return 0;
}

int LogicCode::Std::string_byte(LogicCodeState* L)
{
    auto len = logic_stack_len(L);
    if (len >= 1)
    {
        auto v1 = logic_stack_get_string(L, 0);


        LogicInteger idx = 0;
        if (len >= 2)
        {
            idx = logic_stack_get_integer(L, 1);
        }
        if (v1 != NULL)
        {
            if (idx < 0 || idx > v1->size)
            {
                logic_stack_push_none(L);
            }
            else
            {
                logic_stack_push_integer(L, v1->txt[idx]);
            }
            return 1;
        }


    }
    return 0;
}

int LogicCode::Std::string_char(LogicCodeState* L)
{
    auto len = logic_stack_len(L);
    if (len >= 1)
    {
        auto v1 = logic_stack_get_string(L, 0);


        LogicInteger idx = 0;
        if (len >= 2)
        {
            idx = logic_stack_get_integer(L, 1);

        }
        if (v1 != NULL)
        {
            if (idx < 0 || idx > v1->size)
            {
                logic_stack_push_none(L);
            }
            else
            {
                const char current[2] = { v1->txt[idx],'\0' };
                logic_stack_push_string(L,current);
            }
            return 1;
        }


    }
    return 0;
}

int LogicCode::Std::string_len(LogicCodeState* L)
{
    auto& stack = L->stack;
    auto& scope = L->scope;
    auto len = logic_stack_len(L);
    if (len >= 1)
    {
        auto str = logic_stack_get_string(L, 0);


        size_t len = 0;
        if (str != NULL)
        {
            len = str->size;
        }
        logic_stack_push_integer(L,len);
        return 1;

    }
    return 0;

}

int LogicCode::Std::string_reverse(LogicCodeState* L)
{
    auto& stack = L->stack;
    auto& scope = L->scope;
    auto len = logic_stack_len(L);
    if (len >= 1)
    {
        auto str = logic_stack_get_string(L, 0);

        if (str != NULL)
        {
            auto len_str = str->size;
            auto end_str = len_str - 1;
            auto strret = ObjectHelper::NewStringLen(len_str);
            auto buff = (char*)strret->txt;
            for (size_t i = 0; i < len_str; i++)
            {
                auto current = str->txt[end_str - i];
                buff[i] = current;
            }
            stack.push(strret);
        }
        else
        {
            logic_stack_push_none(L);
        }
        return 1;

    }
    return 0;
}

int LogicCode::Std::string_lower(LogicCodeState* L)
{
    auto& stack = L->stack;
    auto& scope = L->scope;
    auto len = logic_stack_len(L);
    if (len >= 1)
    {
        auto str = logic_stack_get_string(L, 0);


        if (str != NULL)
        {
            auto len_str = str->size;
            auto strret = ObjectHelper::NewStringLen(len_str);
            auto buff = (char*)strret->txt;
            for (size_t i = 0; i < len_str; i++)
            {
                auto current = str->txt[i];
                buff[i] = tolower(current);
            }
            stack.push(strret);
        }
        else
        {
            logic_stack_push_none(L);
        }
        return 1;

    }
    return 0;
}

int LogicCode::Std::string_upper(LogicCodeState* L)
{
    auto& stack = L->stack;
    auto& scope = L->scope;
    auto len = logic_stack_len(L);
    if (len >= 1)
    {

        auto str = logic_stack_get_string(L, 0);


        if (str != NULL)
        {
            auto len_str = str->size;
            auto strret = ObjectHelper::NewStringLen(len_str);
            auto buff = (char*)strret->txt;
            for (size_t i = 0; i < len_str; i++)
            {
                auto current = str->txt[i];
                buff[i] = toupper(current);
            }
            stack.push(strret);
        }
        else
        {
            logic_stack_push_none(L);
        }
        return 1;

    }
    return 0;
}

int LogicCode::Std::bitset_tostring(LogicCodeState* L)
{
    auto len = logic_stack_len(L);
    if (len >= 1)
    {
        auto bitset = logic_stack_get_bitset(L, 0);

        size_t size = bitset->size();
        if (bitset != NULL)
        {
            char* val = new char[size + 1];
            val[size] = '\0';
            for (size_t i = 0; i < size; i++)
            {
                val[i] = bitset->get(i) ? '1' : '0';
            }
            logic_stack_push_string(L, val);
            delete[] val;
            return 1;
        }
        else
        {
            return _Error(L, "Invalid parameter #1");
        }

    }
    return 0;
}

int LogicCode::Std::bitset_parse(LogicCodeState* L)
{
    auto& stack = L->stack;
    auto& scope = L->scope;
    auto len = logic_stack_len(L);
    if (len >= 1)
    {
        auto str = logic_stack_get_string(L, 0);

        size_t size = str->size;
        if (str != NULL)
        {
            auto bitset = ObjectHelper::NewBitset(size);
            for (size_t i = 0; i < size; i++)
            {
                bool currentval = str->txt[i] == '1';
                bitset->set(i, currentval);
            }
            stack.push(bitset);
            return 1;
        }
        else
        {
            return _Error(L, "Invalid parameter #1");
        }

    }
    return 0;
}

int LogicCode::Std::bitset_len(LogicCodeState* L)
{
    auto len = logic_stack_len(L);
    if (len >= 1)
    {
        size_t sizeret = 0;
        for (size_t i = 0; i < len; i++)
        {
            auto val = logic_stack_get_bitset(L, i);

            if (val != NULL)
            {
                sizeret += val->size();
            }
        }
        logic_stack_push_integer(L, sizeret);
        return 1;
    }
    return 0;
}

int LogicCode::Std::bitset_concat(LogicCodeState* L)
{

    auto& stack = L->stack;
    auto& scope = L->scope;
    auto len = logic_stack_len(L);
    if (len >= 1)
    {
        size_t sizeret = 0;
        for (size_t i = 0; i < len; i++)
        {
            auto val = logic_stack_get_bitset(L, i);


            if (val != NULL)
            {
                sizeret += val->size();
            }
        }
        auto valret = ObjectHelper::NewBitset(sizeret);
        size_t indexcurrent = sizeret - 1;
        for (size_t i = 0; i < len; i++)
        {
            auto val = logic_stack_get_bitset(L, i);

            if (val != NULL)
            {
                auto vallen = val->size();
                for (size_t i2 = 0; i2 < vallen; i2++)
                {

                    auto currentvaluebit = val->get(vallen - 1 - i2);
                    valret->set(indexcurrent - i2, currentvaluebit);
                }
                indexcurrent -= vallen;
            }
        }

        stack.push(valret);
        return 1;
    }
    return 0;
}

int LogicCode::Std::bitset_slice(LogicCodeState* L)
{
    auto& stack = L->stack;
    auto& scope = L->scope;
    auto len = logic_stack_len(L);
    if (len >= 2)
    {
        auto bits = logic_stack_get_bitset(L, 0);
        auto start = logic_stack_get_integer(L,1);
        if (bits != NULL)
        {
            auto bitslen = bits->size();
            auto end = len >= 3 ? logic_stack_get_integer(L, 2) : bitslen;

            auto sizeretbitset = end - start;
            if (sizeretbitset > 0 && sizeretbitset <= bitslen)
            {
                auto ret = ObjectHelper::NewBitset((size_t)sizeretbitset);

                for (size_t i = 0; i < sizeretbitset; i++)
                {
                    ret->set(i, bits->get(start + i));
                }
                stack.push(ret);
                return 1;
            }
        }
    }
    return 0;
}

int LogicCode::Std::bitset_reverse(LogicCodeState* L)
{
    auto& stack = L->stack;
    auto& scope = L->scope;
    auto len = logic_stack_len(L);
    if (len >= 1)
    {
        auto bits = logic_stack_get_bitset(L, 0);
        if (bits != NULL)
        {
            auto bits_size = bits->size();
            auto ret = ObjectHelper::NewBitset(bits_size);
            auto bits_last = bits_size - 1;
            for (size_t i = 0; i < bits_size; i++)
            {
                ret->set(i, bits->get(bits_last - i));
            }
            stack.push(ret);
            return 1;
        }
        
    }
    return 0;
}

void LogicCode::Std::__Inc(std::bitsetdynamic* v)
{
    auto size = v->size();
    auto CarryIn = false;
    for (size_t i = 0; i < size; i++)
    {
        auto A = v->get(i);
        auto B = i == 0;
        auto CarryOut = A && B || CarryIn && B || CarryIn && A;
        auto C = !CarryIn && !A && B || !CarryIn && A && !B || CarryIn && !A && !B || CarryIn && A && B;


        v->set(i, C);
        CarryIn = CarryOut;

    }
}

void LogicCode::Std::__Dec(std::bitsetdynamic* v)
{
    auto size = v->size();
    auto BorrowIn = false;
    for (size_t i = 0; i < size; i++)
    {
        auto A = v->get(i);
        auto B = i == 0;
        auto BorrowOut = !A && B || BorrowIn && !A || BorrowIn && B;
        auto C = !BorrowIn && !A && B || !BorrowIn && A && !B || BorrowIn && !A && !B || BorrowIn && A && B;


        v->set(i, C);
        BorrowIn = BorrowOut;

    }
}






void LogicCode::Std::__Init(LogicCodeState* L)
{

        
    // wiring
    Wiring::BitExtender::Init(L);


    // io functions 
    logic_scope_setvar_fnnative(L, "print", Print);
    logic_scope_setvar_fnnative(L, "debug.log", Debug_Log);
    logic_scope_setvar_fnnative(L, "debug.clear", Debug_Clear);

    // general function
    logic_scope_setvar_fnnative(L, "type", GetType);
    logic_scope_setvar_fnnative(L, "argslen", Argslen);
    logic_scope_setvar_fnnative(L, "isnone", IsNone);
    logic_scope_setvar_fnnative(L, "zero", Zero);
    logic_scope_setvar_fnnative(L, "one", One);
    logic_scope_setvar_fnnative(L, "truthtable", TruthTable);

    // logisim gates functions
    logic_scope_setvar_fnnative(L, "and", And);
    logic_scope_setvar_fnnative(L, "or", Or);
    logic_scope_setvar_fnnative(L, "not", Not);
    logic_scope_setvar_fnnative(L, "xor", Xor);
    logic_scope_setvar_fnnative(L, "nand", Nand);
    logic_scope_setvar_fnnative(L, "nor", Nor);
    logic_scope_setvar_fnnative(L, "xnor", Xnor);
    logic_scope_setvar_fnnative(L, "buffer", Buffer);
    logic_scope_setvar_fnnative(L, "controlledbuffer", ControlledBuffer);
    logic_scope_setvar_fnnative(L, "controlledinverter", ControlledInverter);
    logic_scope_setvar_fnnative(L, "oddparity", OddParity);
    logic_scope_setvar_fnnative(L, "evenparity", EvenParity);

    // logisim plexers functions
    logic_scope_setvar_fnnative(L, "mux", Mux);
    logic_scope_setvar_fnnative(L, "demux", Demux);
    logic_scope_setvar_fnnative(L, "decoder", Decoder);
    logic_scope_setvar_fnnative(L, "bitselector", BitSelector);
    logic_scope_setvar_fnnative(L, "prioritydecoder", PriorityDecoder);



    // logisim arith  functions
    logic_scope_setvar_fnnative(L, "add", Add);
    logic_scope_setvar_fnnative(L, "sub", Sub);
    logic_scope_setvar_fnnative(L, "mul", Mul);
    logic_scope_setvar_fnnative(L, "div", Div);
    logic_scope_setvar_fnnative(L, "negator", Negator);
    Arithmetic::Shifter::Init(L);
    Arithmetic::BitFinder::Init(L);
    Arithmetic::BitAdder::Init(L);
    Arithmetic::Comparator::Init(L);

    // function api
    logic_scope_setvar_fnnative(L, "function.isNative", function_isNative);
    logic_scope_setvar_fnnative(L, "function.isRuntime", function_isRuntime);
    logic_scope_setvar_fnnative(L, "function.argslen", function_argslen);
    logic_scope_setvar_fnnative(L, "function.getargname", function_getargname);

    // refbitset
    logic_scope_setvar_fnnative(L, "refbitset.get", refbitset_get);
    logic_scope_setvar_fnnative(L, "refbitset.set", refbitset_set);

    // Integer
    logic_scope_setvar_integer(L, "integer.maxvalue", INT64_MAX);
    logic_scope_setvar_integer(L, "integer.minvalue", INT64_MIN);
    logic_scope_setvar_fnnative(L, "integer.abs", integer_Abs);
    logic_scope_setvar_fnnative(L, "integer.equals", integer_Equals);
    logic_scope_setvar_fnnative(L, "integer.clamp", integer_Clamp);
    logic_scope_setvar_fnnative(L, "integer.tostring", integer_ToString);
    logic_scope_setvar_fnnative(L, "integer.sign", integer_Sign);
    logic_scope_setvar_fnnative(L, "integer.parse", integer_Parse);
    logic_scope_setvar_fnnative(L, "integer.max", integer_Max);
    logic_scope_setvar_fnnative(L, "integer.min", integer_Min);
    logic_scope_setvar_fnnative(L, "integer.isnegative", integer_IsNegative);
    logic_scope_setvar_fnnative(L, "integer.ispositive", integer_IsPositive);

    // number
    logic_scope_setvar_number(L, "number.maxvalue", DBL_MAX);
    logic_scope_setvar_number(L, "number.minvalue", DBL_MIN);
    logic_scope_setvar_number(L, "number.nan", std::numeric_limits<double>::quiet_NaN());
    logic_scope_setvar_number(L, "number.negativeinfinity", -std::numeric_limits<double>::infinity());
    logic_scope_setvar_number(L, "number.positiveinfinity", std::numeric_limits<double>::infinity());
    logic_scope_setvar_number(L, "number.negativezero", -0.0);
    logic_scope_setvar_number(L, "number.PI", 3.14159265358979323846);
    logic_scope_setvar_fnnative(L, "number.abs", number_Abs);
    logic_scope_setvar_fnnative(L, "number.clamp", number_Clamp);
    logic_scope_setvar_fnnative(L, "number.equals", number_Equals);
    logic_scope_setvar_fnnative(L, "number.isfinite", number_IsFinite);
    logic_scope_setvar_fnnative(L, "number.isinfinity", number_IsInfinity);
    logic_scope_setvar_fnnative(L, "number.isnan", number_IsNaN);
    logic_scope_setvar_fnnative(L, "number.isnegative", number_IsNegative);
    logic_scope_setvar_fnnative(L, "number.isnegativeinfinity", number_IsNegativeInfinity);
    logic_scope_setvar_fnnative(L, "number.ispositive", number_IsPositive);
    logic_scope_setvar_fnnative(L, "number.ispositiveinfinity", number_IsPositiveInfinity);
    logic_scope_setvar_fnnative(L, "number.max", number_Max);
    logic_scope_setvar_fnnative(L, "number.min", number_Min);
    logic_scope_setvar_fnnative(L, "number.parse", number_Parse);
    logic_scope_setvar_fnnative(L, "number.tostring", number_ToString);

    // string
    logic_scope_setvar_fnnative(L, "string.byte", string_byte);
    logic_scope_setvar_fnnative(L, "string.char", string_char);
    logic_scope_setvar_fnnative(L, "string.len", string_len);
    logic_scope_setvar_fnnative(L, "string.reverse", string_reverse);
    logic_scope_setvar_fnnative(L, "string.lower", string_lower);
    logic_scope_setvar_fnnative(L, "string.upper", string_upper);

    // bitset
    logic_scope_setvar_fnnative(L, "bitset.tostring", bitset_tostring);
    logic_scope_setvar_fnnative(L, "bitset.parse", bitset_parse);
    logic_scope_setvar_fnnative(L, "bitset.len", bitset_len);
    logic_scope_setvar_fnnative(L, "bitset.concat", bitset_concat);
    logic_scope_setvar_fnnative(L, "bitset.slice", bitset_slice);
    logic_scope_setvar_fnnative(L, "bitset.reverse", bitset_reverse);


}

int LogicCode::Std::_Error(LogicCodeState* L, const char* v)
{
    L->error = v;
    return 0;
}
