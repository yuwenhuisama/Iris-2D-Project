#include "Common/Util/RefCounter.h"

namespace Iris2D
{
	unsigned int RefCounter::GetRefCount() const
	{
		return m_nRefCount;
	}

	void RefCounter::IncreamRefCount()
	{
		++m_nRefCount;
	}

	void RefCounter::DecreamRefCount()
	{
		--m_nRefCount;
	}

	RefCounter::RefCounter() {
		++m_nRefCount;
	}
}
