#ifndef _H_IRISMODULEBASETAG_
#define _H_IRISMODULEBASETAG_

#include "IrisModule.h"

class IrisModuleBaseTag
{
private:
	IrisModule* m_pModule = nullptr;

public:
	IrisModuleBaseTag(IrisModule* pModule);

	void SetModule(IrisModule* pModule);
	const string& GetModuleName();

	IrisModule* GetModule();

	~IrisModuleBaseTag();
};

#endif