#include "LogicCodeHelper.h"
#include "LogicCodeSTD.h"
#include <iostream>
const char* LogicCode::Helper::ToStr(bool v)
{
    return v ? "true" : "false";
}

const char* LogicCode::Helper::ToStr2(bool v)
{
    return  v ? "true " : "false";
}

bool LogicCode::Helper::ToBool(Light::CommandResult& command, VariableData& vars, bool& ret)
{
    if (command.resultType == Light::ResultType::Number)
    {
        auto number = command.ToInt();

        return number != 0;
    }
    else if (command.resultType == Light::ResultType::Label)
    {
        auto str = command.str;

        if (str->Equals("true") || str->Equals("TRUE"))
        {
            return true;
        }
        else if (str->Equals("false") || str->Equals("FALSE"))
        {
            return false;
        }
        else
        {
            return vars.GetValue(str->data());
        }
    }
    else if (command.resultType == Light::ResultType::Expression)
    {
        auto& exp = command.expression;
        if (exp->get_Count() == 1)
        {
            return GetValue(exp->at(0), vars, ret);
        }
    }
    return false;
}

bool LogicCode::Helper::GetValue(Light::List& current, VariableData& vars, bool& ret)
{
    auto instructionsize = current.get_Count();
    if (instructionsize > 0)
    {
        auto& currentopcode = current[0].str;
        if (currentopcode->Equals("and"))
        {
            return Std::And(current, vars, ret);
            
        }
        else if (currentopcode->Equals("or"))
        {
            return Std::Or(current, vars, ret);
        }
        else if (currentopcode->Equals("not"))
        {
            return Std::Not(current, vars, ret);
        }
        else if (currentopcode->Equals("xor"))
        {
            return Std::Xor(current, vars, ret);

        }
        else if (currentopcode->Equals("nand"))
        {
            return Std::Nand(current, vars, ret);

        }
        else if (currentopcode->Equals("nor"))
        {
            return Std::Nor(current, vars, ret);

        }
        else if (currentopcode->Equals("xnor"))
        {
            return Std::Xnor(current, vars, ret);

        }
        else if (currentopcode->Equals("if"))
        {
            Std::If(current, vars, ret);
        }
        else if (currentopcode->Equals("while"))
        {
            Std::While(current, vars, ret);

        }
        else if (currentopcode->Equals("fun"))
        {
            Std::Fun(current, vars, ret);
        }
        else if (currentopcode->Equals("return"))
        {
            Std::Return(current, vars, ret);
        }
        else if (currentopcode->Equals("print"))
        {
            Std::Print(current, vars, ret);
        }
        else if (currentopcode->Equals("const"))
        {
            Std::Const(current, vars, ret);
        }
        else if (currentopcode->Equals("truthtable"))
        {
            Std::TruthTable(current, vars, ret);
        }
        else if (currentopcode->Equals("case"))
        {
            Std::Case(current, vars, ret);
        }
        else if (currentopcode->Equals("true") || currentopcode->Equals("TRUE"))
        {
            return true;
        }
        else if (currentopcode->Equals("false") || currentopcode->Equals("FALSE"))
        {
            return false;
        }
        else
        {
            if (instructionsize == 3)
            {
                auto type = current[1];

                if (type.resultType == Light::ResultType::Operador)
                {
                    if (*type.operador == Light::COperator::Set)
                    {
                        auto v2 = ToBool(current[2], vars, ret);
                        vars.SetVar(currentopcode->data(), v2);

                    }
                }
                else
                {
                    auto getfn = vars.GetFunction(currentopcode->data());

                    if (getfn.body != NULL)
                    {
                        VariableData vd;
                        vd.parent = (VariableData*)getfn.parent;
                        bool retfn = false;
                        auto& args = getfn.argsname;
                        if (instructionsize - 1 == args.size())
                        {
                            for (size_t i = 0; i < args.size(); i++)
                            {
                                vd.SetConst(args[i], ToBool(current[i + 1], vars, ret));
                            }
                            ExecuteExpression(*getfn.body, vd, retfn);

                        }
                        return vd.ret;
                    }
                }
            }

        }

    }

    return false;
}

VariableData LogicCode::Helper::IntrepreterLogic(Light::Expression& token)
{
    VariableData variables;
    variables.parent = NULL;
    bool ret = false;
    ExecuteExpression(token, variables, ret);

    return variables;
}

void LogicCode::Helper::ExecuteExpression(Light::Expression& expression, VariableData& vars, bool& ret)
{
    auto count = expression.get_Count();

    for (size_t i = 0; i < count; i++)
    {
        if (ret)
        {
            break;
        }
        auto& current = expression[i];
        GetValue(current, vars, ret);
    }
}
