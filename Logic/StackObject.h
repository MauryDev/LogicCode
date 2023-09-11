#ifndef Logic_StackObject_H
#define Logic_StackObject_H
#include <vector>
#include "refcount_ptr.hpp"
#include "bitsetdynamic.hpp"
#include "LogicObject.hpp"
#include "LogicObjectView.hpp"
class StackObject
{
private:
	std::vector<LogicCode::Object::refcount_ptr_elem> stack;
	size_t offset;
public:

	StackObject()
	{
		offset = 0;
	}
	~StackObject()
	{
		offset = 0;
	}
	size_t absidx(int idx)
	{
		return idx >= 0 ? idx + offset : size() - abs(idx);
	}
	template<typename T>
	void push(LogicCode::ObjectView<T>& v)
	{
	
		stack.push_back(v);
	}
	template<typename T>
	void push(LogicCode::ObjectView<T>&& v)
	{
		stack.push_back(v);
	}
	void push(LogicCode::Object::refcount_ptr_elem& v)
	{
		stack.push_back(v);
	}
	void push(LogicCode::Object::refcount_ptr_elem&& v)
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
	LogicCode::Object::refcount_ptr_elem& top()
	{
		return stack.back();
	}
	LogicCode::Object::refcount_ptr_elem& get(size_t n)
	{
		return stack[n + offset];
	}
	template<typename T>
	LogicCode::ObjectView<T> getasview(size_t n)
	{
		return { stack[n + offset] };
	}
	template<typename T>
	LogicCode::ObjectView<T> topasview(size_t n)
	{
		return { stack[size() - 1] };
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

#endif