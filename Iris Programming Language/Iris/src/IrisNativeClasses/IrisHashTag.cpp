#include "IrisHashTag.h"



IrisHashTag::IrisHashTag() : m_mpHash()
{
}

void IrisHashTag::Initialize(IrisValues* pValues) {
	if (pValues) {
		int nSize = pValues->size() / 2;
		for (int i = 0; i < nSize; ++i) {
			m_mpHash[(*pValues)[i * 2]] = (*pValues)[i * 2 + 1];
		}
	}
}

IrisValue IrisHashTag::At(const IrisValue& ivIndex) {
	if(m_mpHash.find(ivIndex) == m_mpHash.end()) {
		m_mpHash[ivIndex] = IrisInterpreter::CurInstance()->Nil();
		return IrisInterpreter::CurInstance()->Nil();
	}
	return m_mpHash[ivIndex];
}

IrisValue IrisHashTag::Set(const IrisValue& ivKey, const IrisValue& ivValue) {
	m_mpHash[ivKey] = ivValue;
	return ivValue;
}

IrisHashTag::~IrisHashTag()
{
}
