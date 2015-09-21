#include "IrisMethodBaseTag.h"


IrisMethodBaseTag::IrisMethodBaseTag(IrisMethod* pMethod) : m_pMethod(pMethod)
{
}

const string& IrisMethodBaseTag::GetMethodName() {
	return m_pMethod->GetMethodName();
}

void IrisMethodBaseTag::SetMethod(IrisMethod* pMethod) {
	m_pMethod = pMethod;
}::

IrisMethodBaseTag::~IrisMethodBaseTag()
{
}
