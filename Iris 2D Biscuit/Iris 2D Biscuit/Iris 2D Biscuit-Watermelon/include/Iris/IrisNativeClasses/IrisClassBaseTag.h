#ifndef _H_IRISCLASSBASETGA_
#define _H_IRISCLASSBASETGA_

#include "IrisClass.h"

class IrisClassBaseTag
{
private:
	IrisClass* m_pClass = nullptr;

public:

	const string& GetClassName();
	void SetClass(IrisClass* pClass);
	IrisClass* GetClass();

	IrisClassBaseTag(IrisClass* pClass);
	~IrisClassBaseTag();
};

#endif