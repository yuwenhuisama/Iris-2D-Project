#include "Common/Util/DirtyChecker.h"
#include <winerror.h>

namespace Iris2D {

	DirtyChecker::DirtyCheckerHandler DirtyChecker::Register() {
		const auto nIndex = m_vcSlot.size();
		m_vcSlot.push_back(true);
		return nIndex + 1;
	}

	void DirtyChecker::SetDirty(DirtyCheckerHandler hHandler) {
		m_vcSlot[hHandler - 1] = true;
	}

	void DirtyChecker::DoIfDirty(DirtyCheckerHandler hHandler, const std::function<void()>& fCondition, bool bReset) {
		if (IsDirty(hHandler)) {
			fCondition();
			if (bReset) {
				ResetDirty(hHandler);
			}
		}
	}

	void DirtyChecker::ResetDirty(DirtyCheckerHandler hHandler) {
		m_vcSlot[hHandler - 1] = false;
	}

	bool DirtyChecker::IsDirty(DirtyCheckerHandler hHandler) const {
		return m_vcSlot[hHandler - 1];
	}
}
