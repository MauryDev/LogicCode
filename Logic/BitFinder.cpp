#include "BitFinder.h"
#include "LogicObjectHelper.hpp"
#include "LogicCodeExt.h"
using namespace LogicCodeExt;
    
void LogicCode::Arithmetic::BitFinder::Init(LogicCodeState* L)
{
    logic_scope_setvar_fnnative(L, "bitfinder", _BitFinder);


    logic_scope_setvar_integer(L, "bitfindertype.highestorder0", (LogicInteger)Type::highestorder0);
    logic_scope_setvar_integer(L, "bitfindertype.highestorder1", (LogicInteger)Type::highestorder1);
    logic_scope_setvar_integer(L, "bitfindertype.lowestorder0", (LogicInteger)Type::lowestorder0);
    logic_scope_setvar_integer(L, "bitfindertype.lowestorder1", (LogicInteger)Type::lowestorder1);

}

int LogicCode::Arithmetic::BitFinder::_BitFinder(LogicCodeState* L)
{
    auto len = logic_stack_len(L);
    if (len == 2)
    {
        auto type = (Type)logic_stack_get_integer(L, 0);
        auto bits = logic_stack_get_bitset(L, 1);

        if (bits != NULL)
        {
            auto size = bits->size();
            auto ishighest = type == Type::highestorder1 || type == Type::highestorder0;
            auto isone = type == Type::lowestorder1 || type == Type::highestorder1;
            LogicInteger idx = -1;
            if (ishighest)
            {
                size_t i = size - 1;
                for (size_t i2 = 0; i2 < size; i2++)
                {
                    auto current = bits->get(i);

                    if (isone == current)
                    {
                        idx = i;
                        break;
                    }
                    i--;
                }
            }
            else {
                for (size_t i = 0; i < size; i++)
                {
                    auto current = bits->get(i);

                    if (isone == current)
                    {
                        idx = i;
                        break;
                    }
                }
            }
            

            logic_stack_push_integer(L,idx);
            return 1;
        }


    }
    return 0;
}
