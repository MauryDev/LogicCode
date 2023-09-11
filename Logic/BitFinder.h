#pragma once
#include "VariableData.hpp"

namespace LogicCode::Arithmetic {
    namespace BitFinder
    {
        enum class Type
        {
            highestorder1,
            lowestorder1,
            lowestorder0,
            highestorder0
        };
        void Init(LogicCodeState* L);
        int _BitFinder(LogicCodeState* L);

    }
}