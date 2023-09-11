#include "BitAdder.h"
#include "LogicObjectHelper.hpp"
#include "LogicCodeExt.h"
using namespace LogicCodeExt;

void LogicCode::Arithmetic::BitAdder::Init(LogicCodeState* L)
{
    logic_scope_setvar_fnnative(L, "bitadder", _BitAdder);

}

int LogicCode::Arithmetic::BitAdder::_BitAdder(LogicCodeState* L)
{
    auto len = logic_stack_len(L);
    LogicInteger adder = 0;
    for (size_t i = 0; i < len; i++)
    {
        auto bits = logic_stack_get_bitset(L, i);
        auto bitslen = bits->size();
        for (size_t i2 = 0; i2 < bitslen; i2++)
        {
            auto current = bits->get(i2);
            if (current)
            {
                adder++;
            }
        }
    }
    logic_stack_push_integer(L,adder);
    return 1;
}
