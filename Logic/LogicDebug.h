#pragma once

namespace LogicCode::LogicDebug
{
    typedef  void(__stdcall*FunLog)(const char* v);
    inline FunLog funlog = {};
    void Log(const char* value);
};

