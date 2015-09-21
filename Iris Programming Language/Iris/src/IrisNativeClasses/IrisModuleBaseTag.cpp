#include "IrisModuleBaseTag.h"


IrisModuleBaseTag::IrisModuleBaseTag(IrisModule* pModule) : m_pModule(pModule)
{
}

void IrisModuleBaseTag::SetModule(IrisModule* pModule) {
	m_pModule = pModule;
}

const string& IrisModuleBaseTag::GetModuleName() {
	return m_pModule->GetModuleName();
}

IrisModule* IrisModuleBaseTag::GetModule() {
	return m_pModule;
}

IrisModuleBaseTag::~IrisModuleBaseTag()
{
}
