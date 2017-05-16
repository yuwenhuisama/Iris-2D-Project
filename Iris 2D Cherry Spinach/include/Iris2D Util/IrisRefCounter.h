#ifndef _H_IRISREFCOUNTER_
#define _H_IRISREFCOUNTER_

namespace Iris2D
{
	class IrisRefCounter
	{
	protected:
		unsigned int m_nRefCount = 0;

	public:
		unsigned int GetRefCount();
		void IncreamRefCount();
		void DecreamRefCount();

	public:
		IrisRefCounter() = default;
		virtual ~IrisRefCounter() = 0;
	};
}
#endif // _H_IRISREFCOUNTER_
