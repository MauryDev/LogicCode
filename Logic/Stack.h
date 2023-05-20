#pragma once
#include <vector>
#include "refcount_ptr.h"
#include "bitsetdynamic.h"

class StackBitset
{
private:
	std::vector<std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic>> stack;
	size_t offset;
public:

	StackBitset()
	{
		offset = 0;
	}
	~StackBitset()
	{
	}
	void push(std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic>& v)
	{
		stack.push_back(v);
	}
	void push(std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic>&& v)
	{
		stack.push_back(v);
	}
	size_t size()
	{
		return stack.size();
	}
	size_t sizeoffset()
	{
		return size() - offset;
	}
	void pop()
	{
		stack.pop_back();
	}
	void remove(int index)
	{
		stack.erase(stack.begin() + (index + offset));
	}
	std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic>& top()
	{
		return stack[size() - 1];
	}
	std::refcount_ptr<std::bitsetdynamic, std::bitsetdynamic>& get(size_t n)
	{
		return stack[n + offset];
	}
	void set_Offset(size_t v)
	{
		offset = v;
	}
	size_t get_Offset()
	{
		return offset;
	}
};

