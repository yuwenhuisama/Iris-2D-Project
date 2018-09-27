#include "Common/Util/DebugCounter.h"

namespace Iris2D {
	DebugCounter * Iris2D::DebugCounter::Instance() {
		static DebugCounter counter;
		return &counter;
	}

	void DebugCounter::ResetFrameData() {
		m_nDrawCallTimesPerFrame = 0;
		m_nShaderSwitchTimesPerFrame = 0;
	}

	void DebugCounter::IncreaseShaderSwitchTimesPerFrame() {
		++m_nShaderSwitchTimesPerFrame;
	}

	void DebugCounter::IncreaseDrawCallTimesPerFrame() {
		++m_nDrawCallTimesPerFrame;
	}

	unsigned DebugCounter::GetShaderSwitchTimesPerFrame() const {
		return m_nShaderSwitchTimesPerFrame;
	}

	unsigned DebugCounter::GetDrawCallTimesPerFrame() const {
		return m_nDrawCallTimesPerFrame;
	}
}
