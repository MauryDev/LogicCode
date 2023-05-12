#include "LogicCodeSTD.h"
#include "LogicCodeHelper.h"
#include <iostream>

bool LogicCode::Std::And(Light::List& current, VariableData& vars, bool& ret)
{
    auto instructionsize = current.get_Count();
    if (instructionsize >= 3)
    {
        auto v1 = Helper::ToBool(current[1], vars, ret);
        auto result = v1;
        for (int i = 2; i < instructionsize; i++)
            result = result && Helper::ToBool(current[i], vars, ret);
        return result;
    }
    
    return false;
}

bool LogicCode::Std::Or(Light::List& current, VariableData& vars, bool& ret)
{
    auto instructionsize = current.get_Count();

    if (instructionsize >= 3)
    {
        auto v1 = Helper::ToBool(current[1], vars, ret);
        auto result = v1;
        for (int i = 2; i < instructionsize; i++)
            result = result || Helper::ToBool(current[i], vars, ret);

        return result;
    }
    return false;
}

bool LogicCode::Std::Not(Light::List& current, VariableData& vars, bool& ret)
{
    auto instructionsize = current.get_Count();

    if (instructionsize == 2)
    {

        auto v1 = Helper::ToBool(current[1], vars, ret);

        return !v1;
    }
    return false;
}

bool LogicCode::Std::Xor(Light::List& current, VariableData& vars, bool& ret)
{
    auto instructionsize = current.get_Count();

    if (instructionsize >= 3)
    {
        auto v1 = Helper::ToBool(current[1], vars, ret);
        auto result = v1;
        for (int i = 2; i < instructionsize; i++)
            result = result ^ Helper::ToBool(current[i], vars, ret);

        return result;
    }
    return false;
}

bool LogicCode::Std::Nand(Light::List& current, VariableData& vars, bool& ret)
{
    auto instructionsize = current.get_Count();

    if (instructionsize >= 3)
    {
        auto v1 = Helper::ToBool(current[1], vars, ret);
        auto result = v1;
        for (int i = 2; i < instructionsize; i++)
            result = result && Helper::ToBool(current[i], vars, ret);

        return !result;
    }
    return false;
}

bool LogicCode::Std::Nor(Light::List& current, VariableData& vars, bool& ret)
{
    auto instructionsize = current.get_Count();

    if (instructionsize >= 3)
    {
        auto v1 = Helper::ToBool(current[1], vars, ret);
        auto result = v1;
        for (int i = 2; i < instructionsize; i++)
            result = result || Helper::ToBool(current[i], vars, ret);

        return !result;
    }
    return false;
}

bool LogicCode::Std::Xnor(Light::List& current, VariableData& vars, bool& ret)
{
    auto instructionsize = current.get_Count();

    if (instructionsize >= 3)
    {
        auto v1 = Helper::ToBool(current[1], vars, ret);
        auto result = v1;
        for (int i = 2; i < instructionsize; i++)
            result = result ^ Helper::ToBool(current[i], vars, ret);

        return !result;
    }
    return false;
}

void LogicCode::Std::If(Light::List& current, VariableData& vars, bool& ret)
{
    auto instructionsize = current.get_Count();

    if (instructionsize == 3)
    {

        auto condition = Helper::ToBool(current[1], vars, ret);

        auto exp = current[2].expression;

        if (condition)
        {
            Helper::ExecuteExpression(*exp, vars, ret);
        }

    }
    if (instructionsize == 5)
    {

        auto condition = Helper::ToBool(current[1], vars, ret);

        auto exp = current[2].expression;
        auto _else = current[3].str;
        auto exp2 = current[4].expression;

        if (_else->Equals("else"))
        {
            if (condition)
            {
                Helper::ExecuteExpression(*exp, vars, ret);
            }
            else
            {
                Helper::ExecuteExpression(*exp2, vars, ret);

            }
        }

    }
}

void LogicCode::Std::While(Light::List& current, VariableData& vars, bool& ret)
{
    auto instructionsize = current.get_Count();

    if (instructionsize == 3)
    {
        auto condition = Helper::ToBool(current[1], vars, ret);

        auto exp = current[2].expression;

        while (condition)
        {
            Helper::ExecuteExpression(*exp, vars, ret);
            condition = Helper::ToBool(current[1], vars, ret);
        }
    }
}

void LogicCode::Std::Fun(Light::List& current, VariableData& vars, bool& ret)
{
    auto instructionsize = current.get_Count();

    if (instructionsize == 4)
    {
        auto fnname = current[1].str;

        auto argsname = current[2].expression;
        auto argscount = argsname->get_Count();
        FunctionData data;
        for (size_t i = 0; i < argscount; i++)
        {
            data.argsname.push_back(argsname->at(i)[0].str->data());
        }
        data.body = current[3].expression;


        data.parent = &vars;

        vars.SetFunction(fnname->data(), data);
    }
}

void LogicCode::Std::Return(Light::List& current, VariableData& vars, bool& ret)
{
    auto instructionsize = current.get_Count();

    if (instructionsize == 2)
    {
        auto result = Helper::ToBool(current[1], vars, ret);
        vars.ret = result;
        ret = true;
    }
}

void LogicCode::Std::Print(Light::List& current, VariableData& vars, bool& ret)
{
    auto instructionsize = current.get_Count();

    if (instructionsize == 2)
    {
        auto result = Helper::ToBool(current[1], vars, ret);
        std::cout << Helper::ToStr(result) << std::endl;
    }
}

void LogicCode::Std::Const(Light::List& current, VariableData& vars, bool& ret)
{
    auto instructionsize = current.get_Count();

    if (instructionsize == 4)
    {
        auto name = current[1].str;
        auto type = current[2];

        if (type.resultType == Light::ResultType::Operador)
        {
            if (*type.operador == Light::COperator::Set)
            {
                auto v2 = Helper::ToBool(current[3], vars, ret);
                vars.SetConst(name->data(), v2);
            }
        }
    }
}

bool LogicCode::Std::Case(Light::List& current, VariableData& vars, bool& ret)
{
    auto instructionsize = current.get_Count();

    if (instructionsize == 3)
    {
        auto condition = Helper::ToBool(current[1], vars, ret);
        if (condition)
        {
            return Helper::ToBool(current[2], vars, ret);
        }
        else
        {
            return Helper::ToBool(current[3], vars, ret);
        }
        
    }
    return false;
}

void LogicCode::Std::_AddBitArray(std::bitsetdynamic& bitset)
{
    auto len = bitset.length();
    for (size_t i = 0; i < len; i++)
    {
        auto current = bitset.get(i);
        bitset.set(i, !current);
        if (!current)
        {
            break;
        }
        
    }
}

void LogicCode::Std::TruthTable(Light::List& current, VariableData& vars, bool& ret)
{
    auto instructionsize = current.get_Count();

    if (instructionsize == 3)
    {
        auto argsls = current[1].expression;
        auto argscount = argsls->get_Count();
        auto body = current[2].expression;
        std::vector<std::string> argsname;
        
        for (size_t i = 0; i < argscount; i++)
        {
            argsname.push_back(argsls->at(i)[0].str->data());
        }
        std::bitsetdynamic arrbits(argscount);
        for (size_t i = 0; i < argscount; i++)
        {
            for (size_t i2 = 0; i2 < argscount; i2++)
            {
                VariableData vd;
                vd.parent = &vars;
                bool retv = false;
                for (size_t i3 = 0; i3 < argscount; i3++)
                {
                    auto currentbit = arrbits.get(i3);
                    vd.SetConst(argsname[i3], currentbit);
                    std::cout << Helper::ToStr2(currentbit) << " | ";
                }
                Helper::ExecuteExpression(*body, vd, retv);
                std::cout << Helper::ToStr2(vd.ret) << std::endl;
                _AddBitArray(arrbits);
            }            
        }

    }
}
