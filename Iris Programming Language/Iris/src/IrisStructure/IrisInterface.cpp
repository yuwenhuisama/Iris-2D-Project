#include "IrisInterface.h"
#include "IrisInterpreter.h"
#include "IrisInterfaceBase.h"

IrisInterface::IrisInterface(const string& strInterfaceName, IrisModule* pUpperModule) : m_strInterfaceName(strInterfaceName), m_pUpperModule(pUpperModule) {
	IrisValue ivValue = IrisInterpreter::CurInstance()->GetIrisClass("Interface")->CreateInstance(nullptr, nullptr);
	((IrisInterfaceBaseTag*)ivValue.GetInstanceNativePointer())->SetInterface(this);
	m_pInterfaceObject = ivValue.GetObject();
}

void IrisInterface::AddInterface(IrisInterface* pInterface) {

	string strFullPath = "";
	IrisModule* pTmpModule = pInterface->m_pUpperModule;
	while (pTmpModule) {
		strFullPath = pTmpModule->GetModuleName() + "::" + strFullPath;
		pTmpModule = pTmpModule->m_pUpperModule;
	}
	strFullPath += pInterface->GetInterfaceName();

	if (m_mpInterfaces.find(strFullPath) != m_mpInterfaces.end()) {
		m_mpInterfaces[strFullPath] = pInterface;
	}
	else {
		m_mpInterfaces.insert(_InterfacePair(strFullPath, pInterface));
	}
}

void IrisInterface::AddInterfaceFunctionDeclare(const string& strFunctionName, int m_nParameterAmount, bool bHaveHaveVariableParameter){
	InterfaceFunctionDeclare ifdDeclare { strFunctionName, m_nParameterAmount, bHaveHaveVariableParameter };
	if (m_mpFunctionDeclareMap.find(strFunctionName) != m_mpFunctionDeclareMap.end()) {
		m_mpFunctionDeclareMap[strFunctionName] = ifdDeclare;
	}
	else {
		m_mpFunctionDeclareMap.insert(_InterfaceFunctionDeclarePair(strFunctionName, ifdDeclare));
	}
}

void IrisInterface::ClearJointingInterfaces() {
	m_mpInterfaces.clear();
}

IrisInterface::~IrisInterface() {

}