#ifndef _H_IRISINTEGER_
#define _H_IRISINTEGER_
#include "IrisClass.h"
#include "IrisValue.h"
#include "IrisMethod.h"
#include "IrisIntegerTag.h"
#include "IrisInterpreter.h"
#include "IrisFloatTag.h"
#include "IrisGC.h"

class IrisInteger : public IrisClass
{
private:

	enum class Operation {
		Add = 0,
		Sub,
		Mul,
		Div,
		Power,
		Mod,

		Shr,
		Shl,
		Sar,
		Sal,
		BitXor,
		BitAnd,
		BitOr,

		Equal,
		NotEqual,
		BigThan,
		BigThanOrEqual,
		LessThan,
		LessThanOrEqual,
	};

	static IrisValue CmpOperation(Operation eOperationType, IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		IrisIntegerTag* pInteger = (IrisIntegerTag*)ivObj.GetInstanceNativePointer();
		bool bResult = false;
		// 如果右边为Float，则转化为Float之间的运算
		if ((*ivsValues)[0].GetObject()->GetClass()->GetClassName() == "Float") {
			// 获取被加数
			IrisFloatTag* pRightFloat = (IrisFloatTag*)(*ivsValues)[0].GetInstanceNativePointer();
			// 将当前对象转换为Float
			IrisFloatTag iftLeftFloat = (IrisFloatTag)(*pInteger);
			// 执行运算并保存数据
			switch (eOperationType)
			{
			case(Operation::Equal) :
				bResult = iftLeftFloat.Equal(*pRightFloat);
				break;
			case(Operation::NotEqual) :
				bResult = iftLeftFloat.NotEqual(*pRightFloat);
				break;
			case(Operation::BigThan) :
				bResult = iftLeftFloat.BigThan(*pRightFloat);
				break;
			case(Operation::BigThanOrEqual) :
				bResult = iftLeftFloat.BigThanOrEqual(*pRightFloat);
				break;
			case(Operation::LessThan) :
				bResult = iftLeftFloat.LessThan(*pRightFloat);
				break;
			case(Operation::LessThanOrEqual) :
				bResult = iftLeftFloat.LessThanOrEqual(*pRightFloat);
				break;
			default:
				break;
			}
		}
		else {
			// 获取被加数
			IrisIntegerTag* pRightInteger = (IrisIntegerTag*)(*ivsValues)[0].GetInstanceNativePointer();
			// 执行并保存数据
			switch (eOperationType)
			{
			case(Operation::Equal) :
				bResult = pInteger->Equal(*pRightInteger);
				break;
			case(Operation::NotEqual) :
				bResult = pInteger->NotEqual(*pRightInteger);
				break;
			case(Operation::BigThan) :
				bResult = pInteger->BigThan(*pRightInteger);
				break;
			case(Operation::BigThanOrEqual) :
				bResult = pInteger->BigThanOrEqual(*pRightInteger);
				break;
			case(Operation::LessThan) :
				bResult = pInteger->LessThan(*pRightInteger);
				break;
			case(Operation::LessThanOrEqual) :
				bResult = pInteger->LessThanOrEqual(*pRightInteger);
				break;
			default:
				break;
			}
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
		IrisIntegerTag* pInteger = (IrisIntegerTag*)ivObj.GetInstanceNativePointer();
		// 如果右边为Float，则转化为Float之间的运算
		if ((*ivsValues)[0].GetObject()->GetClass()->GetClassName() == "Float") {
			// 获取被加数
			IrisFloatTag* pRightFloat = (IrisFloatTag*)(*ivsValues)[0].GetInstanceNativePointer();
			// 将当前对象转换为Float
			IrisFloatTag iftLeftFloat = (IrisFloatTag)(*pInteger);
			if (eOperationType != Operation::Mod) {
				// 新建临时Float对象作为结果
				ivValue = IrisInterpreter::CurInstance()->GetIrisClass("Float")->CreateInstance(nullptr, pContextEnvironment);
				// 获取新建对象的Native Pointer
				IrisFloatTag* pResultFloat = (IrisFloatTag*)ivValue.GetInstanceNativePointer();
				// 执行运算并保存数据
				switch (eOperationType)
				{
				case(Operation::Add) :
					(*pResultFloat) = iftLeftFloat.Add(*pRightFloat);
					break;
				case(Operation::Sub) :
					(*pResultFloat) = iftLeftFloat.Sub(*pRightFloat);
					break;
				case(Operation::Mul) :
					(*pResultFloat) = iftLeftFloat.Mul(*pRightFloat);
					break;
				case(Operation::Div) :
					(*pResultFloat) = iftLeftFloat.Div(*pRightFloat);
					break;
				case(Operation::Power) :
					(*pResultFloat) = iftLeftFloat.Power(*pRightFloat);
					break;
				default:
					break;
				}
			}
			else {
				// 新建临时Integer对象作为结果
				ivValue = IrisInterpreter::CurInstance()->GetIrisClass("Integer")->CreateInstance(nullptr, pContextEnvironment);
				// 获取新建对象的Native Pointer
				IrisIntegerTag* pResultInteger = (IrisIntegerTag*)ivValue.GetInstanceNativePointer();
				(*pResultInteger) = pInteger->Mod((IrisIntegerTag)(*pRightFloat));
			}
		}
		else {
			// 获取被加数
			IrisIntegerTag* pRightInteger = (IrisIntegerTag*)(*ivsValues)[0].GetInstanceNativePointer();
			// 新建临时Integer对象作为结果
			ivValue = IrisInterpreter::CurInstance()->GetIrisClass("Integer")->CreateInstance(nullptr, pContextEnvironment);
			// 获取新建对象的Native Pointer
			IrisIntegerTag* pResultInteger = (IrisIntegerTag*)ivValue.GetInstanceNativePointer();
			// 执行并保存数据
			switch (eOperationType)
			{
			case(Operation::Add) :
				(*pResultInteger) = pInteger->Add(*pRightInteger);
				break;
			case(Operation::Sub) :
				(*pResultInteger) = pInteger->Sub(*pRightInteger);
				break;
			case(Operation::Mul) :
				(*pResultInteger) = pInteger->Mul(*pRightInteger);
				break;
			case(Operation::Div) :
				(*pResultInteger) = pInteger->Div(*pRightInteger);
				break;
			case(Operation::Power) :
				(*pResultInteger) = pInteger->Power(*pRightInteger);
				break;
			case(Operation::Mod) :
				(*pResultInteger) = pInteger->Mod(*pRightInteger);
				break;
			default:
				break;
			}
		}
		return ivValue;
	}

	static IrisValue Operation(Operation eOperationType, IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		IrisValue ivValue;
		IrisIntegerTag* pInteger = (IrisIntegerTag*)ivObj.GetInstanceNativePointer();
		// 获取Right
		IrisIntegerTag* pRightInteger = (IrisIntegerTag*)(*ivsValues)[0].GetInstanceNativePointer();
		// 新建临时Integer对象作为结果
		ivValue = IrisInterpreter::CurInstance()->GetIrisClass("Integer")->CreateInstance(nullptr, pContextEnvironment);
		// 获取新建对象的Native Pointer
		IrisIntegerTag* pResultInteger = (IrisIntegerTag*)ivValue.GetInstanceNativePointer();
		// 执行并保存数据
		switch (eOperationType)
		{
		case(Operation::Shr) :
			(*pResultInteger) = pInteger->Shr(*pRightInteger);
			break;
		case(Operation::Shl) :
			(*pResultInteger) = pInteger->Shl(*pRightInteger);
			break;
		case(Operation::Sar) :
			(*pResultInteger) = pInteger->Sar(*pRightInteger);
			break;
		case(Operation::Sal) :
			(*pResultInteger) = pInteger->Sal(*pRightInteger);
			break;
		case(Operation::BitXor) :
			(*pResultInteger) = pInteger->BitXor(*pRightInteger);
			break;
		case(Operation::BitAnd) :
			(*pResultInteger) = pInteger->BitAnd(*pRightInteger);
			break;
		case(Operation::BitOr) :
			(*pResultInteger) = pInteger->BitOr(*pRightInteger);
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
	static IrisValue Mod(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		return CastOperation(Operation::Mod, ivObj, ivsValues, ivsVariableValues, pContextEnvironment);
	}

	static IrisValue Shl(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		return CastOperation(Operation::Shl, ivObj, ivsValues, ivsVariableValues, pContextEnvironment);
	}

	static IrisValue Shr(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		return Operation(Operation::Shr, ivObj, ivsValues, ivsVariableValues, pContextEnvironment);
	}

	static IrisValue Sar(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		return Operation(Operation::Sar, ivObj, ivsValues, ivsVariableValues, pContextEnvironment);
	}

	static IrisValue Sal(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		return Operation(Operation::Sal, ivObj, ivsValues, ivsVariableValues, pContextEnvironment);
	}

	static IrisValue BitXor(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		return Operation(Operation::BitXor, ivObj, ivsValues, ivsVariableValues, pContextEnvironment);
	}

	static IrisValue BitAnd(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		return Operation(Operation::BitAnd, ivObj, ivsValues, ivsVariableValues, pContextEnvironment);
	}

	static IrisValue BitOr(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		return Operation(Operation::BitOr, ivObj, ivsValues, ivsVariableValues, pContextEnvironment);
	}

	static IrisValue BitNot(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValuse, IrisContextEnvironment* pContextEnvironment) {
		IrisValue ivValue;
		IrisIntegerTag* pInteger = (IrisIntegerTag*)ivObj.GetInstanceNativePointer();
		// 新建临时Integer对象作为结果
		ivValue = IrisInterpreter::CurInstance()->GetIrisClass("Integer")->CreateInstance(nullptr, pContextEnvironment);
		// 获取新建对象的Native Pointer
		IrisIntegerTag* pResultInteger = (IrisIntegerTag*)ivValue.GetInstanceNativePointer();
		(*pResultInteger) = pInteger->BitNot();
		return ivValue;
	}

	static IrisValue Equal(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValuse, IrisContextEnvironment* pContextEnvironment) {
		return CmpOperation(Operation::Equal, ivObj, ivsValues, ivsVariableValuse, pContextEnvironment);
	}

	static IrisValue NotEqual(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValuse, IrisContextEnvironment* pContextEnvironment) {
		return CmpOperation(Operation::NotEqual, ivObj, ivsValues, ivsVariableValuse, pContextEnvironment);
	}

	static IrisValue BigThan(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValuse, IrisContextEnvironment* pContextEnvironment) {
		return CmpOperation(Operation::BigThan, ivObj, ivsValues, ivsVariableValuse, pContextEnvironment);
	}

	static IrisValue BigThanOrEqual(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValuse, IrisContextEnvironment* pContextEnvironment) {
		return CmpOperation(Operation::BigThanOrEqual, ivObj, ivsValues, ivsVariableValuse, pContextEnvironment);
	}

	static IrisValue LessThan(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValuse, IrisContextEnvironment* pContextEnvironment) {
		return CmpOperation(Operation::LessThan, ivObj, ivsValues, ivsVariableValuse, pContextEnvironment);
	}

	static IrisValue LessThanOrEqual(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValuse, IrisContextEnvironment* pContextEnvironment) {
		return CmpOperation(Operation::LessThanOrEqual, ivObj, ivsValues, ivsVariableValuse, pContextEnvironment);
	}

	static IrisValue Plus(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		IrisIntegerTag* pInteger = (IrisIntegerTag*)ivObj.GetInstanceNativePointer();
		IrisValue ivValue = IrisInterpreter::CurInstance()->GetIrisClass("Integer")->CreateInstanceByInstantValue(pInteger->m_nInteger);
		return ivValue;
	}

	static IrisValue Minus(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		IrisIntegerTag* pInteger = (IrisIntegerTag*)ivObj.GetInstanceNativePointer();
		IrisValue ivValue = IrisInterpreter::CurInstance()->GetIrisClass("Integer")->CreateInstanceByInstantValue(-pInteger->m_nInteger);
		return ivValue;
	}

	static IrisValue ToString(IrisValue& ivObj, IrisValues* ivsValues, IrisValues* ivsVariableValues, IrisContextEnvironment* pContextEnvironment) {
		IrisIntegerTag* pInteger = (IrisIntegerTag*)ivObj.GetInstanceNativePointer();
		return IrisInterpreter::CurInstance()->GetIrisClass("String")->CreateInstanceByInstantValue(pInteger->ToString());
	}

public:
	IrisInteger(IrisClass* pSuperClass = nullptr);

	int GetTrustteeSize() {
		return sizeof(IrisIntegerTag);
	}

	void* NativeAlloc() {
		return new IrisIntegerTag(0);
	}

	void NativeFree(void* pNativePointer) {
		delete (IrisIntegerTag*)pNativePointer;
	}

	void NativeClassDefine() {
		AddInstanceMethod(new IrisMethod("__format", InitializeFunction, 0, false));
		AddInstanceMethod(new IrisMethod("+", Add, 1, false));
		AddInstanceMethod(new IrisMethod("-", Sub, 1, false));
		AddInstanceMethod(new IrisMethod("*", Mul, 1, false));
		AddInstanceMethod(new IrisMethod("/", Div, 1, false));
		AddInstanceMethod(new IrisMethod("**", Power, 1, false));
		AddInstanceMethod(new IrisMethod("<<", Shl, 1, false));
		AddInstanceMethod(new IrisMethod(">>", Shr, 1, false));
		AddInstanceMethod(new IrisMethod("<<<", Sal, 1, false));
		AddInstanceMethod(new IrisMethod(">>>", Sar, 1, false));
		AddInstanceMethod(new IrisMethod("^", BitXor, 1, false));
		AddInstanceMethod(new IrisMethod("&", BitAnd, 1, false));
		AddInstanceMethod(new IrisMethod("|", BitOr, 1, false));
		AddInstanceMethod(new IrisMethod("~", BitNot, 0, false));
		AddInstanceMethod(new IrisMethod("%", Mod, 1, false));

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
		return new IrisIntegerTag(szLiterral);
	}

	static int GetIntData(IrisValue& ivValue) {
		return ((IrisIntegerTag*)ivValue.GetInstanceNativePointer())->m_nInteger;
	}

	IrisValue CreateInstanceByInstantValue(char* szLiterral) {
		IrisValue ivValue;
		IrisObject* pObject = new IrisObject();
		pObject->m_pClass = this;
		IrisIntegerTag* pInteger = new IrisIntegerTag(szLiterral);
		pObject->m_pNativeObject = pInteger;
		ivValue.m_pObject = pObject;

		IrisGC::AddSize(sizeof(IrisObject) + pObject->GetClass()->GetTrustteeSize());
		IrisGC::Start();

		// 将新对象保存到堆里
		IrisInterpreter::CurInstance()->AddNewInstanceToHeap(ivValue);
		return ivValue;
	}

	IrisValue CreateInstanceByInstantValue(int nValue) {
		IrisValue ivValue;
		IrisObject* pObject = new IrisObject();
		pObject->m_pClass = this;
		IrisIntegerTag* pInteger = new IrisIntegerTag(nValue);
		pObject->m_pNativeObject = pInteger;
		ivValue.m_pObject = pObject;

		IrisGC::AddSize(sizeof(IrisObject) + pObject->GetClass()->GetTrustteeSize());
		IrisGC::Start();

		// 将新对象保存到堆里
		IrisInterpreter::CurInstance()->AddNewInstanceToHeap(ivValue);
		return ivValue;
	}

	~IrisInteger();

	friend class IrisFloatTag;
};

#endif