#ifndef _H_IRISPOINTERTAG_
#define _H_IRISPOINTERTAG_

#include <string>
using namespace std;

class IrisPointerTag
{
private:
	char* m_pBuffer = nullptr;
	size_t m_nLength = 0;

public:
	IrisPointerTag();

	bool Initialize(int nLength);

	bool Set(int nPointer, const char* pData, int nLength);
	bool Get(int nPointer, int nLength, string& strResult);

	size_t GetTrustteeSize();

	~IrisPointerTag();
};

#endif