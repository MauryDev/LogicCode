#include "LogicCodeSTD.h"
#include "LogicCodeHelper.h"
#include <iostream>
#include "refcount_ptr.h"
#include <cmath>

void LogicCode::Std::And(FunctionData* __this, LogicCodeState* state)
{
    auto& stack = state->stack;
    auto& scope = state->scope;
    auto len = stack.sizeoffset();
    if (len > 0)
    {
        auto retv = std::bitsetdynamic::Copy(stack.get(0));

        scope->SetRet(retv);
        auto sizeinput = retv->size();
        
        for (size_t i = 1; i < len; i++)
        {
            auto current = stack.get(i);
            if (current->size() == sizeinput)
            {
                for (size_t i = 0; i < sizeinput; i++)
                {
                    retv->set(i, retv->get(i) && current->get(i));
                }
            }
            else
            {
                scope->SetRet({});
                return;
            }
        }
        return;
    }
    scope->SetRet({});

    
}

void LogicCode::Std::Or(FunctionData* __this, LogicCodeState* state)
{
    auto& stack = state->stack;
    auto& scope = state->scope;
    auto len = stack.sizeoffset();
    if (len > 0)
    {

        auto firstparam = std::bitsetdynamic::Copy(stack.get(0));
        scope->SetRet(firstparam);
        auto sizeinput = firstparam->size();

        for (size_t i = 1; i < len; i++)
        {
            auto current = stack.get(i);
            if (current->size() == sizeinput)
            {
                for (size_t i = 0; i < sizeinput; i++)
                {
                    firstparam->set(i, firstparam->get(i) || current->get(i));
                }
            }
            else
            {
                scope->SetRet({});
                return;
            }
        }
        return;

    }
    scope->SetRet({});


}


void LogicCode::Std::Not(FunctionData* __this, LogicCodeState* state)
{
    auto& stack = state->stack;
    auto& scope = state->scope;
    auto len = stack.sizeoffset();
    if (len == 1)
    {

        auto firstparam = std::bitsetdynamic::Copy(stack.get(0));

        scope->SetRet(firstparam);
        auto sizeinput = firstparam->size();

        for (size_t i = 0; i < sizeinput; i++)
        {
            firstparam->set(i, !firstparam->get(i));
        }
        return;

    }
    scope->SetRet({});
}

void LogicCode::Std::Xor(FunctionData* __this, LogicCodeState* state)
{
    auto& stack = state->stack;
    auto& scope = state->scope;
    auto len = stack.sizeoffset();
    if (len > 0)
    {

        auto firstparam = std::bitsetdynamic::Copy(stack.get(0));


        scope->SetRet(firstparam);
        auto sizeinput = firstparam->size();

        for (size_t i = 1; i < len; i++)
        {
            auto current = stack.get(i);
            if (current->size() == sizeinput)
            {
                for (size_t i = 0; i < sizeinput; i++)
                {
                    firstparam->set(i, firstparam->get(i) ^ current->get(i));
                }
            }
            else
            {
                scope->SetRet({});
                return;
            }
        }
        return;

    }
    scope->SetRet({});
}

void LogicCode::Std::Nand(FunctionData* __this, LogicCodeState* state)
{
    auto& stack = state->stack;
    auto& scope = state->scope;
    auto len = stack.sizeoffset();
    if (len > 0)
    {

        auto firstparam = std::bitsetdynamic::Copy(stack.get(0));

        scope->SetRet(firstparam);
        auto sizeinput = firstparam->size();

        for (size_t i = 1; i < len; i++)
        {
            auto current = stack.get(i);
            if (current->size() == sizeinput)
            {
                for (size_t i = 0; i < sizeinput; i++)
                {
                    firstparam->set(i, firstparam->get(i) && current->get(i));
                }
            }
            else
            {
                scope->SetRet({});
                return;
            }
        }
        for (size_t i = 0; i < sizeinput; i++)
        {
            firstparam->set(i, !firstparam->get(i));
        }
        return;


    }
    scope->SetRet({});
}

void LogicCode::Std::Nor(FunctionData* __this, LogicCodeState* state)
{
    auto& stack = state->stack;
    auto& scope = state->scope;
    auto len = stack.sizeoffset();
    if (len > 0)
    {

        auto firstparam = std::bitsetdynamic::Copy(stack.get(0));

        state->scope->SetRet(firstparam);
        auto sizeinput = firstparam->size();

        for (size_t i = 1; i < len; i++)
        {
            auto current = stack.get(i);
            if (current->size() == sizeinput)
            {
                for (size_t i = 0; i < sizeinput; i++)
                {
                    firstparam->set(i, firstparam->get(i) || current->get(i));
                }
            }
            else
            {
                scope->SetRet({});
                return;
            }
        }
        for (size_t i = 0; i < sizeinput; i++)
        {
            firstparam->set(i, !firstparam->get(i));
        }
        return;


    }
    scope->SetRet({});
}

void LogicCode::Std::Xnor(FunctionData* __this, LogicCodeState* state)
{
    auto& stack = state->stack;
    auto& scope = state->scope;
    auto len = stack.sizeoffset();
    if (len > 0)
    {

        auto firstparam = std::bitsetdynamic::Copy(stack.get(0));

        scope->SetRet(firstparam);
        auto sizeinput = firstparam->size();

        for (size_t i = 1; i < len; i++)
        {
            auto current = stack.get(i);
            if (current->size() == sizeinput)
            {
                for (size_t i = 0; i < sizeinput; i++)
                {
                    firstparam->set(i, firstparam->get(i) ^ current->get(i));
                }
            }
            else
            {
                scope->SetRet({});
                return;
            }
        }
        for (size_t i = 0; i < sizeinput; i++)
        {
            firstparam->set(i, !firstparam->get(i));
        }
        return;


    }
    scope->SetRet({});
}

void LogicCode::Std::If(LogicCodeState* state, Light::List& current)
{
    auto instructionsize = current.get_Count();

    if (instructionsize == 3)
    {
        auto arg1 = Helper::ToBitSet(state, current[1]);
        if (arg1->size() == 1)
        {
            auto condition = arg1->get(0);

            auto exp = current[2].expression;

            if (condition)
            {
                Helper::ExecuteInstuctionShared(state, *exp);
            }
        }
        

    }
    if (instructionsize == 5)
    {

        auto arg1 = Helper::ToBitSet(state, current[1]);


        auto exp = current[2].instruction;
        auto _else = current[3].str;
        auto exp2 = current[4].instruction;
        if (arg1->size() && _else->Equals("else"))
        {
            auto condition = arg1->get(0);
            if (condition)
            {
                Helper::ExecuteInstuctionShared(state,*exp);
            }
            else
            {
                Helper::ExecuteInstuctionShared(state ,*exp2);

            }
        }

    }
}

void LogicCode::Std::While(LogicCodeState* state, Light::List& current)
{
    auto instructionsize = current.get_Count();

    if (instructionsize == 3)
    {
        auto arg1 = Helper::ToBitSet(state,current[1]);

        auto exp = current[2].instruction;
        if (arg1->size() == 1)
        {
            auto condition = arg1->get(0);
            while (condition)
            {
                Helper::ExecuteInstuctionShared(state, *exp);
                condition = Helper::ToBitSet(state, current[1])->get(0);
            }
        }
        
    }
}

void LogicCode::Std::Fun(LogicCodeState* state,Light::List& current)
{
    auto instructionsize = current.get_Count();

    if (instructionsize == 4)
    {
        auto fnname = current[1].str;

        auto argsname = current[2].expression;
        auto argscount = argsname->get_Count();

        auto data = FunctionData::Make(state,FunctionData::FunctionRuntime{});
        
        for (size_t i = 0; i < argscount; i++)
        {
            data->get_runtimefn().argsname.push_back(argsname->at(i)[0].str->data());
        }
        data->get_runtimefn().body = current[3].instruction;
        state->scope->SetFunction(fnname->data(), data);
    }
}

void LogicCode::Std::Return(LogicCodeState* state, Light::List& current)
{
    auto instructionsize = current.get_Count();
    if (instructionsize >= 2)
    {
        auto lenlist = instructionsize - 1;
        Light::List values(lenlist, lenlist, &current.at(1));
       
        auto v2 = Helper::GetValue(state, values);
        if (!state->CanRun())
        {
            if (!state->IsError())
            {
                state->error = "Don't use return in expression";
            }
            return;
        }

        state->scope->SetRet(v2);
        state->ret = true;
    }
    else
    {
        state->scope->SetRet({});

    }
}

void LogicCode::Std::Print(FunctionData* __this, LogicCodeState* state)
{
    auto& stack = state->stack;
    auto& scope = state->scope;
    auto len = stack.sizeoffset();

    if (len >= 1)
    {

        for (size_t i = 0; i < len; i++)
        {
            auto result = stack.get(i);
            std::cout << result->to_string() << " ";
        }

        std::cout << std::endl;
        
    }

    scope->SetRet({});
}

void LogicCode::Std::Const(LogicCodeState* state, Light::List& current)
{
    auto instructionsize = current.get_Count();

    if (instructionsize >= 4)
    {
        auto name = current[1].str;
        auto type = current[2];

        if (type.resultType == Light::ResultType::Operador)
        {
            if (*type.coperator == Light::COperator::Set)
            {
                auto lenlist = instructionsize - 3;
                Light::List values(lenlist, lenlist, &current.at(3));
                auto v2 = Helper::GetValue(state, values);
                if (!state->CanRun())
                {
                    if (!state->IsError())
                    {
                        state->error = "Don't use return in expression";
                    }
                    return;
                }
                state->scope->SetConst(name->data(), v2,false);
            }
        }
    }
}

void LogicCode::Std::Var(LogicCodeState* state, Light::List& current)
{
    auto instructionsize = current.get_Count();

    if (instructionsize >= 4)
    {
        auto name = current[1].str;
        auto type = current[2];

        if (type.resultType == Light::ResultType::Operador)
        {
            if (*type.coperator == Light::COperator::Set)
            {
                auto lenlist = instructionsize - 3;
                Light::List values(lenlist, lenlist, &current.at(3));
                auto v2 = Helper::GetValue(state, values);
                if (!state->CanRun())
                {
                    if (!state->IsError())
                    {
                        state->error = "Don't use return in expression";
                    }
                    return;
                }
                state->scope->SetVar(name->data(), v2, false);
            }
        }
    }
}

void LogicCode::Std::Case(LogicCodeState* state, Light::List& current)
{
    auto instructionsize = current.get_Count();

    if (instructionsize == 3)
    {
        auto bits = Helper::ToBitSet(state,current[1]);
        auto len = bits->size();
        if (len == 1)
        {
            auto condition = bits->get(0);
            if (condition)
            {
                state->scope->SetRet(Helper::ToBitSet(state, current[2]));
            }
            else
            {
                state->scope->SetRet(Helper::ToBitSet(state, current[3]));
            }
        }
        
        
    }
    state->scope->SetRet({});

}

void LogicCode::Std::Buffer(FunctionData* __this, LogicCodeState* state)
{
    auto& stack = state->stack;
    auto& scope = state->scope;
    auto len = stack.sizeoffset();
    if (len == 1)
    {

        auto firstparam = std::bitsetdynamic::Copy(stack.get(0));
        scope->SetRet(firstparam);
        return;

    }
    scope->SetRet({});
}

void LogicCode::Std::Zero(FunctionData* __this, LogicCodeState* state)
{
    auto& stack = state->stack;
    auto& scope = state->scope;
    auto len = stack.sizeoffset();
    if (len == 1)
    {

        auto first = stack.get(0);
        auto data = __Toi8(first);
        auto ret = std::bitsetdynamic::Make((size_t)data);
        for (uint8_t i = 0; i < data; i++)
        {
            ret->set(i, false);
        }
        state->scope->SetRet(ret);
        return;

    }
    scope->SetRet({});
}

void LogicCode::Std::One(FunctionData* __this, LogicCodeState* state)
{
    auto& stack = state->stack;
    auto& scope = state->scope;
    auto len = stack.sizeoffset();
    if (len == 1)
    {

        auto first = stack.get(0);
        auto data = __Toi8(first);
        auto ret = std::bitsetdynamic::Make((size_t)data);
        for (uint8_t i = 0; i < data; i++)
        {
            ret->set(i, true);
        }
        state->scope->SetRet(ret);
        return;

    }
    scope->SetRet({});
}


std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic> LogicCode::Std::i8(LogicCodeState* state, Light::List& current)
{
    auto instructionsize = current.get_Count();

    if (instructionsize == 2)
    {
        auto numi8 = current[1].str;

        int8_t num = (int8_t)std::strtol(numi8->data(), nullptr, 10);
        auto refbits = std::bitsetdynamic::Make((size_t)8);
        char* data = (char*)refbits->data();

        memcpy(data, &num, sizeof(int8_t));
        return refbits;
    }
    return {};
}

std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic> LogicCode::Std::Ref(LogicCodeState* state, Light::List& current)
{
    auto instructionsize = current.get_Count();

    if (instructionsize == 2)
    {
        auto bits = current[1].str;
        
        auto refbits = RefValue::NewBitSet(state, *bits);

        return refbits;
    }
    return {};
}

void LogicCode::Std::Mux(FunctionData* __this, LogicCodeState* state)
{
    auto& stack = state->stack;
    auto& scope = state->scope;
    auto len = stack.sizeoffset();
    if (len >= 2)
    {

        auto selectbits = stack.get(0);
        auto selectbits_i8 = __Toi8(selectbits);

        auto lenargs = len - 1;
        if (selectbits_i8 < lenargs)
        {
            scope->SetRet(std::bitsetdynamic::Copy(stack.get(selectbits_i8 + 1)));
            return;
        }

    }
    scope->SetRet({});
}

void LogicCode::Std::Demux(FunctionData* __this, LogicCodeState* state)
{
    auto& stack = state->stack;
    auto& scope = state->scope;
    auto len = stack.sizeoffset();
    if (len >= 3)
    {

        auto selectbits = stack.get(0);
        auto value = stack.get(1);

        auto selectbits_i8 = __Toi8(selectbits);

        auto lenargs = len - 2;
        if (selectbits_i8 < lenargs)
        {

            auto value_selected = stack.get(selectbits_i8 + 2);
            auto valueref = (RefValue*)value_selected->data();
            valueref->state->scope->SetVar(valueref->str(), value);
            return;
        }

    }
    scope->SetRet({});
}

void LogicCode::Std::Decoder(FunctionData* __this, LogicCodeState* state)
{
    auto& stack = state->stack;
    auto& scope = state->scope;
    auto len = stack.sizeoffset();
    if (len >= 2)
    {

        auto selectbits = stack.get(0);

        auto selectbits_i8 = __Toi8(selectbits);

        auto lenargs = len - 1;
        if (selectbits_i8 < lenargs)
        {

            auto value_selected = stack.get(selectbits_i8 + 2);
            auto valueref = (RefValue*)value_selected->data();
            valueref->state->scope->SetVar(valueref->str(), std::bitsetdynamic::Make(true));
            return;
        }

    }
    scope->SetRet({});
}

void LogicCode::Std::BitSelector(FunctionData* __this, LogicCodeState* state)
{
    auto& stack = state->stack;
    auto& scope = state->scope;
    auto len = stack.sizeoffset();
    if (len == 2)
    {
        auto bits = stack.get(0);

        auto selectbits = stack.get(1);
        auto selectbits_i8 = __Toi8(selectbits);

        auto bitssize = bits->size();
        if (selectbits_i8 < bitssize)
        {
            scope->SetRet(std::bitsetdynamic::Make(bits->get(selectbits_i8)));
            return;
        }

    }
    scope->SetRet({});
}

void LogicCode::Std::Add(FunctionData* __this, LogicCodeState* state)
{
    auto& stack = state->stack;
    auto& scope = state->scope;
    auto len = stack.sizeoffset();
    if (len == 2)
    {
        auto value1 = stack.get(0);
        auto value2 = stack.get(1);
        auto value1size = value1->size();
        auto value2size = value2->size();
        if (value1size == value2size)
        {
            auto result = std::bitsetdynamic::Make(value1size);

            auto carry = false;
            for (size_t i = 0; i < value1size; i++)
            {
                auto bitcurrent1 = value1->get(i);
                auto bitcurrent2 = value2->get(i);
                if (bitcurrent1 && bitcurrent2)
                {
                    if (carry)
                    {
                        result->set(i, true);
                        carry = true;
                    }
                    else
                    {
                        result->set(i, false);
                        carry = true;
                    }
                }
                else
                {
                    auto orval = bitcurrent1 || bitcurrent2;
                    if (orval)
                    {
                        if (carry)
                        {
                            result->set(i, false);
                            carry = true;
                        }
                        else
                        {
                            result->set(i, true);
                            carry = false;

                        }
                    }
                    else
                    {
                        if (carry)
                        {
                            result->set(i, true);
                            carry = false;
                        }
                        else
                        {
                            result->set(i, false);
                            carry = false;

                        }

                    }
                }
            }

            scope->SetRet(result);
            return;
        }
        
    }
    
    scope->SetRet({});
    

}

void LogicCode::Std::Sub(FunctionData* __this, LogicCodeState* state)
{
}

int8_t LogicCode::Std::__Toi8(std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic>& v)
{
    auto sizev = v->size();
    auto len = sizev < 8 ? 0 : sizev - 8;
    int8_t value = 0;

    for (size_t i = 0; i < sizev; i++)
    {
        value <<= 1;
        value |= (int8_t)v->get(sizev - i - 1);
    }
    return value;
}

bool LogicCode::Std::__ToBool(std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic>& v)
{
    auto size = v->size();
    if (size > 0)
    {
        return v->get(0);
    }
    return false;
}




void LogicCode::Std::__Init(LogicCodeState* state)
{
    state->scope->SetFunction("and", FunctionData::Make(state, { And }));
    state->scope->SetFunction("or", FunctionData::Make(state, { Or }));
    state->scope->SetFunction("not", FunctionData::Make(state, { Not }));
    state->scope->SetFunction("xor", FunctionData::Make(state, { Xor }));
    state->scope->SetFunction("nand", FunctionData::Make(state, { Nand }));
    state->scope->SetFunction("nor", FunctionData::Make(state, { Nor }));
    state->scope->SetFunction("xnor", FunctionData::Make(state, { Xnor }));
    state->scope->SetFunction("print", FunctionData::Make(state, { Print }));
    state->scope->SetFunction("buffer", FunctionData::Make(state, { Buffer }));
    state->scope->SetFunction("zero", FunctionData::Make(state, { Zero }));
    state->scope->SetFunction("one", FunctionData::Make(state, { One }));
    state->scope->SetFunction("mux", FunctionData::Make(state, { Mux }));
    state->scope->SetFunction("demux", FunctionData::Make(state, { Demux }));
    state->scope->SetFunction("decoder", FunctionData::Make(state, { Decoder }));
    state->scope->SetFunction("bitselector", FunctionData::Make(state, { BitSelector }));
    state->scope->SetFunction("add", FunctionData::Make(state, { Add }));

}

const char* LogicCode::Std::RefValue::str()
{
    return (const char*)(this+1);
}

std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic> LogicCode::Std::RefValue::NewBitSet(LogicCodeState* state, Light::string_view& str)
{
    const auto lenv = sizeof(state) + str.size() + 1;
    auto refbits = std::bitsetdynamic::Make(lenv * 8);

    RefValue* data = (RefValue*)refbits->data();
    data->state = state;
    memcpy((void*)data->str(), str.data(), str.size() + 1);
    return refbits;
}
