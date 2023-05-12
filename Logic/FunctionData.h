#pragma once
#include <Light.h>
#include <string>

#include <vector>
struct FunctionData
{
	std::vector<std::string> argsname;
	void* parent;
	Light::Expression* body;
};

