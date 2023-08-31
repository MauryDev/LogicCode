#include "LogicDebug.h"


void LogicCode::LogicDebug::Log(const char* value)
{
    
    if (funlog != nullptr)
    {
        funlog(value);
    }
}
