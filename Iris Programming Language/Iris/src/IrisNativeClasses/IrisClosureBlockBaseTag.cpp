#include "IrisClosureBlockBaseTag.h"



IrisClosureBlockBaseTag::IrisClosureBlockBaseTag(IrisClosureBlock* pClosureBlock) : m_pClosureBlock(pClosureBlock)
{
}

IrisClosureBlock* IrisClosureBlockBaseTag::GetClosureBlock() {
	return m_pClosureBlock;
}

void IrisClosureBlockBaseTag::SetClosureBlock(IrisClosureBlock* pClosureBlock) {
	m_pClosureBlock = pClosureBlock;
}

IrisClosureBlockBaseTag::~IrisClosureBlockBaseTag()
{
}
