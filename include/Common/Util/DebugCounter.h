#ifndef _H_DEBUG_COUNTER_
#define _H_DEBUG_COUNTER_

namespace Iris2D {
	class DebugCounter {
	private:
		unsigned int m_nShaderSwitchTimesPerFrame = 0;
		unsigned int m_nDrawCallTimesPerFrame = 0;

	public:
		static DebugCounter* Instance();

		void ResetFrameData();
		void IncreaseShaderSwitchTimesPerFrame();
		void IncreaseDrawCallTimesPerFrame();

		unsigned int GetShaderSwitchTimesPerFrame() const;
		unsigned int GetDrawCallTimesPerFrame() const;

	private:
		DebugCounter() = default;
		~DebugCounter() = default;
	};
}

#endif // !_H_DEBUG_COUNTER_
