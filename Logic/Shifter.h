#pragma once
#include "VariableData.hpp"
namespace LogicCode::Arithmetic {
    namespace Shifter
    {
        enum class Type : uint8_t
        {
            None,
            LogicalLeft,
            LogicalRight,
            RotateLeft,
            RotateRight
        };
        void Init(LogicCodeState* L);
        int _Shifter(LogicCodeState* L);
    };
}