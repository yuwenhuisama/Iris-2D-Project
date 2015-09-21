#ifndef _H_IRISHEAP_
#define _H_IRISHEAP_

#include <list>
using namespace std;

class IrisObject;
class IrisHeap
{
private:
	list<IrisObject*> m_lsHeap;

public:
	void AddObject(IrisObject* pObject);
	void RemoveObject(IrisObject* pObject);
	list<IrisObject*>& GetHeapList();

	IrisHeap();
	~IrisHeap();
};

#endif