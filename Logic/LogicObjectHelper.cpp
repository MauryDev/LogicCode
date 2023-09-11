#include "LogicObjectHelper.hpp"
void LogicCode::ObjectHelper::DefaultBitset_Init()
{
    static bool inited = false;
    if (inited)
    {
        return;
    }
    size_t sizelen = 1;
    Bitset_FALSE = NewBitset(sizelen);
    Bitset_FALSE->set(0, false);
    Bitset_TRUE = NewBitset(sizelen);
    Bitset_TRUE->set(0, true);

}
LogicCode::ObjectView<std::nullptr_t> LogicCode::ObjectHelper::New()
{
    return {};
}

LogicCode::ObjectView<LogicCode::LogicNumber> LogicCode::ObjectHelper::NewNumber(LogicNumber val)
{
	ObjectView<LogicNumber> variable = { Object::refcount_ptr_elem::make((size_t)sizeof(val)) };
	*variable = val;
	variable.set_type(ObjectType::Number);
	return variable;
}

LogicCode::ObjectView<LogicCode::LogicInteger> LogicCode::ObjectHelper::NewInteger(LogicInteger val)
{
	ObjectView<LogicInteger> variable = { Object::refcount_ptr_elem::make((size_t)sizeof(val)) };
	*variable = val;
	variable.set_type(ObjectType::Integer);
	return variable;
}

LogicCode::ObjectView<LogicCode::LogicBitset> LogicCode::ObjectHelper::NewBitset(size_t len)
{
	auto lenarr = LogicBitset::GetBufferSize(len);
	auto lenobj = LogicBitset::GetMemorySize(lenarr);
	ObjectView<LogicBitset> variable = { Object::refcount_ptr_elem::make(lenobj) };
	variable.set_type(ObjectType::Bitset);
   
	variable->_size = len;
	
	memset(variable->data(), 0, sizeof(LogicBitset::Bits) * lenarr);

	return variable;
}

LogicCode::ObjectView<LogicCode::LogicBitset> LogicCode::ObjectHelper::NewBitset(bool v)
{
     
    DefaultBitset_Init();
	return v ? Bitset_TRUE : Bitset_FALSE;
}

LogicCode::ObjectView<LogicCode::LogicRefBitset> LogicCode::ObjectHelper::NewRefBitset(const char* key, std::refcount_ptr<VariableData>& state)
{
	auto keylen = key == NULL ? 0 : strlen(key);
	ObjectView<LogicRefBitset> variable = { Object::refcount_ptr_elem::make(sizeof(LogicRefBitset) + keylen + 1) };
	variable.set_type(ObjectType::RefBitset);
    auto refbit = variable.ToPtr();

    refbit->scope = state;
	refbit->name.size = keylen;
	memcpy_s((void*)refbit->name.txt, keylen + 1, key, keylen + 1);

	return variable;
}

LogicCode::ObjectView<LogicCode::LogicString> LogicCode::ObjectHelper::NewString(const char* val)
{
	size_t size = 0;
	if (val != NULL)
	{
		size = strlen(val);
        ObjectView<LogicString> variable = { Object::refcount_ptr_elem::make(size + 1 + sizeof(LogicString)) };
        variable.set_type(ObjectType::String);

        auto str = variable.ToPtr();
        str->size = size;
        memcpy((void*)str->txt, val, size + 1);

        return variable;
    }
    else
    {

        return {};
    }


	

}

LogicCode::ObjectView<LogicCode::LogicString> LogicCode::ObjectHelper::NewStringLen(size_t bufferlen)
{
	size_t size = bufferlen;


	ObjectView<LogicString> variable = { Object::refcount_ptr_elem::make(size + 1 + sizeof(LogicString)) };
	variable.set_type(ObjectType::String);

    auto str = variable.ToPtr();
    str->size = size;
	return variable;
}

LogicCode::ObjectView<LogicCode::LogicFunctionObject> LogicCode::ObjectHelper::NewFunctionNative(LogicCodeState* state, FunctionData::FunctionNative& fnative)
{
	auto len = LogicFunctionObject::GetMemorySize(FunctionData::FunctionType::Native);
	ObjectView<LogicFunctionObject> variable = { Object::refcount_ptr_elem::make(len) };
	auto logicfnobj = variable.ToPtr();

	logicfnobj->type = FunctionData::FunctionType::Native;
	logicfnobj->parentscope = state->scope;
	logicfnobj->get_nativefn() = fnative;
	variable.set_type(ObjectType::Function);
	return variable;
}

LogicCode::ObjectView<LogicCode::LogicFunctionObject> LogicCode::ObjectHelper::NewFunctionNative(LogicCodeState* state, FunctionData::FunctionNative&& fnative)
{
	return NewFunctionNative(state,fnative);
}

LogicCode::ObjectView<LogicCode::LogicFunctionObject> LogicCode::ObjectHelper::NewFunctionRuntime(LogicCodeState* state, FunctionData::FunctionRuntime& fruntime)
{
	auto len = LogicFunctionObject::GetMemorySize(FunctionData::FunctionType::Runtime);
	ObjectView<LogicFunctionObject> variable = { Object::refcount_ptr_elem::make(len) };
	auto logicfnobj = variable.ToPtr();
	logicfnobj->type = FunctionData::FunctionType::Runtime;
	logicfnobj->parentscope = state->scope;
	logicfnobj->get_runtimefn() = fruntime;
	
	variable.set_type(ObjectType::Function);
	return variable;
}

LogicCode::ObjectView<LogicCode::LogicFunctionObject> LogicCode::ObjectHelper::NewFunctionRuntime(LogicCodeState* state, FunctionData::FunctionRuntime&& fruntime)
{
	return NewFunctionRuntime(state,fruntime);
}

LogicCode::ObjectView<LogicCode::LogicBitset> LogicCode::ObjectHelper::CopyBitset(LogicCode::LogicBitset* bitset)
{
    if (bitset == NULL)
    {
        return {};
    }
    auto len = bitset->size();
    auto ret = NewBitset(len);
    for (size_t i = 0; i < len; i++)
    {
        ret->set(i, bitset->get(i));
    }
	return ret;
}

LogicCode::ObjectView<LogicCode::LogicPointer> LogicCode::ObjectHelper::NewPointer(void* ptr)
{
    ObjectView<LogicPointer> variable = { Object::refcount_ptr_elem::make(sizeof(LogicPointer)) };
    *variable = ptr;
    variable.set_type(ObjectType::Pointer);

    return variable;
}

LogicCode::ObjectView<LogicCode::LogicUserObject> LogicCode::ObjectHelper::NewUserObject(LogicUserClass* klass, size_t len)
{
    auto lenmalloc =LogicUserObject::GetMemorySize(len);
    ObjectView<LogicUserObject> variable = { Object::refcount_ptr_elem::make(lenmalloc) };
    variable->klass = klass;
    variable.set_type(ObjectType::UserObject);

	return variable;
}
