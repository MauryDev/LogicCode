#include "LogicObject.hpp"
#include "LogicRefBitset.hpp"
#include "LogicFunctionObject.hpp"
#include "LogicUserObject.h"
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
        else if (vtype == ObjectType::UserObject)
        {
            auto userobject = _this->obj.ptr<LogicUserObject>();
            auto klass = userobject->klass;
            if (klass != NULL)
            {
                auto __gc = klass->__gc; 
                if (__gc != NULL)
                {
                    __gc(userobject);
                }
            }
        }
		free(_this);
	}
}
