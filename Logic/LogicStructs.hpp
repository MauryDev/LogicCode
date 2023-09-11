
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
		Var
	};
	enum class ObjectType : int32_t
	{
		None,
		Bitset, // bitset
		RefBitset, // bitset*
		String, // const char*
		Integer, // i64
		Number, // f64,
		Function, // FunctionData
		UserObject, // LogicUserObject
		Pointer // LogicPointer
	};
	using LogicNumber = double;
	using LogicInteger = signed long long;
	using LogicBitset = std::bitsetdynamic;
    using LogicPointer = void*;

	struct LogicBitsetConfig {
		size_t size;
	};
	
}

#endif