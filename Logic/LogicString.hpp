#ifndef Logic_LogicString_HPP
#define Logic_LogicString_HPP
#include <cinttypes>
namespace LogicCode
{
	struct LogicString {
		static size_t GetMemorySize(size_t strlen)
		{
			return sizeof(LogicString) + strlen + 1;
		}
		size_t size;
		char txt[];
	};
}

#endif