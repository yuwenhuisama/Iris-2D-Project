#ifndef _H_IIRISINTERFACE_
#define _H_IIRISINTERFACE_

class IrisInterface;
class IIrisInterface
{
private:
	IrisInterface* m_pInternInterface = nullptr;

public:

	inline virtual IrisInterface* GetInternInterface() { return m_pInternInterface; }

	IIrisInterface() {}

	virtual ~IIrisInterface() = 0 {};

	friend class IrisInterface;
};

#endif