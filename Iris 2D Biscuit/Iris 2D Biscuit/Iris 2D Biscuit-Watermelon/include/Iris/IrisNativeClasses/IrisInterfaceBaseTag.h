#ifndef _H_IRISINTERFACEBASETAG_
#define _H_IRISINTERFACEBASETAG_

#include "IrisInterface.h"

class IrisInterfaceBaseTag
{
private:
	IrisInterface* m_pInterface = nullptr;

public:

	const string& GetInterfaceName();
	void SetInterface(IrisInterface* pInterface);
	IrisInterface* GetInterface();

public:
	IrisInterfaceBaseTag(IrisInterface* pInterface);
	~IrisInterfaceBaseTag();
};

#endif