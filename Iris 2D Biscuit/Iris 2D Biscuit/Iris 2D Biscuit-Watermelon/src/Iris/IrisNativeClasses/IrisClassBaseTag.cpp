#include "IrisClassBaseTag.h"


IrisClassBaseTag::IrisClassBaseTag(IrisClass* pClass) : m_pClass(pClass)
{
}

const string& IrisClassBaseTag::GetClassName() {
	return m_pClass->GetClassName();
}

void IrisClassBaseTag::SetClass(IrisClass* pClass) {
	m_pClass = pClass;
}

IrisClass* IrisClassBaseTag::GetClass() {
	return m_pClass;
}

IrisClassBaseTag::~IrisClassBaseTag()
{
}
