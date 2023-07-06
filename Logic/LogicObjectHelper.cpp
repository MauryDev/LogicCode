#include "LogicObjectHelper.hpp"

LogicCode::ObjectView<std::nullptr_t> LogicCode::ObjectHelper::New()
{
	ObjectView<std::nullptr_t> variable = { Object::refcount_ptr_elem::make((size_t)0) };
	variable.v->type = ObjectType::None;
	return variable;
}

LogicCode::ObjectView<LogicCode::LogicNumber> LogicCode::ObjectHelper::NewNumber(LogicNumber val)
{
	ObjectView<LogicNumber> variable = { Object::refcount_ptr_elem::make((size_t)sizeof(val)) };
	*variable = val;
	variable.v->type = ObjectType::Number;
	return variable;
}

LogicCode::ObjectView<LogicCode::LogicInteger> LogicCode::ObjectHelper::NewInteger(LogicInteger val)
{
	ObjectView<LogicInteger> variable = { Object::refcount_ptr_elem::make((size_t)sizeof(val)) };
	*variable = val;
	variable.v->type = ObjectType::Integer;
	return variable;
}

LogicCode::ObjectView<std::bitsetdynamic> LogicCode::ObjectHelper::NewBitset(size_t len)
{
	auto lenarr = std::bitsetdynamic::GetBufferSize(len);
	ObjectView<std::bitsetdynamic> variable = { Object::refcount_ptr_elem::make(lenarr) };
	variable.v->type = ObjectType::Bitset;

	auto& bd = variable.v->data<std::bitsetdynamic>();
	bd._size = len;
	memset(bd.data(), 0, sizeof(std::bitsetdynamic::Bits) * lenarr);

	return variable;
}

LogicCode::ObjectView<std::bitsetdynamic> LogicCode::ObjectHelper::NewBitset(bool v)
{

	ObjectView<std::bitsetdynamic> val = NewBitset((size_t)1);
	val->set(0, v);
	return val;
}

LogicCode::ObjectView<LogicCode::LogicRefBitset> LogicCode::ObjectHelper::NewRefBitset(const char* key, std::refcount_ptr<VariableData>& state)
{
	auto keylen = key == NULL ? 0 : strlen(key);
	ObjectView<LogicRefBitset> variable = { Object::refcount_ptr_elem::make(sizeof(LogicRefBitset) + keylen + 1) };
	variable.v->type = ObjectType::RefBitset;
	auto& refbit = variable.v->data<LogicRefBitset>();
	refbit.scope = state;
	refbit.name.size = keylen;
	memcpy_s((void*)refbit.name.txt, keylen + 1, key, keylen + 1);

	return variable;
}

LogicCode::ObjectView<LogicCode::LogicString> LogicCode::ObjectHelper::NewString(const char* val)
{
	size_t size = 0;
	if (val != NULL)
	{
		size = strlen(val);
	}


	ObjectView<LogicString> variable = { Object::refcount_ptr_elem::make(size) };
	variable.v->type = ObjectType::String;

	auto& str = variable.v->data<LogicString>();
	str.size = size;
	memcpy((void*)str.txt, val, size + 1);

	return variable;

}