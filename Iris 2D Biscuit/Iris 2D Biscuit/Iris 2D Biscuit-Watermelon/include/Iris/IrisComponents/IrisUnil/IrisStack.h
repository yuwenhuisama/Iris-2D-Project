#ifndef _H_IRISSTACK_
#define _H_IRISSTACK_

#include "IrisValue.h"
#include <list>
using namespace std;

class IrisStack
{
private:
	list<IrisValue> m_lsStack;

public:
	IrisValue Pop();
	void Push(IrisValue ivValue);
	void Clear();

	IrisStack();
	~IrisStack();

	friend class IrisGC;
};

#endif