#include <iostream>
#include <Light.h>
#include <fstream>
#include <sstream>
#include "VariableData.hpp"
#include "LogicCodeHelper.h"
#include <chrono>
#include <Windows.h>
#include "refcount_ptr.hpp"
#include "LogicObject.hpp"
#include "Logic.h"
#include "LogicDebug.h"
std::string slurp(std::ifstream& in) {
    
    std::ostringstream sstr;
    sstr << in.rdbuf();
    return sstr.str();
}

void Test(int argc, const char** args)
{
    const char* filesrc;
    if (argc > 1)
    {
        filesrc = args[1];
    }
    else
    {
        filesrc = "Script.lc";
    }
    Light::Token token;
    std::ifstream file(filesrc);
    auto strv = slurp(file);
    Light::string_view str(strv.data(), strv.length());
    token.ReadSTR_s(str);
    auto start = std::chrono::high_resolution_clock::now();

    auto results = LogicCode::Helper::IntrepreterLogic(token.expression);

    auto end = std::chrono::high_resolution_clock::now();

    auto duracao = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    token.Free();
    if (results->IsError())
    {
        std::cout <<"ERROR: " << results->error << std::endl;
    }
    std::cout << "Tempo de execucao: " << duracao.count() << " microsegundos" << std::endl;
}
int _Test(int argc, const char** args)
{
    Test(argc, args);
    system("pause");
    return 1;
}
BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,  // handle to DLL module
    DWORD fdwReason,     // reason for calling function
    LPVOID lpvReserved)  // reserved
{
    // Perform actions based on the reason for calling.
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        // Initialize once for each new process.
        // Return FALSE to fail DLL load.
        break;

    case DLL_THREAD_ATTACH:
        // Do thread-specific initialization.
        break;

    case DLL_THREAD_DETACH:
        // Do thread-specific cleanup.
        break;

    case DLL_PROCESS_DETACH:

        if (lpvReserved != nullptr)
        {
            break; // do not do cleanup if process termination scenario
        }

        // Perform any necessary cleanup.
        break;
    }
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}
extern "C"
{
    DLLEXPORT void SetupLog(void* method)
    {
        LogicCode::LogicDebug::funlog = (LogicCode::LogicDebug::FunLog)method;
    }

    DLLEXPORT void runCode(const char* code)
    {
        Light::Token token;
        Light::string_view str(code);
        token.ReadSTR_s(str);

        auto results = LogicCode::Helper::IntrepreterLogic(token.expression);

        token.Free();

    }
}
