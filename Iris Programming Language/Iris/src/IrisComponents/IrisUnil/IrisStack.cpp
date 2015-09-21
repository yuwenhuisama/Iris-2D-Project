#include "IrisStack.h"


IrisStack::IrisStack()
{
}

IrisValue IrisStack::Pop() {
	IrisValue ivCurTop = m_lsStack.back();
	m_lsStack.pop_back();
	return ivCurTop;
}

void IrisStack::Push(IrisValue ivValue) {
	m_lsStack.push_back(ivValue);
}

void IrisStack::Clear() {
	m_lsStack.clear();
}

IrisStack::~IrisStack()
{
}
