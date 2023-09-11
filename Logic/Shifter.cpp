#include "Shifter.h"
#include "LogicObjectHelper.hpp"
#include "LogicCodeExt.h"
using namespace LogicCodeExt;

void LogicCode::Arithmetic::Shifter::Init(LogicCodeState* L)
{
    logic_scope_setvar_fnnative(L, "shifter", _Shifter);
    
    logic_scope_setvar_integer(L, "shifttype.LogicalLeft", (LogicInteger)Type::LogicalLeft);
    logic_scope_setvar_integer(L, "shifttype.LogicalRight", (LogicInteger)Type::LogicalRight);
    logic_scope_setvar_integer(L, "shifttype.RotateLeft", (LogicInteger)Type::RotateLeft);
    logic_scope_setvar_integer(L, "shifttype.RotateRight", (LogicInteger)Type::RotateRight);

}

int LogicCode::Arithmetic::Shifter::_Shifter(LogicCodeState* L)
{
    auto len = logic_stack_len(L);
    if (len == 3)
    {
        auto type = (Type)logic_stack_get_integer(L, 0);

        auto bits = logic_stack_get_bitset(L, 1);
        auto distance = logic_stack_get_integer(L, 2);
        if (bits != NULL)
        {
            auto bitslen = bits->size();
            auto ret = ObjectHelper::NewBitset(bitslen);
            if (type == Type::LogicalLeft)
            {
                for (size_t i = distance; i < bitslen; i++)
                {
                    ret->set(i, bits->get(i - distance));
                }
            }
            else if (type == Type::LogicalRight)
            {
                for (size_t i = distance; i < bitslen; i++)
                {
                    ret->set(i- distance, bits->get(i));
                }

            }
            else if (type == Type::RotateLeft)
            {
                auto v = (int)(distance % bitslen);
                for (size_t i = 0; i < bitslen; i++)
                {
                    int val = (int)i - v;
                    int current = val >= 0 ? val : (int)bitslen + val;
                    ret->set(i, bits->get(current));
                }
            }
            else if (type == Type::RotateRight)
            {
                auto v = (int)(distance % bitslen);
                for (size_t i = 0; i < bitslen; i++)
                {
                    int val = (int)i - v;
                    int current = val >= 0 ? val : (int)bitslen + val;
                    ret->set(current, bits->get(i));
                }
            }
            L->stack.push(ret);
            return 1;
        }
    }
    return 0;
}
