#ifndef _H_IIRISCLOSUREBLOCK_
#define _H_IIRISCLOSUREBLOCK_

#include "IrisUnil/IrisValue.h"

class IIrisValues;
class IIrisClosureBlock
{
public:

	IIrisClosureBlock() {}

	//virtual IrisValue Excute(IIrisValues* pValues) = 0;

	virtual ~IIrisClosureBlock() = 0 {};
};

#endif