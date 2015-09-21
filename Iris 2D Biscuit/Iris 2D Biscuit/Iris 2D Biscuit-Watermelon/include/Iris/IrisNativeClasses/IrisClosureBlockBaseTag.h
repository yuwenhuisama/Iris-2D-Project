#ifndef _H_IRISCLOSUREBLOCKBASETAG_
#define _H_IRISCLOSUREBLOCKBASETAG_

#include "IrisClosureBlock.h"

class IrisClosureBlockBaseTag
{
private:
	IrisClosureBlock* m_pClosureBlock = nullptr;

public:

	IrisClosureBlock* GetClosureBlock();
	void SetClosureBlock(IrisClosureBlock* pColosureBlock);

	IrisClosureBlockBaseTag(IrisClosureBlock* pColosureBlock);
	~IrisClosureBlockBaseTag();
};

#endif