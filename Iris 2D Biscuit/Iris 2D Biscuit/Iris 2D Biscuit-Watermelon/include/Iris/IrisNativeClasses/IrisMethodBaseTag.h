#ifndef _IRIS_METHODBASETAG_
#define _IRIS_METHODBASETAG_
#include "IrisMethod.h"

class IrisMethodBaseTag
{
private:
	IrisMethod* m_pMethod = nullptr;

public:
	const string& GetMethodName();
	void SetMethod(IrisMethod* pMethod);

	IrisMethodBaseTag(IrisMethod* pMethod);
	~IrisMethodBaseTag();
};

#endif