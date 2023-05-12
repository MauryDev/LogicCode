#include <iostream>
#include <Light.h>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include "VariableData.h"
#include "LogicCodeHelper.h"
#include <chrono>

std::string slurp(std::ifstream& in) {
    std::ostringstream sstr;
    sstr << in.rdbuf();
    return sstr.str();
}
int main()
{
    Light::Token token;
    std::ifstream file("Script.lc");
    auto strv = slurp(file);
    Light::string_view str(strv.data(),strv.length());
    token.ReadSTR_s(str);
    auto start = std::chrono::high_resolution_clock::now();

    auto results = LogicCode::Helper::IntrepreterLogic(token.expression);

    auto end = std::chrono::high_resolution_clock::now();
    auto duracao = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Tempo de execucao: " << duracao.count() << " microsegundos" << std::endl;
    system("pause");
}