#include "IrisHeap.h"
#include "IrisObject.h"

IrisHeap::IrisHeap()
{
}

void IrisHeap::AddObject(IrisObject* pObject) {
	m_lsHeap.push_back(pObject);
}

void IrisHeap::RemoveObject(IrisObject* pObject) {
	m_lsHeap.remove(pObject);
}

list<IrisObject*>& IrisHeap::GetHeapList() {
	return m_lsHeap;
}

IrisHeap::~IrisHeap()
{
}
