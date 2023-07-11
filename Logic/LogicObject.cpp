#include "LogicObject.hpp"
#include "LogicRefBitset.hpp"
#include "LogicFunctionObject.hpp"
void LogicCode::Object::Free(refcount_elem* _this)
{
	if (_this != NULL)
	{
		auto vtype = _this->obj.type;
		if (vtype == ObjectType::RefBitset)
		{
			LogicRefBitset::FromObject(_this->obj)->scope.dec_ref();
		}
		else if (vtype == ObjectType::Function)
		{
			auto fndata = LogicFunctionObject::FromObject(_this->obj);
			fndata->Free();
		}
		free(_this);
	}
}
