#ifndef _H_PROXY_CONVERT_
#define _H_PROXY_CONVERT_

#include "Common/Iris2D/Proxy.h"

namespace Iris2D {
	template<typename T1, typename T2>
	inline T1 GetProxied(T2 pProxy) {
		return static_cast<T1*>(pProxy->GetProxied());
	}
}

#endif // !_H_PROXY_CONVERT_
