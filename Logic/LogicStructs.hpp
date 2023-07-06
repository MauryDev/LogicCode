
#ifndef Logic_LogicStructs_HPP
#define Logic_LogicStructs_HPP
#include <cinttypes>
#include "bitsetdynamic.hpp"
#include <string>


namespace LogicCode
{
	enum class VarType: int8_t
	{
		None,
		Const,
		Var,
		Function
	};
	enum class ObjectType : int8_t
	{
		None,
		Bitset, // bitset
		RefBitset, // bitset*
		String, // const char*
		Integer, // i64
		Number, // f64,
		Function, // FunctionData
		Userdata, // UserData
		LightUserData // UserDataView
	};
	using LogicNumber = double;
	using LogicInteger = signed long long;
	using LogicBitset = std::bitsetdynamic;
	
	struct LogicBitsetConfig {
		size_t size;
	};
	
}

#endif