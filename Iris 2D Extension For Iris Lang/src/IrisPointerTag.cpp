#include "IrisPointerTag.h"



IrisPointerTag::IrisPointerTag()
{
}

bool IrisPointerTag::Initialize(int nLength)
{
	m_pBuffer = new char[nLength];
	m_nLength = nLength;
	return true;
}

bool IrisPointerTag::Set(int nPointer, const char * pData, int nLength)
{
	if (nPointer < 0 || nLength < 0) {
		return false;
	}
	if (nPointer + nLength > (int)m_nLength) {
		return false;
	}
	memcpy(m_pBuffer + nPointer, pData, nLength);
	return true;
}

bool IrisPointerTag::Get(int nPointer, int nLength, string & strResult)
{
	if (nPointer < 0 || nLength < 0) {
		return false;
	}
	if (nPointer + nLength >(int)m_nLength) {
		return false;
	}

	strResult.assign(m_pBuffer, nLength);

	return true;
}

size_t IrisPointerTag::GetTrustteeSize()
{
	return sizeof(IrisPointerTag) + m_nLength;
}

IrisPointerTag::~IrisPointerTag()
{
	if (m_pBuffer) {
		delete[] m_pBuffer;
	}
}
