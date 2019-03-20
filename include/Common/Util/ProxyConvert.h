#ifndef _H_PROXY_CONVERT_
#define _H_PROXY_CONVERT_

#include "Common/Iris2D/Proxy.h"

#ifndef _WIN32
template <class T>
using remove_pointer_t = typename std::remove_pointer<T>::type;
#endif

namespace Iris2D {
	template<typename T1, typename T2>
	T1 GetProxied(T2 pProxy) {
#ifdef _WIN32
		using R_T1 = std::remove_pointer_t<T1>;
		static_assert(std::is_base_of<std::remove_pointer_t<decltype(pProxy->GetProxied())>, R_T1>::value, "Wrong convert operation happend in GetProxied() function.");
#else
//		using R_T1 = std::remove_pointer<T1>;
//        static_assert(std::is_base_of<remove_pointer_t<decltype(pProxy->GetProxied())>, R_T1>::value, "Wrong convert operation happend in GetProxied() function.");
#endif
		return pProxy ? static_cast<T1>(pProxy->GetProxied()) : nullptr;
	}
}

#endif // !_H_PROXY_CONVERT_
