#pragma once

#include "LogicObjectView.hpp"
#include "LogicStructs.hpp"
#include "LogicString.hpp"
#include "LogicRefBitset.hpp"
#include "bitsetdynamic.hpp"
#include "LogicFunctionObject.hpp"
namespace LogicCode::ObjectHelper
{
	ObjectView<std::nullptr_t> New();
	
	ObjectView<LogicNumber> NewNumber(LogicNumber val);
	ObjectView<LogicInteger> NewInteger(LogicInteger val);

	

	ObjectView<std::bitsetdynamic> NewBitset(size_t len);

	
	ObjectView<std::bitsetdynamic> NewBitset(bool v);
	ObjectView<LogicRefBitset> NewRefBitset(const char* key, std::refcount_ptr<VariableData>& state);

	ObjectView<LogicString> NewString(const char* val);
	ObjectView<LogicFunctionObject> NewFunctionNative(LogicCodeState* state, FunctionData::FunctionNative& fnative);
	ObjectView<LogicFunctionObject> NewFunctionNative(LogicCodeState* state, FunctionData::FunctionNative&& fnative);
	ObjectView<LogicFunctionObject> NewFunctionRuntime(LogicCodeState* state, FunctionData::FunctionRuntime& fruntime);
	ObjectView<LogicFunctionObject> NewFunctionRuntime(LogicCodeState* state, FunctionData::FunctionRuntime&& fruntime);

	//static refcount_elem* NewUserData(size_t len);
	//static refcount_elem* NewLightUserData(void* ptr);


}

