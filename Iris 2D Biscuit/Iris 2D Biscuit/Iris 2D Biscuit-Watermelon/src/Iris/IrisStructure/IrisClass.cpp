#include "IrisClass.h"
#include "IrisInterpreter.h"
#include "IrisClassBaseTag.h"
#include "IrisGC.h"

void IrisClass::_FunctionCollect(IrisInterface* pInterface, _InterfaceFunctionDeclareMap& mpFunctionDeclare) {
	// 出口
	if (!pInterface)
		return;

	IrisInterface* pTmpInter = pInterface;

	// 从继承链最低端的接口开始往上添加FunctionDeclare
	for (auto funcdec : pTmpInter->m_mpFunctionDeclareMap){
		// 没找到则添加进去（默认继承链最低端的接口方法定义覆盖父接口的方法定义）
		if (mpFunctionDeclare.find(funcdec.first) == mpFunctionDeclare.end()){
			mpFunctionDeclare.insert(_InterfaceFunctionDeclarePair(funcdec.first, funcdec.second));
		}
	}

	// 下一层
	for (auto inter : pTmpInter->m_mpInterfaces){
		_FunctionCollect(inter.second, mpFunctionDeclare);
	}
}

bool IrisClass::_FunctionAchieved() {
	_InterfaceFunctionDeclareMap mpFunctionDeclare;
	// 递归调用，把所有的接口的FunctionDeclare给放到map里面
	for (auto inter : m_hsInterfaces){
		_FunctionCollect(inter.second, mpFunctionDeclare);
	}

	bool bResult = false;
	IrisMethod* pMethod = nullptr;
	// 开始逐个检查
	for (auto funcdec : mpFunctionDeclare) {
		pMethod = GetMethod(IrisClass::SearchMethodType::InstanceMethod, funcdec.first, bResult);
		// 如果没有找到，那么直接退出
		if (!pMethod) {
			return false;
		}
		else {
			// 如果找到了但是参数不对，还是退出
			auto pMethodDeclare = funcdec.second;
			if (pMethod->m_bIsWithVariableParameter != pMethodDeclare.m_bHaveVariableParameter
				|| pMethod->m_nParameterAmount != pMethodDeclare.m_nParameterAmount) {
				return false;
			}
		}
	}
	return true;
}

void IrisClass::AddConstance(const string& strConstName, const IrisValue& ivInitialValue){
	IrisVariable ivbVariable;
	ivbVariable.m_ivValue = ivInitialValue;
	ivbVariable.m_strName = strConstName;
	m_hsConstances.insert(_VariablePair(strConstName, ivbVariable));
}

void IrisClass::_SearchModuleConstance(SearchVariableType eType, const string& strVariableName, IrisModule* pCurModule, IrisValue** pValue) {
	//出口
	if (pCurModule == nullptr) {
		return;
	}

	if (eType == SearchVariableType::Constance) {
		if (pCurModule->m_hsConstances.find(strVariableName) != pCurModule->m_hsConstances.end()) {
			*pValue = &(pCurModule->m_hsConstances[strVariableName].m_ivValue);
			return;
		}
	}
	else {
		if (pCurModule->m_hsClassVariables.find(strVariableName) != pCurModule->m_hsClassVariables.end()) {
			*pValue = &(pCurModule->m_hsClassVariables[strVariableName].m_ivValue);
			return;
		}
	}

	for (auto module : pCurModule->m_hsModules) {
		_SearchModuleConstance(eType, strVariableName, module.second, pValue);
		if (*pValue)
			return;
	}
}

const IrisValue& IrisClass::SearchConstance(const string& strConstName, bool& bResult) {
	bResult = true;
	IrisValue* pValue = nullptr;
	// 查找顺序本类、所包含的模块、父类
	// 本类
	if (m_hsConstances.find(strConstName) != m_hsConstances.end()){
		return m_hsConstances[strConstName].m_ivValue;
	}

	// 所包含的模块
	IrisClass* pCurClass = this;
	do{
		for (auto module : pCurClass->m_hsModules){
			_SearchModuleConstance(SearchVariableType::Constance, strConstName, module.second, &pValue);
			if (pValue){
				return *pValue;
			}
		}
		pCurClass = pCurClass->m_pSuperClass;
	} while (pCurClass);

	// 父类
	pCurClass = m_pSuperClass;
	do{
		if (pCurClass->m_hsConstances.find(strConstName) != pCurClass->m_hsConstances.end()){
			return pCurClass->m_hsConstances[strConstName].m_ivValue;
		}
		pCurClass = pCurClass->m_pSuperClass;
	} while (pCurClass);

	pValue = (IrisValue*)&IrisInterpreter::CurInstance()->GetConstance(strConstName, bResult);
	if (bResult) {
		return *pValue;
	}

	bResult = false;
	return IrisInterpreter::CurInstance()->Nil();
}

void IrisClass::ClearInvolvingModules() {
	m_hsModules.clear();
}

void IrisClass::ClearJointingInterfaces() {
	m_hsInterfaces.clear();
}

void IrisClass::AddClassMethod(IrisMethod* pMethod) {
	if (m_hsClassMethods.find(pMethod->GetMethodName()) != m_hsClassMethods.end()) {
		delete m_hsClassMethods[pMethod->GetMethodName()];
		m_hsClassMethods[pMethod->GetMethodName()] = pMethod;
	}
	else {
		m_hsClassMethods.insert(_MethodPair(pMethod->m_strMethodName, pMethod));
	}
}

void IrisClass::AddInstanceMethod(IrisMethod* pMethod) {
	if (m_hsInstanceMethods.find(pMethod->GetMethodName()) != m_hsInstanceMethods.end()) {
		delete m_hsInstanceMethods[pMethod->GetMethodName()];
		m_hsInstanceMethods[pMethod->GetMethodName()] = pMethod;
	}
	else {
		m_hsInstanceMethods.insert(_MethodPair(pMethod->m_strMethodName, pMethod));
	}
}

void IrisClass::AddInterface(IrisInterface* pInterface) {

	string strFullPath = "";
	IrisModule* pTmpModule = pInterface->m_pUpperModule;
	while (pTmpModule) {
		strFullPath = pTmpModule->GetModuleName() + "::" + strFullPath;
		pTmpModule = pTmpModule->m_pUpperModule;
	}
	strFullPath += pInterface->GetInterfaceName();

	if (m_hsInterfaces.find(strFullPath) != m_hsInterfaces.end()) {
		m_hsInterfaces[strFullPath] = pInterface;
	}
	else {
		m_hsInterfaces.insert(_InterfacePair(strFullPath, pInterface));
	}	
}

void IrisClass::AddModule(IrisModule* pModule) {

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

void IrisClass::AddClassVariable(const string& strClassVariableName) {
	IrisVariable ivbVariable;
	ivbVariable.m_ivValue = IrisInterpreter::CurInstance()->Nil();
	ivbVariable.m_strName = strClassVariableName;
	m_hsClassVariables.insert(_VariablePair(strClassVariableName, ivbVariable));
}

void IrisClass::AddClassVariable(const string& strClassVariableName, const IrisValue& ivInitialValue) {
	IrisVariable ivbVariable;
	ivbVariable.m_ivValue = ivInitialValue;
	ivbVariable.m_strName = strClassVariableName;
	m_hsClassVariables.insert(_VariablePair(strClassVariableName, ivbVariable));
}

const IrisValue& IrisClass::SearchClassVariable(const string& strClassVariableName, bool& bResult) {
	bResult = true;
	IrisValue* pValue = nullptr;
	// 查找顺序本类、所包含的模块、父类
	// 本类
	if (m_hsClassVariables.find(strClassVariableName) != m_hsClassVariables.end()) {
		return m_hsClassVariables[strClassVariableName].m_ivValue;
	}

	// 所包含的模块
	IrisClass* pCurClass = this;
	do {
		for (auto module : pCurClass->m_hsModules) {
			_SearchModuleConstance(SearchVariableType::ClassInstance, strClassVariableName, module.second, &pValue);
			if (pValue) {
				return *pValue;
			}
		}
		pCurClass = pCurClass->m_pSuperClass;
	} while (pCurClass);

	// 父类
	pCurClass = m_pSuperClass;
	do {
		if (pCurClass->m_hsClassVariables.find(strClassVariableName) != pCurClass->m_hsClassVariables.end()) {
			return pCurClass->m_hsClassVariables[strClassVariableName].m_ivValue;
		}
		pCurClass = pCurClass->m_pSuperClass;
	} while (pCurClass);

	bResult = false;
	return IrisInterpreter::CurInstance()->Nil();
}

IrisValue IrisClass::CreateInstance(IrisValues* ivsParams, IrisContextEnvironment* pContexEnvironment) {
	// 检查是否有没有实现的接口
	IrisValue ivValue;
	if (!m_bIsCompleteClass){
		if (!(m_bIsCompleteClass = _FunctionAchieved())) {
			// **Error**
			IrisInterpreter::CurInstance()->GroanFatalIrregular
				(IrisInterpreter::FatalIrregular::ClassNotCompleteIrregular, 0, "Class " + m_strClassName + " is still having some methods not defined but declared in the interfaces jointed.");
			return IrisInterpreter::CurInstance()->Nil();
		}
	}
	// 生成对象
	IrisObject* pObject = new IrisObject();
	pObject->m_pClass = this;
	if (m_strClassName == "Object") {
		pObject->m_pNativeObject = this;
		IrisGC::AddSize(sizeof(IrisObject));
	}
	else {
		pObject->m_pNativeObject = NativeAlloc();
		IrisGC::AddSize(sizeof(IrisObject) + pObject->GetClass()->GetTrustteeSize());
	}
	IrisGC::Start();
	ivValue.m_pObject = pObject;
	//InstanceFunctionCall(ivValue, "initialize", ivsParams);
	if (pContexEnvironment && pContexEnvironment->m_pClosureBlock) {
		pContexEnvironment->m_pTransferBlock = pContexEnvironment->m_pClosureBlock;
		pContexEnvironment->m_pClosureBlock = nullptr;
	}
	pObject->CallInstanceFunction("__format", pContexEnvironment, ivsParams);

	// 将新对象保存到堆里
	IrisInterpreter::CurInstance()->AddNewInstanceToHeap(ivValue);

	return ivValue;
}

// 为内置对象提供
IrisValue IrisClass::CreateInstanceFromLiteral(char* pLiteral){
	// 检查是否有没有实现的接口
	IrisValue ivValue;
	// 生成对象
	IrisObject* pObject = new IrisObject();
	pObject->m_pClass = this;
	pObject->m_pNativeObject = GetLiteralObject(pLiteral);

	IrisGC::AddSize(sizeof(IrisObject) + pObject->GetClass()->GetTrustteeSize());
	IrisGC::Start();

	ivValue.m_pObject = pObject;
	// 将新对象保存到堆里
	IrisInterpreter::CurInstance()->AddNewInstanceToHeap(ivValue);

	return ivValue;
}

void IrisClass::_ClassModuleMethodSearch(SearchMethodType eSearchType, IrisClass* pCurClass, const string& strMethodName, IrisMethod** ppMethod) {
	for (auto module : pCurClass->m_hsModules) {
		_ModuleMethodSearch(eSearchType, strMethodName, module.second, ppMethod);
		// 找到就退出
		if (*ppMethod)
			return;
	}
}

void IrisClass::_ModuleMethodSearch(SearchMethodType eSearchType, const string& strFunctionName, IrisModule* pCurModule, IrisMethod** ppMethod) {
	// 出口
	if (!pCurModule)
		return;
	// 如果找到
	// 类方法
	if (eSearchType == SearchMethodType::ClassMethod) {
		if (pCurModule->m_hsClassMethods.find(strFunctionName) != pCurModule->m_hsClassMethods.end()) {
			*ppMethod = pCurModule->m_hsClassMethods[strFunctionName];
			return;
		}
	}
	// 实例方法
	else {
		if (pCurModule->m_hsInstanceMethods.find(strFunctionName) != pCurModule->m_hsInstanceMethods.end()) {
			*ppMethod = pCurModule->m_hsInstanceMethods[strFunctionName];
			return;
		}
	}
	// 继续递归查找
	for (auto module : pCurModule->m_hsModules) {
		_ModuleMethodSearch(eSearchType, strFunctionName, module.second, ppMethod);
		if (*ppMethod)
			break;
	}
}

IrisMethod* IrisClass::GetMethod(SearchMethodType eSearchType, const string& strMethodName, bool& bIsCurClassMethod) {
	// 方法的查找顺序：本类、所包含的模块、父类，如果都找不到那就真找不到了
	// 检查本类
	// 如果是调用类方法的情况下
	bIsCurClassMethod = false;
	if (eSearchType == SearchMethodType::ClassMethod) {
		if (m_hsClassMethods.find(strMethodName) != m_hsClassMethods.end()) {
			bIsCurClassMethod = true;
			return m_hsClassMethods[strMethodName];
		}
		else {
			// 检查所包含的模块
			IrisMethod* pMethod = nullptr;
			IrisClass* pCurClass = this;

			// 对继承链上所有类所包括的模块进行扫描
			while (pCurClass) {
				_ClassModuleMethodSearch(eSearchType, pCurClass, strMethodName, &pMethod);
				if (pMethod) {
					// 找到返回
					return pMethod;
				}
				pCurClass = pCurClass->m_pSuperClass;
			}
			// 还没找到就只能在父类查找了
			IrisClass* pCurSuperClass = m_pSuperClass;
			while (pCurSuperClass) {
				if (pCurSuperClass->m_hsClassMethods.find(strMethodName) != pCurSuperClass->m_hsClassMethods.end()) {
					return pCurSuperClass->m_hsClassMethods[strMethodName];
				}
				pCurSuperClass = pCurSuperClass->m_pSuperClass;
			}
			// 如果没有找到就去Class类里面找
			bool bResult = false;
			pMethod = IrisInterpreter::CurInstance()->GetIrisClass("Class")->GetMethod(IrisClass::SearchMethodType::ClassMethod, strMethodName, bResult);
			return pMethod;
		}
	}
	// 如果是调用实例方法的情况下
	else{
		if (m_hsInstanceMethods.find(strMethodName) != m_hsInstanceMethods.end()) {
			bIsCurClassMethod = true;
			return m_hsInstanceMethods[strMethodName];
		}
		else {
			// 检查所包含的模块
			IrisMethod* pMethod = nullptr;
			IrisClass* pCurClass = this;

			// 对继承链上所有类所包括的模块进行扫描
			while (pCurClass) {
				_ClassModuleMethodSearch(eSearchType, pCurClass, strMethodName, &pMethod);
				if (pMethod) {
					// 找到返回
					bIsCurClassMethod = true;
					return pMethod;
				}
				pCurClass = pCurClass->m_pSuperClass;
			}
			// 还没找到就只能在父类查找了
			IrisClass* pCurSuperClass = m_pSuperClass;
			while (pCurSuperClass) {
				if (pCurSuperClass->m_hsInstanceMethods.find(strMethodName) != pCurSuperClass->m_hsInstanceMethods.end()) {
					return pCurSuperClass->m_hsInstanceMethods[strMethodName];
				}
				pCurSuperClass = pCurSuperClass->m_pSuperClass;
			}
		}
	}

	// 除此之外就真的找不到了
	return nullptr;
}

void IrisClass::ResetNativeObject() {
	IrisValue ivValue = IrisInterpreter::CurInstance()->GetIrisClass("Class")->CreateInstance(nullptr, nullptr);
	((IrisClassBaseTag*)ivValue.GetObjectPointer()->m_pNativeObject)->SetClass(this);
	m_pClassObject = ivValue.GetObjectPointer();
}

IrisClass::IrisClass(const string& strClassName, IrisClass* pSuperClass, IrisModule* pUpperModule) : m_strClassName(strClassName), m_pSuperClass(pSuperClass), m_pUpperModule(pUpperModule) {
	if (IrisInterpreter::CurInstance()->GetIrisClass("Class")) {
		IrisValue ivValue = IrisInterpreter::CurInstance()->GetIrisClass("Class")->CreateInstance(nullptr, nullptr);
		((IrisClassBaseTag*)ivValue.GetObjectPointer()->m_pNativeObject)->SetClass(this);
		m_pClassObject = ivValue.GetObjectPointer();
	}
}

IrisValue IrisClass::CallClassMethod(const string& strMethodName, IrisContextEnvironment* pContextEnvironment, IrisValues* ivParameters, CallerSide eSide) {
	bool bIsCrrentModuleMethod = false;
	IrisMethod* pMethod = GetMethod(SearchMethodType::ClassMethod, strMethodName, bIsCrrentModuleMethod);
	if (pMethod) {
		// 内部调用
		if (eSide == CallerSide::Inside) {
			// 当前类调用没有限制
			if (bIsCrrentModuleMethod) {
				return pMethod->Call(IrisValue::WrapObjectPointerToIrisValue(m_pClassObject), pContextEnvironment, ivParameters);
			}
			// 调用其他模块/类的Personal方法
			else {
				if (pMethod->m_eAuthority == IrisMethod::MethodAuthority::Personal) {
					// **Error**
					IrisInterpreter::CurInstance()->GroanFatalIrregular
					(IrisInterpreter::FatalIrregular::MethodAuthorityIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Method of " + strMethodName + " is Personal and cannot be called from derrived class " + m_strClassName + " .");
					return IrisInterpreter::CurInstance()->Nil();
				}
				else {
					return pMethod->Call(IrisValue::WrapObjectPointerToIrisValue(m_pClassObject), pContextEnvironment, ivParameters);
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
					(IrisInterpreter::FatalIrregular::MethodAuthorityIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Method of " + strMethodName + " is not Everyone and cannot be called outside the class " + m_strClassName + " .");
				return IrisInterpreter::CurInstance()->Nil();
			}
			else {
				return pMethod->Call(IrisValue::WrapObjectPointerToIrisValue(m_pClassObject), pContextEnvironment, ivParameters);
			}
		}

		//return pMethod->Call(IrisValue::WrapObjectPointerToIrisValue(m_pClassObject), pContexEnvironment, ivParameters);
	}
	IrisInterpreter::CurInstance()->GroanFatalIrregular
		(IrisInterpreter::FatalIrregular::NoMethodIrregular, IrisInterpreter::CurInstance()->GetExcutedLineNumber(), "Method of " + strMethodName + " not found in class " + m_strClassName + " .");

	return IrisInterpreter::CurInstance()->Nil();
}

void IrisClass::ResetAllMethodsObject() {
	for (auto classmethod : m_hsClassMethods) {
		classmethod.second->ResetObject();
	}

	for (auto instancemethod : m_hsInstanceMethods) {
		instancemethod.second->ResetObject();
	}
}

IrisMethod* IrisClass::GetCurrentClassMethod(SearchMethodType eSearchType, const string& strMethodName) {
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

void IrisClass::AddSetter(const string& strProperName, IrisNativeFunction pfMethod) {
	string strMethodName = strProperName;
	strMethodName.assign(strMethodName.begin() + 1, strMethodName.end());
	strMethodName = "__set_" + strMethodName;
	IrisMethod* pMethod = new IrisMethod(strMethodName, pfMethod, 1, false);
	pMethod->m_strMethodName = strMethodName;

	if (m_hsInstanceMethods.find(pMethod->GetMethodName()) != m_hsInstanceMethods.end()) {
		delete m_hsInstanceMethods[pMethod->GetMethodName()];
		m_hsInstanceMethods[pMethod->GetMethodName()] = pMethod;
	}
	else {
		m_hsInstanceMethods.insert(_MethodPair(pMethod->m_strMethodName, pMethod));
	}
}

void IrisClass::AddGetter(const string& strProperName, IrisNativeFunction pfMethod) {
	string strMethodName = strProperName;
	strMethodName.assign(strMethodName.begin() + 1, strMethodName.end());
	strMethodName = "__get_" + strMethodName;
	IrisMethod* pMethod = new IrisMethod(strMethodName, pfMethod, 0, false);
	pMethod->m_strMethodName = strMethodName;
	if (m_hsInstanceMethods.find(pMethod->GetMethodName()) != m_hsInstanceMethods.end()) {
		delete m_hsInstanceMethods[pMethod->GetMethodName()];
		m_hsInstanceMethods[pMethod->GetMethodName()] = pMethod;
	}
	else {
		m_hsInstanceMethods.insert(_MethodPair(pMethod->m_strMethodName, pMethod));
	}
}

IrisClass::~IrisClass() {
	for (auto iter : m_hsInstanceMethods){
		delete iter.second;
	}
	for (auto iter : m_hsClassMethods){
		delete iter.second;
	}
}