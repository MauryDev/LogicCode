#pragma once
#include "LogicUserObject.h"
#include "VariableData.hpp"
namespace LogicCode::Wiring {

    struct BitExtender
    {
        enum class ExtensionType : uint8_t
        {
            None,
            Zero,
            One
        };
        static LogicUserClass klass;
        size_t len;
        ExtensionType type;

        static int New(LogicCodeState* L);
        static void Init(LogicCodeState* L);

        static int on(LogicCodeState* L);

    };
}


