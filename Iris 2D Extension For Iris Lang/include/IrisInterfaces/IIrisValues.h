#ifndef _H_IIRISVALUES_
#define _H_IIRISVALUES_

#include <IrisUnil/IrisValue.h>

class IIrisValues
{
public:
	IIrisValues() {}

	virtual void Add(const IrisValue& ivValue) = 0;
	virtual const IrisValue& GetValue(size_t nIndex) const = 0;
	virtual void SetValue(size_t nIndex, const IrisValue& ivValue) = 0;
	virtual inline size_t GetSize() = 0;

	virtual ~IIrisValues() = 0 {};
};

#endif