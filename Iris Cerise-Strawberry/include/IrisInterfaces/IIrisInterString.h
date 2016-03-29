#ifndef _H_IIRISINTERSTRING_
#define _H_IIRISINTERSTRING_
class IIrisInterString
{
public:

	virtual const char* GetCTypeString() const = 0;

	IIrisInterString() {}

	virtual ~IIrisInterString() = 0 {};
};

#endif