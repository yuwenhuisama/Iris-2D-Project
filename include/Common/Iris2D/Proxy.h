#ifndef _H_PROXY_
#define _H_PROXY_

namespace Iris2D {
	template<typename P> class Proxy {
	protected:
		P* m_pProxied = nullptr;

	public:
		Proxy(P* pProxied) : m_pProxied(pProxied) {}

		P * GetProxied() const { return m_pProxied; }
		void SetProxied(P* pProxied) { m_pProxied = pProxied; }
	};

};

#endif // !_H_PROXY_
