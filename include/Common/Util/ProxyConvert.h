#ifndef _H_PROXY_CONVERT_
#define _H_PROXY_CONVERT_

#include "Common/Iris2D/Proxy.h"

namespace Iris2D {
	template<typename T1, typename T2>
	T1 GetProxied(T2 pProxy) {
		using R_T1 = std::remove_pointer_t<T1>;

		static_assert(std::is_base_of<std::remove_pointer_t<decltype(pProxy->GetProxied())>, R_T1>::value, "Wrong convert operation happend in GetProxied() function.");

		return pProxy ? static_cast<T1>(pProxy->GetProxied()) : nullptr;
	}
}

#endif // !_H_PROXY_CONVERT_
