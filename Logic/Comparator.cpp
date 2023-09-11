#include "Comparator.h"
#include "LogicObjectHelper.hpp"
#include "LogicCodeExt.h"
using namespace LogicCodeExt;
void LogicCode::Arithmetic::Comparator::Init(LogicCodeState* L)
{
    logic_scope_setvar_fnnative(L, "cmpequal", CmpEqual);
    logic_scope_setvar_fnnative(L, "cmpgreater", CmpGreater);
    logic_scope_setvar_fnnative(L, "cmpless", CmpLess);

}

int LogicCode::Arithmetic::Comparator::CmpEqual(LogicCodeState* L)
{
    auto len = logic_stack_len(L);
    if (len == 2)
    {
        auto bits1 = logic_stack_get_bitset(L, 0);
        auto bits2 = logic_stack_get_bitset(L, 1);
        if (bits1 != NULL && bits2 != NULL)
        {
            auto firstlen = bits1->size();
            auto isequal = firstlen == bits2->size();
            if (isequal)
            {
                for (size_t i = 0; i < firstlen; i++)
                {
                    auto current1 = bits1->get(i);
                    auto current2 = bits2->get(i);

                    if (current1 != current2)
                    {
                        isequal = false;
                        break;
                    }
                }
            }
            logic_stack_push_bool(L, isequal);
            return 1;
        }
    }
    return 0;
}

int LogicCode::Arithmetic::Comparator::CmpGreater(LogicCodeState* L)
{
    auto len = logic_stack_len(L);
    if (len == 2)
    {
        auto bits1 = logic_stack_get_bitset(L, 0);
        auto bits2 = logic_stack_get_bitset(L, 1);
        if (bits1 != NULL && bits2 != NULL)
        {
            auto firstlen = bits1->size();
            auto isgreater = firstlen == bits2->size();
            if (isgreater)
            {
                isgreater = false;
                auto i2 = firstlen - 1;
                for (size_t i = 0; i < firstlen; i++)
                {
                    auto current1 = bits1->get(i2);
                    auto current2 = bits2->get(i2);

                    if (current1 && !current2)
                    {
                        isgreater = true;
                        break;
                    }
                    i2--;
                }
                logic_stack_push_bool(L, isgreater);
                return 1;
            }
            logic_stack_push_none(L);
            return 1;
        }
    }
    return 0;
}

int LogicCode::Arithmetic::Comparator::CmpLess(LogicCodeState* L)
{
    auto len = logic_stack_len(L);
    if (len == 2)
    {
        auto bits1 = logic_stack_get_bitset(L, 0);
        auto bits2 = logic_stack_get_bitset(L, 1);
        if (bits1 != NULL && bits2 != NULL)
        {
            auto firstlen = bits1->size();
            auto isless = firstlen == bits2->size();
            if (isless)
            {
                isless = false;
                auto i2 = firstlen - 1;
                for (size_t i = 0; i < firstlen; i++)
                {
                    auto current1 = bits1->get(i2);
                    auto current2 = bits2->get(i2);

                    if (!current1 && current2)
                    {
                        isless = true;
                        break;
                    }
                    i2--;
                }
                logic_stack_push_bool(L, isless);
                return 1;
            }
            logic_stack_push_none(L);
            return 1;
        }
    }
    return 0;
}
