#include "BitExtenderConfig.h"
#include "LogicObjectHelper.hpp"
#include "LogicCodeExt.h"
using namespace LogicCodeExt;
LogicCode::LogicUserClass LogicCode::Wiring::BitExtender::klass;

int LogicCode::Wiring::BitExtender::New(LogicCodeState* L)
{
    auto len = logic_stack_len(L);
    if (len == 2)
    {
        auto v = ObjectHelper::NewTUserObject<BitExtender>(&klass);
        auto bitextenderconfig = v->ptr();

        auto len = logic_stack_get_integer(L, 0);
        auto type = logic_stack_get_integer(L, 1);

        bitextenderconfig->len = len;
        bitextenderconfig->type = (ExtensionType)type;

        L->stack.push(v);
        return 1;
    }
    

    return 0;
}

void LogicCode::Wiring::BitExtender::Init(LogicCodeState* L)
{
    logic_scope_setvar_fnnative(L, "bitextender.new", New);
    logic_scope_setvar_fnnative(L, "bitextender.on", on);
    logic_scope_setvar_integer(L, "extensiontype.Zero", (LogicInteger)ExtensionType::Zero);
    logic_scope_setvar_integer(L, "extensiontype.One", (LogicInteger)ExtensionType::One);

}

int LogicCode::Wiring::BitExtender::on(LogicCodeState* L)
{
    auto len = logic_stack_len(L);
    if (len == 2)
    {
        auto obj = logic_stack_get_userobject(L, 0);

        auto bits = logic_stack_get_bitset(L, 1);
        if (obj != NULL && bits != NULL && obj->klass == &klass)
        {
            BitExtender& bitextender = obj->obj<BitExtender>();
            auto len = bitextender.len;
            auto type = bitextender.type;
            auto ret = ObjectHelper::NewBitset(len);
            auto bitslen = bits->size();
            for (size_t i = 0; i < len; i++)
            {
                if (i < bitslen)
                {
                    ret->set(i, bits->get(i));
                }
                else
                {
                    auto isone = type == ExtensionType::One;
                    ret->set(i, isone);
                }
            }
            
            L->stack.push(ret);
            return 1;
        }
    }
    return 0;
}
