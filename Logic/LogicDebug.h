#pragma once

namespace LogicCode::LogicDebug
{
    typedef  void(__stdcall*FunLog)(const char* v);
    typedef  void(__stdcall*FunClear)();

    inline FunLog funlog = {};
    inline FunClear funclear = {};

    void Log(const char* value);
    void Clear();

};

