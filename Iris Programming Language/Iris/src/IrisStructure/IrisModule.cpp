#include "IrisModule.h"
#include "IrisInterpreter.h"
#include "IrisModuleBaseTag.h"


void IrisModule::ClearInvolvingModules() {
	m_hsModules.clear();
}

void IrisModule::AddInvolvedInterface(IrisInterface* pInterface) {
	if (m_hsInvolvedInterfaces.find(pInterface->GetInterfaceName()) == m_hsInvolvedInterfaces.end()) {
		m_hsInvolvedInterfaces.insert(_InterfacePair(pInterface->GetInterfaceName(), pInterface));
	}
	else {
		m_hsInvolvedInterfaces[pInterface->GetInterfaceName()] = pInterface;
	}
}

void IrisModule::AddConstance(const string& strConstName, const IrisValue& ivInitialValue){
	IrisVariable ivbVariable;
	ivbVariable.m_ivValue = ivInitialValue;
	ivbVariable.m_strName = strConstName;
	m_hsConstances.insert(_VariablePair(strConstName, ivbVariable));
}

void IrisModule::_SearchConstance(const string& strConstanceName, IrisModule* pCurModule, IrisValue** pValue) {
	//出口
	if (pCurModule == nullptr) {
		return;
	}
	if (pCurModule->m_hsConstances.find(strConstanceName) != pCurModule->m_hsConstances.end()) {
		*pValue = &(pCurModule->m_hsConstances[strConstanceName].m_ivValue);
		return;
	}

	for (auto module : pCurModule->m_hsModules) {
		_SearchConstance(strConstanceName, module.second, pValue);
		if (pValue)
			return;
	}
}
void IrisModule::_SearchClassVariable(const string& strVariableName, IrisModule* pCurModule, IrisValue** pValue){
	//出口
	if (pCurModule == nullptr) {
		return;
	}
	if (pCurModule->m_hsClassVariables.find(strVariableName) != pCurModule->m_hsClassVariables.end()) {
		*pValue = &(pCurModule->m_hsClassVariables[strVariableName].m_ivValue);
		return;
	}

	for (auto module : pCurModule->m_hsModules) {
		_SearchClassVariable(strVariableName, module.second, pValue);
		if (*pValue)
			return;
	}
}

const IrisValue& IrisModule::SearchConstance(const string& strConstName, bool& bResult) {
	bResult = true;
	IrisValue* pValue = nullptr;

	_SearchConstance(strConstName, this, &pValue);
	if (pValue){
		return *pValue;
	}
	else{
		pValue = (IrisValue*)&IrisInterpreter::CurInstance()->GetOtherValue(strConstName, bResult);
		if (bResult) {
			return *pValue;
		}
		bResult = false;
		return IrisInterpreter::CurInstance()->Nil();
	}
}

void IrisModule::AddClassMethod(IrisMethod* pMethod) {
	//m_hsClassMethods.insert(_MethodPair(pMethod->m_strMethodName, pMethod));
	if (m_hsClassMethods.find(pMethod->GetMethodName()) != m_hsClassMethods.end()) {
		delete m_hsClassMethods[pMethod->GetMethodName()];
		m_hsClassMethods[pMethod->GetMethodName()] = pMethod;
	}
	else {
		m_hsClassMethods.insert(_MethodPair(pMethod->m_strMethodName, pMethod));
	}
}

void IrisModule::AddInstanceMethod(IrisMethod* pMethod) {
	//m_hsInstanceMethods.insert(_MethodPair(pMethod->m_strMethodName, pMethod));
	if (m_hsInstanceMethods.find(pMethod->GetMethodName()) != m_hsInstanceMethods.end()) {
		delete m_hsInstanceMethods[pMethod->GetMethodName()];
		m_hsInstanceMethods[pMethod->GetMethodName()] = pMethod;
	}
	else {
		m_hsInstanceMethods.insert(_MethodPair(pMethod->m_strMethodName, pMethod));
	}
}

void IrisModule::AddModule(IrisModule* pModule) {
	//m_hsModules.insert(_ModulePair(pModule->m_strModuleName, pModule));

	string strFullPath = "";
	IrisModule* pTmpModule = pModule->m_pUpperModule;
	while (pTmpModule) {
		strFullPath = pTmpModule->GetModuleName() + "::" + strFullPath;
		pTmpModule = pTmpModule->m_pUpperModule;
	}
	strFullPath += pModule->GetModuleName();

	if (m_hsModules.find(strFullPath) != m_hsModules.end()) {
		m_hsModules[strFullPath] = pModule;
	}
	else {
		m_hsModules.insert(_ModulePair(strFullPath, pModule));
	}
}

void IrisModule::AddClassVariable(const string& strClassVariableName) {
	IrisVariable ivbVariable;
	ivbVariable.m_ivValue = IrisInterpreter::CurInstance()->Nil();
	ivbVariable.m_strName = strClassVariableName;
	m_hsClassVariables.insert(_VariablePair(strClassVariableName, ivbVariable));
}

void IrisModule::AddClassVariable(const string& strClassVariableName, const IrisValue& ivInitialValue) {
	IrisVariable ivbVariable;
	ivbVariable.m_ivValue = ivInitialValue;
	ivbVariable.m_strName = strClassVariableName;
	m_hsClassVariables.insert(_VariablePair(strClassVariableName, ivbVariable));
}

const IrisValue& IrisModule::SearchClassVariable(const string& strClassVariableName, bool& bResult){
	bResult = true;
	IrisValue* pValue = nullptr;

	_SearchClassVariable(strClassVariableName, this, &pValue);
	if (pValue){
		return *pValue;
	}
	else{
		bResult = false;
		return IrisInterpreter::CurInstance()->Nil();
	}
}

void IrisModule::_SearchModuleMethod(const string& strFunctionName, IrisModule* pCurModule, IrisMethod** ppMethod) {

	// 出口
	if (*ppMethod)
		return;

	if (pCurModule->m_hsClassMethods.find(strFunctionName) != pCurModule->m_hsClassMethods.end()) {
		*ppMethod = pCurModule->m_hsClassMethods[strFunctionName];
		return;
	}

	for (auto module : pCurModule->m_hsModules) {
		_SearchModuleMethod(strFunctionName, module.second, ppMethod);
		if (*ppMethod)
			return;
	}
}

IrisValue IrisModule::CallClassMethod(const string& strMethodName, IrisContextEnvironment* pContextEnvironment, IrisValues* ivParameters, CallerSide eSide) {
	IrisMethod* pMethod = nullptr;
	bool bIsCrrentModuleMethod = false;

	if (m_hsClassMethods.find(strMethodName) != m_hsClassMethods.end()) {
		pMethod = m_hsClassMethods[strMethodName];
		bIsCrrentModuleMethod = true;
	}
	else {
		for (auto module : m_hsModules) {
			_SearchModuleMethod(strMethodName, module.second, &pMethod);
			if (pMethod) {
				break;
			}
		}
	}

	if (pMethod) {
		// 内部调用
		if (eSide == CallerSide::Inside) {
			// 当前模块调用没有限制
			if (bIsCrrentModuleMethod) {
				return pMethod->Call(IrisValue::WrapObjectPointerToIrisValue(m_pModuleObject), pContextEnvironment, ivParameters);
			}
			// 调用其他模块的Personal方法
			else {
				if (pMethod->m_eAuthority == IrisMethod::MethodAuthority::Personal) {
					// **Error**
					IrisInterpreter::CurInstance()->GroanFatalIrregular
						(IrisInterpreter::FatalIrregular::MethodAuthorityIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Method of " + strMethodName + " is Personal and cannot be called from module " + m_strModuleName + " .");
					return IrisInterpreter::CurInstance()->Nil();
				}
				else {
					return pMethod->Call(IrisValue::WrapObjectPointerToIrisValue(m_pModuleObject), pContextEnvironment, ivParameters);
				}
			}
		}
		// 外部调用
		else {
			// 只能调用EveryOne的方法
			// 禁止调用
			if (pMethod->m_eAuthority != IrisMethod::MethodAuthority::Everyone) {
				// **Error**
				IrisInterpreter::CurInstance()->GroanFatalIrregular
					(IrisInterpreter::FatalIrregular::MethodAuthorityIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Method of " + strMethodName + " is not Everyone and cannot be called outside the module " + m_strModuleName + " .");
				return IrisInterpreter::CurInstance()->Nil();
			}
			else {
				return pMethod->Call(IrisValue::WrapObjectPointerToIrisValue(m_pModuleObject), pContextEnvironment, ivParameters);
			}
		}
	}
	// **Error**
	IrisInterpreter::CurInstance()->GroanFatalIrregular
		(IrisInterpreter::FatalIrregular::NoMethodIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Method of " + strMethodName + " not found in module " + m_strModuleName + " .");
	return IrisInterpreter::CurInstance()->Nil();
}

IrisModule::IrisModule(const string& strModuleName, IrisModule* pUpperModule) : m_strModuleName(strModuleName), m_pUpperModule(pUpperModule) {
	IrisValue ivValue = IrisInterpreter::CurInstance()->GetIrisClass("Module")->CreateInstance(nullptr, nullptr);
	((IrisModuleBaseTag*)ivValue.GetObject()->m_pNativeObject)->SetModule(this);
	m_pModuleObject = ivValue.GetObject();
}

void IrisModule::AddClass(IrisClass* pClass) {
	if (m_hsClasses.find(pClass->GetClassName()) == m_hsClasses.end()) {
		m_hsClasses.insert(_ClassPair(pClass->GetClassName(), pClass));
	}
	else {
		m_hsClasses[pClass->GetClassName()] =  pClass;
	}
}

IrisClass* IrisModule::GetClass(const string& strClassName) {
	if (m_hsClasses.find(strClassName) != m_hsClasses.end()) {
		return m_hsClasses[strClassName];
	}
	return nullptr;
}

IrisInterface* IrisModule::GetInterface(const string& strInterfaceName) {
	if (m_hsInvolvedInterfaces.find(strInterfaceName) != m_hsInvolvedInterfaces.end()) {
		return m_hsInvolvedInterfaces[strInterfaceName];
	}
	return nullptr;
}

void IrisModule::ResetAllMethodsObject() {
	for (auto classmethod : m_hsClassMethods) {
		classmethod.second->ResetObject();
	}

	for (auto instancemethod : m_hsInstanceMethods) {
		instancemethod.second->ResetObject();
	}
}

IrisMethod* IrisModule::GetCurrentModuleMethod(SearchMethodType eSearchType, const string& strMethodName) {
	if (eSearchType == SearchMethodType::ClassMethod) {
		if (m_hsClassMethods.find(strMethodName) == m_hsClassMethods.end()) {
			return nullptr;
		}
		return m_hsClassMethods[strMethodName];
	}
	else {
		if (m_hsInstanceMethods.find(strMethodName) == m_hsInstanceMethods.end()) {
			return nullptr;
		}
		return m_hsInstanceMethods[strMethodName];
	}
}

IrisModule::~IrisModule() {
	for (auto iter : m_hsInstanceMethods) {
		delete iter.second;
	}
	for (auto iter : m_hsClassMethods) {
		delete iter.second;
	}
}