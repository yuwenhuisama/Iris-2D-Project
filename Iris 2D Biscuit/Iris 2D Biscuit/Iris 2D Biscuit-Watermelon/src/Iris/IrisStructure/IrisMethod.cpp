#include "IrisMethod.h"
#include "IrisMethodBase.h"
#include "IrisStatementResult.h"
#include "IrisClass.h"
#include "IrisClosureBlock.h"

struct IrisMethod::UserFunction {
	 IrisFunctionHeader* m_pFunctionHeader = nullptr;
	 IrisBlock* m_pBlock = nullptr;
	 IrisBlock* m_pWithBlock = nullptr;
	 IrisBlock* m_pWithoutBlock = nullptr;

	 UserFunction(IrisFunctionHeader* pFunctionHeader, IrisBlock* pBlock, IrisBlock* pWithBlock, IrisBlock* pWithoutBlock) :m_pFunctionHeader(pFunctionHeader), m_pBlock(pBlock), m_pWithBlock(pWithBlock), m_pWithoutBlock(pWithoutBlock) {
	 }

	 ~UserFunction() {
		 if (m_pBlock) {
			 delete m_pBlock;
		 }
		 if (m_pWithBlock) {
			 delete m_pWithBlock;
		 }
		 if (m_pWithoutBlock) {
			 delete m_pWithoutBlock;
		 }
		 if (m_pFunctionHeader) {
			 delete m_pFunctionHeader;
		 }
	 }
};

const string& IrisMethod::GetMethodName() {
	return m_strMethodName;
}

IrisMethod::IrisMethod(const string& strMethodName, IrisNativeFunction pfNativeFunction, int nParameterAmount, bool bIsWithVariableParameter, MethodAuthority eAuthority) {
	m_strMethodName = strMethodName;
	m_eMethodType = MethodType::NativeMethod;
	m_uFunction.m_pfNativeFunction = pfNativeFunction;
	m_bIsWithVariableParameter = bIsWithVariableParameter;
	m_nParameterAmount = nParameterAmount;
	m_eAuthority = eAuthority;

	IrisClass* pMethodClass = nullptr;
	if (pMethodClass = IrisInterpreter::CurInstance()->GetIrisClass("Method")) {
		IrisValue ivValue = pMethodClass->CreateInstance(nullptr, nullptr);
		((IrisMethodBaseTag*)ivValue.GetObjectPointer()->m_pNativeObject)->SetMethod(this);
		m_pMethodObject = ivValue.GetObjectPointer();
	}
}

IrisMethod::IrisMethod(IrisFunctionHeader* pFunctionHeader, IrisBlock* pFunctionBlock, IrisBlock* pWithBlock, IrisBlock* pWithoutBlock, MethodAuthority eAuthority) {
	m_strMethodName = pFunctionHeader->m_pFunctionName->m_strIdentifier;
	m_eMethodType = MethodType::UserMethod;
	m_uFunction.m_pUserFunction = new UserFunction(pFunctionHeader, pFunctionBlock, pWithBlock, pWithoutBlock);
	m_bIsWithVariableParameter = (pFunctionHeader->m_pVariableParameter != nullptr);
	m_eAuthority = eAuthority;

	IrisValue ivValue = IrisInterpreter::CurInstance()->GetIrisClass("Method")->CreateInstance(nullptr, nullptr);
	((IrisMethodBaseTag*)ivValue.GetObjectPointer()->m_pNativeObject)->SetMethod(this);
	m_pMethodObject = ivValue.GetObjectPointer();
	m_nParameterAmount = !pFunctionHeader->m_pParameters ? 0 : pFunctionHeader->m_pParameters->GetSize();
}

IrisMethod::IrisMethod(IrisFunctionHeader* pFunctionHeader, MethodType eType, MethodAuthority eAuthority) {
	m_strMethodName = pFunctionHeader->m_pFunctionName->m_strIdentifier;
	m_eMethodType = eType;
	m_uFunction.m_pUserFunction = new UserFunction(pFunctionHeader, nullptr, nullptr, nullptr);
	m_bIsWithVariableParameter = false;
	m_eAuthority = eAuthority;

	IrisValue ivValue = IrisInterpreter::CurInstance()->GetIrisClass("Method")->CreateInstance(nullptr, nullptr);
	((IrisMethodBaseTag*)ivValue.GetObjectPointer()->m_pNativeObject)->SetMethod(this);
	m_pMethodObject = ivValue.GetObjectPointer();
	m_nParameterAmount = !pFunctionHeader->m_pParameters ? 0 : pFunctionHeader->m_pParameters->GetSize();
}

bool IrisMethod::_ParameterCheck(IrisValues* pParameters) {
	// 参数检查
	// 如果有可变参数，那么实际参数的个数至少要大于等于形式参数
	if (pParameters) {
		if (m_bIsWithVariableParameter) {
			return pParameters->size() >= (unsigned int) m_nParameterAmount;
		}
		// 如果没有可变参数，那么和实际参数必须要等于形式参数
		else {
			return pParameters->size() == m_nParameterAmount;
		}
	}
	else {
		return m_nParameterAmount == 0;
	}
}

IrisContextEnvironment* IrisMethod::_CreateContextEnvironment(IrisObject* pCaller, IrisValues* pParameters) {
	IrisContextEnvironment* pNewEnvironment = new IrisContextEnvironment();
	pNewEnvironment->m_eType = IrisContextEnvironment::EnvironmentType::Runtime;
	pNewEnvironment->m_uType.m_pCurObject = pCaller;
	pNewEnvironment->m_pCurMethod = this;

	// With Block and Without Block
	if (m_eMethodType == MethodType::UserMethod) {
		pNewEnvironment->m_pWithBlock = m_uFunction.m_pUserFunction->m_pWithBlock;
		pNewEnvironment->m_pWithouBlock = m_uFunction.m_pUserFunction->m_pWithoutBlock;
	}

	// 如果该方法是UserFunction则将参数作为局部变量添加进来
	if (pParameters && m_eMethodType == MethodType::UserMethod) {
		IrisValues::iterator it = pParameters->begin();
		m_uFunction.m_pUserFunction->m_pFunctionHeader->m_pParameters->Ergodic(
			[&](IrisIdentifier* pIdentifier) { pNewEnvironment->AddLoaclVariable(pIdentifier->m_strIdentifier, *it); ++it; }
		);
		// 如果有可变参数
		if (m_uFunction.m_pUserFunction->m_pFunctionHeader->m_pVariableParameter) {
			// 新建一个数组
			IrisValues ivsValues;

			ivsValues.assign(it, pParameters->end());

			IrisValue ivArray = IrisInterpreter::CurInstance()->GetIrisClass("Array")->CreateInstance(&ivsValues, nullptr);

			pNewEnvironment->AddLoaclVariable(m_uFunction.m_pUserFunction->m_pFunctionHeader->m_pVariableParameter->m_strIdentifier, ivArray);
		}
	}
	// ContextEnvironment入堆

	IrisGC::AddContextEnvironmentSize();
	IrisGC::ContextEnvironmentGC();

	IrisInterpreter::CurInstance()->AddNewEnvironmentToHeap(pNewEnvironment);
	return pNewEnvironment;
}

// 按照类型的不同分别调用不同的函数（直接调用 or 解释运行）
IrisValue IrisMethod::Call(IrisValue& ivObject, IrisContextEnvironment* pContextEnvironment ,IrisValues* pParameters) {
	IrisValue ivValue = IrisInterpreter::CurInstance()->Nil();
	IrisValues ivsNormalPrameters;
	IrisValues ivsVariableValues;
	bool bHaveVariableParameters = false;

	// 参数检查错误
	// 特殊情况 new 不检查，丢给__format检查
	if (!(m_strMethodName == "new")) {
		if (!_ParameterCheck(pParameters)) {
			// **Error**
			IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::ParameterNotFitIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Parameters of method " + m_strMethodName + " assigned is not fit.");
			return IrisInterpreter::CurInstance()->Nil();
		}
	}

	// Getter Setter
	if (m_eMethodType == MethodType::GetterMethod) {
		string strValueName;
		strValueName.assign(m_strMethodName.begin() + 6, m_strMethodName.end());
		strValueName = "@" + strValueName;
		bool bResult = false;
		IrisObject* pObject = ivObject.GetObjectPointer();
		const IrisValue& ivResult = pObject->GetInstanceValue(strValueName, bResult);
		// 不存在则定义
		if (!bResult) {
			pObject->AddInstanceValue(strValueName, IrisInterpreter::CurInstance()->Nil());
			return IrisInterpreter::CurInstance()->Nil();
		}
		return ivResult;
	}
	else if (m_eMethodType == MethodType::SetterMethod) {
		string strValueName;
		strValueName.assign(m_strMethodName.begin() + 6, m_strMethodName.end());
		strValueName = "@" + strValueName;
		bool bResult = false;
		IrisObject* pObject = ivObject.GetObjectPointer();
		IrisValue& ivResult = (IrisValue&)pObject->GetInstanceValue(strValueName, bResult);
		IrisValue& ivParam = (*pParameters)[0];
		// 不存在则定义
		if (!bResult) {
			pObject->AddInstanceValue(strValueName, ivParam);
			return ivParam;
		}
		ivResult.SetObject(ivParam.GetObjectPointer());
		return ivParam;
	}

	IrisContextEnvironment* pNewEnvironment = _CreateContextEnvironment(ivObject.GetObjectPointer(), pParameters);
	++pNewEnvironment->m_nReferenced;
	pNewEnvironment->m_pUpperContextEnvironment = pContextEnvironment;
	
	if (pContextEnvironment && pContextEnvironment->m_pTransferBlock) {
		pNewEnvironment->m_pClosureBlock = pContextEnvironment->m_pTransferBlock;
		pContextEnvironment->m_pTransferBlock = nullptr;
	}
	else if (IrisInterpreter::CurInstance()->GetMainClosureBlock()) {
		pNewEnvironment->m_pClosureBlock = IrisInterpreter::CurInstance()->GetMainClosureBlock();
		IrisInterpreter::CurInstance()->SetMainClosureBlock(nullptr);
	}

	//如果参数为空，直接调用
	if (!pParameters){
		if (m_eMethodType == MethodType::NativeMethod) {
			ivValue = m_uFunction.m_pfNativeFunction(ivObject, nullptr, nullptr, pNewEnvironment);
		}
		else {
			// 将参数加入环境中
			ivValue = m_uFunction.m_pUserFunction->m_pBlock->Execute(pNewEnvironment).m_ivValue;
		}
	}
	else {
		// 检查可变参数
		if ((int)pParameters->size() > m_nParameterAmount) {
			bHaveVariableParameters = true;
			ivsVariableValues.assign(pParameters->begin() + m_nParameterAmount, pParameters->end());
		}
		if (m_nParameterAmount > 0) {
			ivsNormalPrameters.assign(pParameters->begin(), pParameters->begin() + m_nParameterAmount);
		}

		if (m_eMethodType == MethodType::NativeMethod) {
			if (bHaveVariableParameters) {
				if (m_nParameterAmount > 0) {
					ivValue = m_uFunction.m_pfNativeFunction(ivObject, &ivsNormalPrameters, &ivsVariableValues, pNewEnvironment);
				}
				else {
					ivValue = m_uFunction.m_pfNativeFunction(ivObject, nullptr, &ivsVariableValues, pNewEnvironment);
				}
			}
			else {
				if (m_nParameterAmount > 0) {
					ivValue = m_uFunction.m_pfNativeFunction(ivObject, &ivsNormalPrameters, nullptr, pNewEnvironment);
				}
				else {
					ivValue = m_uFunction.m_pfNativeFunction(ivObject, nullptr, nullptr, pNewEnvironment);
				}
			}
		}
		else {
			// 将参数加入环境中
			ivValue = m_uFunction.m_pUserFunction->m_pBlock->Execute(pNewEnvironment).m_ivValue;
		}
	}

	--pNewEnvironment->m_nReferenced;

	if (pNewEnvironment->m_pClosureBlock) {
		delete pNewEnvironment->m_pClosureBlock;
		pNewEnvironment->m_pClosureBlock = nullptr;
	}

	return ivValue;
}

IrisValue IrisMethod::CallMainMethod(IrisValues* pParameters) {
	IrisValue ivValue;

	IrisValues ivsNormalPrameters;
	IrisValues ivsVariableValues;
	bool bHaveVariableParameters = false;

	// 参数检查错误
	if (!_ParameterCheck(pParameters)) {
		// **Error**
		IrisInterpreter::CurInstance()->GroanFatalIrregular(IrisInterpreter::FatalIrregular::ParameterNotFitIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Parameters of method " + m_strMethodName + " assigned is not fit.");
		return IrisInterpreter::CurInstance()->Nil();
	}
	IrisContextEnvironment* pNewEnvironment = _CreateContextEnvironment(nullptr, pParameters);
	++pNewEnvironment->m_nReferenced;
	pNewEnvironment->m_pUpperContextEnvironment = nullptr;

	//pNewEnvironment->m_pClosureBlock = pClosureBlock;
	if (IrisInterpreter::CurInstance()->GetMainClosureBlock()) {
		pNewEnvironment->m_pClosureBlock = IrisInterpreter::CurInstance()->GetMainClosureBlock();
		IrisInterpreter::CurInstance()->SetMainClosureBlock(nullptr);
	}

	// 将参数加入环境中
	ivValue = m_uFunction.m_pUserFunction->m_pBlock->Execute(pNewEnvironment).m_ivValue;

	--pNewEnvironment->m_nReferenced;

	if (pNewEnvironment->m_pClosureBlock) {
		delete pNewEnvironment->m_pClosureBlock;
		pNewEnvironment->m_pClosureBlock = nullptr;
	}

	return ivValue;
}

void IrisMethod::ResetObject() {
	IrisValue ivValue = IrisInterpreter::CurInstance()->GetIrisClass("Method")->CreateInstance(nullptr, nullptr);
	((IrisMethodBaseTag*)ivValue.GetObjectPointer()->m_pNativeObject)->SetMethod(this);
	m_pMethodObject = ivValue.GetObjectPointer();
}

void IrisMethod::SetMethodAuthority(MethodAuthority eAuthority) {
	m_eAuthority = eAuthority;
}

IrisMethod::~IrisMethod() {
	//if (m_eMethodType == MethodType::UserMethod){
	//	delete m_uFunction.m_pUserFunction;
	//}
	//delete m_pMethodObject;
}