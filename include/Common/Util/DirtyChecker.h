#ifndef _H_DIRTY_CHECKER_
#define _H_DIRTY_CHECKER_

#include <vector>
#include <functional>

namespace Iris2D {
	class DirtyChecker {
	public:
		typedef unsigned int DirtyCheckerHandler;

	public:
		DirtyCheckerHandler Register();
		void SetDirty(DirtyCheckerHandler hHandler);
		void DoIfDirty(DirtyCheckerHandler hHandler, const std::function<void()>& fCondition, bool bReset = true);
		void ResetDirty(DirtyCheckerHandler hHandler);
		bool IsDirty(DirtyCheckerHandler hHandler) const;

		template<typename T1, typename T2>
		void Assign(T1& a, T2& b, DirtyCheckerHandler hHandler) {
			if (a != b) {
				SetDirty(hHandler);
				a = b;
			}
		}
	private:
		std::vector<bool> m_vcSlot;

	public:
		DirtyChecker() = default;
		~DirtyChecker() = default;
	};
}

#endif // _H_DIRTY_CHECKER_
