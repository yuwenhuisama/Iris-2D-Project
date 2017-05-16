#include "Iris2D Util/IrisRefCounter.h"

namespace Iris2D
{
	unsigned int IrisRefCounter::GetRefCount()
	{
		return m_nRefCount;
	}

	void IrisRefCounter::IncreamRefCount()
	{
		++m_nRefCount;
	}

	void IrisRefCounter::DecreamRefCount()
	{
		--m_nRefCount;
	}

	IrisRefCounter::~IrisRefCounter()
	{

	}

}