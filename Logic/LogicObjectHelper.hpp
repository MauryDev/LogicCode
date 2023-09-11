#pragma once

#include "LogicObjectView.hpp"
#include "LogicStructs.hpp"
#include "LogicString.hpp"
#include "LogicRefBitset.hpp"
#include "bitsetdynamic.hpp"
#include "LogicFunctionObject.hpp"
#include "LogicUserObject.h"
namespace LogicCode::ObjectHelper
{
    
    inline ObjectView<LogicBitset> Bitset_TRUE;
    inline ObjectView<LogicBitset> Bitset_FALSE;
    void DefaultBitset_Init();
	ObjectView<std::nullptr_t> New();
	ObjectView<LogicNumber> NewNumber(LogicNumber val);
	ObjectView<LogicInteger> NewInteger(LogicInteger val);
	ObjectView<LogicBitset> NewBitset(size_t len);
	ObjectView<LogicBitset> NewBitset(bool v);
	ObjectView<LogicRefBitset> NewRefBitset(const char* key, std::refcount_ptr<VariableData>& state);
	ObjectView<LogicString> NewString(const char* val);
	ObjectView<LogicString> NewStringLen(size_t bufferlen);
	ObjectView<LogicFunctionObject> NewFunctionNative(LogicCodeState* state, FunctionData::FunctionNative& fnative);
	ObjectView<LogicFunctionObject> NewFunctionNative(LogicCodeState* state, FunctionData::FunctionNative&& fnative);
	ObjectView<LogicFunctionObject> NewFunctionRuntime(LogicCodeState* state, FunctionData::FunctionRuntime& fruntime);
	ObjectView<LogicFunctionObject> NewFunctionRuntime(LogicCodeState* state, FunctionData::FunctionRuntime&& fruntime);
    
    ObjectView<LogicBitset> CopyBitset(LogicBitset* bitset);


    ObjectView<LogicPointer> NewPointer(void* ptr);
	ObjectView<LogicUserObject> NewUserObject(LogicUserClass* klass, size_t len);
    template <typename T>
    ObjectView<TLogicUserObject<T>> NewTUserObject(LogicUserClass* klass)
    {
        auto lenmalloc = TLogicUserObject<T>::GetMemorySize();
        ObjectView<TLogicUserObject<T>> variable = { Object::refcount_ptr_elem::make(lenmalloc) };
        variable->klass = klass;
        variable.set_type(ObjectType::UserObject);

        return variable;
    }


}

