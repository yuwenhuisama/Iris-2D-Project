#ifndef _H_REF_COUNTER_
#define _H_REF_COUNTER_

namespace Iris2D
{
	class RefCounter
	{
	protected:
		unsigned int m_nRefCount = 0;

	public:
		unsigned int GetRefCount();
		void IncreamRefCount();
		void DecreamRefCount();

	public:
		RefCounter() = default;
		virtual ~RefCounter() = 0;
	};
}
#endif // _H_REF_COUNTER_
