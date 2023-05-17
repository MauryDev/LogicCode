#include <iostream>
#include <Light.h>
#include <fstream>
#include <sstream>
#include "VariableData.h"
#include "LogicCodeHelper.h"
#include <chrono>
#include <Windows.h>
#include "refcount_ptr.h"
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
    std::cout << "Tempo de execucao: " << duracao.count() << " microsegundos" << std::endl;
}
int main(int argc, const char** args)
{
    Test(argc, args);

}