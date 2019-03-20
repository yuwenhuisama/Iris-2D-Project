#ifndef _H_DEBUG_CONSOLE_
#define _H_DEBUG_CONSOLE_

#include <string>

#ifdef _WIN32
#include <Windows.h>
#endif

#include <queue>
#include <iostream>
namespace Iris2D {
	class DebugConsole {
#if defined(_WIN32) && defined(_DEBUG)
	private:
		unsigned int m_nMaxBufferSize = 0;
		HANDLE m_hOutput = nullptr;
		std::queue<std::string> m_vcDebugBuffer{};
#endif

	public:
		static DebugConsole* Instance();

	public:
		void Create();
		void Release();
		void AppendString(const std::string& strInfo);
		void ShowInfo();

	private:
		DebugConsole() = default;
		~DebugConsole() = default;

	};
}

#endif // !_H_DEBUG_CONSOLE_