#ifndef _H_IRISOBJECTBASE_
#define _H_IRISOBJECTBASE_

#include "IrisObject.h"
#include "IrisClass.h"
#include "IrisValue.h"
#include "IrisMethod.h"
#include "IrisInterpreter.h"
#include "IrisStringTag.h"
#include "IrisIntegerTag.h"

#include "IrisKernel.h"

class IrisObjectBase : public IrisClass
{
public:
	static IrisValue InitializeFunction(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		return ivObj;
	}

	static IrisValue GetClass(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		IrisObject* pObject = ivObj.GetObjectPointer()->GetClass()->m_pClassObject;
		return IrisValue::WrapObjectPointerToIrisValue(pObject);
	}

	static IrisValue GetObjectID(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		IrisObject* pObject = ivObj.GetObjectPointer();
		int nObjectID = pObject->GetObjectID();
		return IrisInterpreter::CurInstance()->GetIrisClass("Integer")->CreateInstanceByInstantValue(nObjectID);
	}

	static IrisValue ToString(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		const string& strClassName = ivObj.GetObjectPointer()->GetClass()->GetClassName();
		IrisValue ivStringObjectID = ivObj.GetObjectPointer()->CallInstanceFunction("object_id", pContextEnvironment, nullptr);
		const string& strObjectID = ((IrisIntegerTag*)ivStringObjectID.GetInstanceNativePointer())->ToString();
		string strOutString = "<" + strClassName + ":" + strObjectID + ">";
		return IrisInterpreter::CurInstance()->GetIrisClass("String")->CreateInstanceByInstantValue(strOutString);
	}

	static IrisValue Equal(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		const IrisValue& ivDestObj = (*ivsValues)[0];
		if (ivObj == ivDestObj){
			return IrisInterpreter::CurInstance()->True();
		}
		else {
			return IrisInterpreter::CurInstance()->False();
		}
	}

	static IrisValue NotEqual(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		IrisValue ivResult = ivObj.GetObjectPointer()->CallInstanceFunction("==", pContextEnvironment, ivsValues);
		if (ivResult == IrisInterpreter::CurInstance()->True()) {
			return IrisInterpreter::CurInstance()->False();
		}
		else{
			return IrisInterpreter::CurInstance()->True();
		}
	}

	static IrisValue LogicOr(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		IrisValue ivDest = (*ivsValues)[0];
		// 左右两边只要有一个不为nil或false那么就为true
		if (ivObj != IrisInterpreter::CurInstance()->False() && ivObj != IrisInterpreter::CurInstance()->Nil()) {
			return IrisInterpreter::CurInstance()->True();
		}
		else if (ivDest != IrisInterpreter::CurInstance()->False() && ivDest != IrisInterpreter::CurInstance()->Nil()){
			return IrisInterpreter::CurInstance()->True();
		}
		else {
			return IrisInterpreter::CurInstance()->False();
		}
	}

	static IrisValue LogicAnd(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		IrisValue ivDest = (*ivsValues)[0];
		// 左右两边只要有一个为nil或false那么就为false
		if (ivObj == IrisInterpreter::CurInstance()->False() || ivObj == IrisInterpreter::CurInstance()->Nil()) {
			return IrisInterpreter::CurInstance()->False();
		}
		else if (ivDest == IrisInterpreter::CurInstance()->False() && ivDest == IrisInterpreter::CurInstance()->Nil()){
			return IrisInterpreter::CurInstance()->False();
		}
		else {
			return IrisInterpreter::CurInstance()->True();
		}
	}

public:

	// 特殊处理
	void* NativeAlloc() {
		return nullptr;
	}

	void NativeClassDefine() {

		AddModule(IrisInterpreter::CurInstance()->GetIrisModule("Kernel"));

		AddInstanceMethod(new IrisMethod("__format", InitializeFunction, 0, false));
		AddInstanceMethod(new IrisMethod("object_id", GetObjectID, 0, false));
		AddInstanceMethod(new IrisMethod("class", GetClass, 0, false));
		AddInstanceMethod(new IrisMethod("to_string", ToString, 0, false));
		AddInstanceMethod(new IrisMethod("==", Equal, 1, false));
		AddInstanceMethod(new IrisMethod("!=", NotEqual, 1, false));
		AddInstanceMethod(new IrisMethod("&&", LogicAnd, 1, false));
		AddInstanceMethod(new IrisMethod("||", LogicOr, 1, false));
	}

	IrisObjectBase(IrisClass* pSuperClass = nullptr);
	~IrisObjectBase();
};

#endif