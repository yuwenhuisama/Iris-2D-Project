#ifndef _H_REF_COUNTER_
#define _H_REF_COUNTER_
#include <type_traits>
#include "Common/Util/ProxyConvert.h"


#ifndef _WIN32
template <class T>
using remove_pointer_t = typename std::remove_pointer<T>::type;
#endif

namespace Iris2D
{
	class RefCounter
	{
	protected:
		unsigned int m_nRefCount = 0;

	public:
		unsigned int GetRefCount() const;
		void IncreamRefCount();
		void DecreamRefCount();

	public:
		RefCounter();
		virtual ~RefCounter() = default;
	};

	template <typename PT, typename T>
	void RefferAssign(T& refferrer, const T& refferee) {
#ifdef _WIN32
		using R_PT = std::remove_pointer_t<PT>;
#else
		using R_PT = remove_pointer_t<PT>;
#endif
		static_assert(std::is_base_of<Iris2D::RefCounter, R_PT>::value, "Only RefCounter type can use RefferAssign function.");

		GetProxied<PT>(refferee)->IncreamRefCount();
		refferrer = refferee;
	}

	template <typename T>
	void RefferRelease(T& refferer) {
#ifdef  _WIN32
		using R_T = std::remove_pointer_t<T>;
#else
		using R_T = remove_pointer_t<T>;
#endif
		static_assert(std::is_base_of<Iris2D::RefCounter, R_T>::value, "Only RefCounter type can use RefferRelease function.");
		refferer->DecreamRefCount();
		if (refferer->GetRefCount() == 0) {
			delete refferer;
			refferer = nullptr;
		}
	}
}

#define REF_FRIEND_DECLARE\
		template <typename T>\
		friend void Iris2D::RefferRelease(T& refferer);


#endif // _H_REF_COUNTER_
