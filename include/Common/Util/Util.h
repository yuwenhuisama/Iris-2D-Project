#ifndef _UTIL_
#define _UTIL_

#include <algorithm>

#ifdef _WIN32
#undef max
#undef min
#endif

namespace Iris2D {
	template <typename T>
	T clip(const T& n, const T& lower, const T& upper) {
		return std::max(lower, std::min(n, upper));
	}
}

#endif // _UTIL_