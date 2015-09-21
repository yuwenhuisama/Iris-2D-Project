#ifndef _H_IRISFLOAT_
#define _H_IRISFLOAT_

#include "IrisClass.h"
#include "IrisValue.h"
#include "IrisMethod.h"
#include "IrisIntegerTag.h"
#include "IrisInterpreter.h"
#include "IrisFloatTag.h"
#include "IrisGC.h"

class IrisFloat : public IrisClass
{
private:

	enum class Operation {
		Add = 0,
		Sub,
		Mul,
		Div,
		Power,

		Equal,
		NotEqual,
		BigThan,
		BigThanOrEqual,
		LessThan,
		LessThanOrEqual,
	};

	static IrisValue CmpOperation(Operation eOperationType, IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment){
		IrisFloatTag* pFloat = (IrisFloatTag*)ivObj.GetInstanceNativePointer();
		IrisFloatTag iftRightFloat;
		// 如果右边为Integer，则转化为Float之间的运算
		if ((*ivsValues)[0].GetObjectPointer()->GetClass()->GetClassName() == "Integer") {
			// 获取右边的值
			IrisIntegerTag* pRightInteger = (IrisIntegerTag*)(*ivsValues)[0].GetInstanceNativePointer();
			// 将右边对象转换为Float
			iftRightFloat = (IrisFloatTag)(*pRightInteger);
		}
		else {
			iftRightFloat = *((IrisFloatTag*)(*ivsValues)[0].GetInstanceNativePointer());
		}
		bool bResult = false;
		switch (eOperationType)
		{
		case IrisFloat::Operation::Equal:
			bResult = pFloat->Equal(iftRightFloat);
			break;
		case IrisFloat::Operation::NotEqual:
			bResult = pFloat->NotEqual(iftRightFloat);
			break;
		case IrisFloat::Operation::BigThan:
			bResult = pFloat->BigThan(iftRightFloat);
			break;
		case IrisFloat::Operation::BigThanOrEqual:
			bResult = pFloat->BigThanOrEqual(iftRightFloat);
			break;
		case IrisFloat::Operation::LessThan:
			bResult = pFloat->LessThan(iftRightFloat);
			break;
		case IrisFloat::Operation::LessThanOrEqual:
			bResult = pFloat->LessThanOrEqual(iftRightFloat);
			break;
		default:
			break;
		}
		if (bResult) {
			return IrisInterpreter::CurInstance()->True();
		}
		else {
			return IrisInterpreter::CurInstance()->False();
		}
	}

	static IrisValue CastOperation(Operation eOperationType, IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		IrisValue ivValue;
		IrisFloatTag* pFloat = (IrisFloatTag*)ivObj.GetInstanceNativePointer();
		IrisFloatTag iftRightFloat;
		// 如果右边为Integer，则转化为Float之间的运算
		if ((*ivsValues)[0].GetObjectPointer()->GetClass()->GetClassName() == "Integer") {
			// 获取右边的值
			IrisIntegerTag* pRightInteger = (IrisIntegerTag*)(*ivsValues)[0].GetInstanceNativePointer();
			// 将右边对象转换为Float
			iftRightFloat = (IrisFloatTag)(*pRightInteger);
		}
		else {
			iftRightFloat = *((IrisFloatTag*)(*ivsValues)[0].GetInstanceNativePointer());
		}
		// 新建临时Float对象作为结果
		ivValue = IrisInterpreter::CurInstance()->GetIrisClass("Float")->CreateInstance(nullptr, pContextEnvironment);
		// 获取新建对象的Native Pointer
		IrisFloatTag* pResultFloat = (IrisFloatTag*)ivValue.GetInstanceNativePointer();
		// 执行运算并保存数据
		switch (eOperationType)
		{
		case(Operation::Add) :
			(*pResultFloat) = pFloat->Add(iftRightFloat);
			break;
		case(Operation::Sub) :
			(*pResultFloat) = pFloat->Sub(iftRightFloat);
			break;
		case(Operation::Mul) :
			(*pResultFloat) = pFloat->Mul(iftRightFloat);
			break;
		case(Operation::Div) :
			(*pResultFloat) = pFloat->Div(iftRightFloat);
			break;
		case(Operation::Power) :
			(*pResultFloat) = pFloat->Power(iftRightFloat);
			break;
		default:
			break;
		}
		return ivValue;
	}

public:

	static IrisValue InitializeFunction(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		return ivObj;
	}

	static IrisValue Add(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		return CastOperation(Operation::Add, ivObj, ivsValues, ivsVariableValues, pContextEnvironment);
	}

	static IrisValue Sub(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		return CastOperation(Operation::Sub, ivObj, ivsValues, ivsVariableValues, pContextEnvironment);
	}

	static IrisValue Mul(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		return CastOperation(Operation::Mul, ivObj, ivsValues, ivsVariableValues, pContextEnvironment);
	}

	static IrisValue Div(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		return CastOperation(Operation::Div, ivObj, ivsValues, ivsVariableValues, pContextEnvironment);
	}

	static IrisValue Power(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		return CastOperation(Operation::Power, ivObj, ivsValues, ivsVariableValues, pContextEnvironment);
	}

	static IrisValue Equal(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		return CmpOperation(Operation::Equal, ivObj, ivsValues, ivsVariableValues, pContextEnvironment);
	}

	static IrisValue NotEqual(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		return CmpOperation(Operation::NotEqual, ivObj, ivsValues, ivsVariableValues, pContextEnvironment);
	}

	static IrisValue BigThan(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		return CmpOperation(Operation::BigThan, ivObj, ivsValues, ivsVariableValues, pContextEnvironment);
	}

	static IrisValue BigThanOrEqual(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		return CmpOperation(Operation::BigThanOrEqual, ivObj, ivsValues, ivsVariableValues, pContextEnvironment);
	}

	static IrisValue LessThan(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		return CmpOperation(Operation::LessThan, ivObj, ivsValues, ivsVariableValues, pContextEnvironment);
	}

	static IrisValue LessThanOrEqual(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		return CmpOperation(Operation::LessThanOrEqual, ivObj, ivsValues, ivsVariableValues, pContextEnvironment);
	}

	static IrisValue Plus(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		IrisFloatTag* pFloat = (IrisFloatTag*)ivObj.GetInstanceNativePointer();
		IrisValue ivValue = IrisInterpreter::CurInstance()->GetIrisClass("Float")->CreateInstanceByInstantValue(pFloat->m_dFloat);
		return ivValue;
	}

	static IrisValue Minus(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		IrisFloatTag* pFloat = (IrisFloatTag*)ivObj.GetInstanceNativePointer();
		IrisValue ivValue = IrisInterpreter::CurInstance()->GetIrisClass("Float")->CreateInstanceByInstantValue(-pFloat->m_dFloat);
		return ivValue;
	}

	static IrisValue ToString(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		IrisFloatTag* pFloat = (IrisFloatTag*)ivObj.GetInstanceNativePointer();
		return IrisInterpreter::CurInstance()->GetIrisClass("String")->CreateInstanceByInstantValue(pFloat->ToString());
	}

public:
	int GetTrustteeSize() {
		return sizeof(IrisFloatTag);
	}

	void* NativeAlloc() {
		return new IrisFloatTag(0.0);
	}

	void NativeFree(void* pNativePointer) {
		delete (IrisFloatTag*)pNativePointer;
	}

	void NativeClassDefine() {
		AddInstanceMethod(new IrisMethod("__format", InitializeFunction, 0, false));
		AddInstanceMethod(new IrisMethod("+", Add, 1, false));
		AddInstanceMethod(new IrisMethod("-", Sub, 1, false));
		AddInstanceMethod(new IrisMethod("*", Mul, 1, false));
		AddInstanceMethod(new IrisMethod("/", Div, 1, false));
		AddInstanceMethod(new IrisMethod("**", Power, 1, false));

		AddInstanceMethod(new IrisMethod("==", Equal, 1, false));
		AddInstanceMethod(new IrisMethod("!=", NotEqual, 1, false));
		AddInstanceMethod(new IrisMethod(">", BigThan, 1, false));
		AddInstanceMethod(new IrisMethod(">=", BigThanOrEqual, 1, false));
		AddInstanceMethod(new IrisMethod("<", LessThan, 1, false));
		AddInstanceMethod(new IrisMethod("<=", LessThanOrEqual, 1, false));

		AddInstanceMethod(new IrisMethod("__plus", Plus, 0, false));
		AddInstanceMethod(new IrisMethod("__minus", Minus, 0, false));

		AddInstanceMethod(new IrisMethod("to_string", ToString, 0, false));
	}

	virtual void* GetLiteralObject(char* szLiterral) {
		return new IrisFloatTag(szLiterral);
	}

	static double GetFloatData(IrisValue& ivValue) {
		return ((IrisFloatTag*)ivValue.GetInstanceNativePointer())->m_dFloat;
	}

	IrisValue CreateInstanceByInstantValue(char* szLiterral){
		IrisValue ivValue;
		IrisObject* pObject = new IrisObject();
		pObject->m_pClass = this;
		IrisFloatTag* pFloat = new IrisFloatTag(szLiterral);
		pObject->m_pNativeObject = pFloat;
		ivValue.m_pObject = pObject;

		IrisGC::AddSize(sizeof(IrisObject) + pObject->GetClass()->GetTrustteeSize());
		IrisGC::Start();

		// 将新对象保存到堆里
		IrisInterpreter::CurInstance()->AddNewInstanceToHeap(ivValue);
		return ivValue;
	}

	IrisValue CreateInstanceByInstantValue(double dValue){
		IrisValue ivValue;
		IrisObject* pObject = new IrisObject();
		pObject->m_pClass = this;
		IrisFloatTag* pFloat = new IrisFloatTag(dValue);
		pObject->m_pNativeObject = pFloat;
		ivValue.m_pObject = pObject;

		IrisGC::AddSize(sizeof(IrisObject) + pObject->GetClass()->GetTrustteeSize());
		IrisGC::Start();

		// 将新对象保存到堆里
		IrisInterpreter::CurInstance()->AddNewInstanceToHeap(ivValue);
		return ivValue;
	}

	IrisFloat(IrisClass* pSuperClass = nullptr);
	~IrisFloat();
};

#endif