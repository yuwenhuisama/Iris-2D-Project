#ifndef _H_PROXIED_
#define _H_PROXIED_

namespace Iris2D {
	template<typename T>
	class Proxied {
	protected:
		T* m_pProxy = nullptr;

	public:
		void SetProxy(T* pProxy) { m_pProxy = pProxy; }
		T* GetProxy() const { return m_pProxy; }
	};
}

#endif // !_H_PROXIED_
