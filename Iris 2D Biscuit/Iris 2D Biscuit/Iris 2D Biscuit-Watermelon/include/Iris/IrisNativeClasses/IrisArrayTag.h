#ifndef _H_IRISARRAYTAG_
#define _H_IRISARRAYTAG_

#include "IrisValue.h"
#include "IrisInterpreter.h"
#include <vector>
using namespace std;

class IrisArrayTag
{
private:
	vector<IrisValue> m_vcValues;

public:

	void Initialize(IrisValues* pValues);
	IrisValue At(int nIndex);
	IrisValue Set(int nIndex, const IrisValue& ivValue);
	IrisValue Push(const IrisValue& ivValue);
	IrisValue Pop();
	int Size();

	IrisArrayTag();
	~IrisArrayTag();

	friend class IrisArray;
	friend class IrisStatement;
};

#endif