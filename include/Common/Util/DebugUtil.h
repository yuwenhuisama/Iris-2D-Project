#ifndef	_H_DEBUG_UTIL_
#define _H_DEBUG_UTIL_

#include <string>
#include <iostream>
#include <WinString.h>

namespace Iris2D {
	inline void PrintDebugMessage(const std::wstring& strMsg) {
#ifdef _DEBUG

#ifdef _WIN32
		const auto strOutput = std::wstring(L"Debug:") + strMsg.c_str();
		::OutputDebugStringW(strOutput.c_str());
#else
		cout << "Debug: " << strMsg << endl;
#endif // _WIN32

#endif // _DEBUG
	}

	template<typename... Args>
	void PrinFormatDebugMessage(const std::wstring& strFormat, Args... args) {
		
	}
}

#endif
