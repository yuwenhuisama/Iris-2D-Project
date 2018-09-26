#ifndef _UTIL_
#define _UTIL_

#include <algorithm>

#ifdef _WIN32
#undef max
#undef min
#endif

namespace Iris2D {
	template <typename T>
	T Clip(const T& tN, const T& tLower, const T& tUpper) {
		return std::max(tLower, std::min(tN, tUpper));
	}

	template<typename T>
	T RandInRange(T tLower, T tUpper) {
		if (tLower > tUpper) {
			std::swap(tLower, tUpper);
		}
		return rand() / static_cast<double>(RAND_MAX) *(tUpper - tLower) + tLower;
	}
}

#endif // _UTIL_
