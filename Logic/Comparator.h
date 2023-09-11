#pragma once
#include "VariableData.hpp"

namespace LogicCode::Arithmetic {
    namespace Comparator
    {

        void Init(LogicCodeState* L);
        int CmpEqual(LogicCodeState* L);
        int CmpGreater(LogicCodeState* L);
        int CmpLess(LogicCodeState* L);

    }
}