#ifndef	_H_DEBUG_UTIL_
#define _H_DEBUG_UTIL_

#include <string>
#include <iostream>

#include <boost/format.hpp>

#ifdef _WIN32
#include <WinString.h>
#endif

namespace Iris2D {
	inline void _PrintDebugMessage(const std::wstring& strMsg, unsigned int strLineNumber = 0, const char* strFileNumber = nullptr) {
#ifdef _DEBUG
		const auto strOutput = std::wstring(L"Debug: ") + strMsg.c_str() + L"\n";

#ifdef _WIN32
		::OutputDebugStringW(L"=======================\n");
		::OutputDebugStringW(L"Iris 2D Debug Message :\n");
		::OutputDebugStringW(strOutput.c_str());
		if (strLineNumber && strFileNumber) {
			boost::format ftFormatter("At line %1%, file %2%");
			ftFormatter % strLineNumber % strFileNumber;
			::OutputDebugStringA(ftFormatter.str().c_str());
			::OutputDebugStringA("\n");
		}
		::OutputDebugStringW(L"=======================\n");
#else
		std::cout << "=======================\n";
		std::cout << "Iris 2D Debug Message :\n";
		std::cout << strOutput;
		if (strLineNumber && strFileNumber) {
			boost::format ftFormatter("At line %1%, file %2%");
			ftFormatter % strLineNumber % strFileNumber;
			std::cout << ftFormatter.str() << std::endl;
		}
		std::cout << L"=======================\n";
#endif // _WIN32
#endif // _DEBUG
	}

	inline void _PrinFormatDebugMessage(const boost::wformat& wftFormatter) {}

	template<typename T, typename... Args>
	void _PrinFormatDebugMessage(boost::wformat& wftFormatter, T head, Args... args) {
		wftFormatter % head;
		_PrinFormatDebugMessage(wftFormatter, args...);
	}

	template<typename... Args>
	void _PrinFormatDebugMessage(unsigned int strLineNumber, const char* strFileNumber, const std::wstring& strFormat, Args... args) {
		boost::wformat wftFormatter(strFormat);
		_PrinFormatDebugMessage(wftFormatter, args...);
		_PrintDebugMessage(wftFormatter.str(), strLineNumber, strFileNumber);
	}

#define PrintFormatDebugMessage(wstrFormat, ...) _PrinFormatDebugMessage(__LINE__, __FILE__, wstrFormat, __VA_ARGS__)
#define PrintDebugMessage(wstrMessage) _PrintDebugMessage(wstrMessage, __LINE__, __FILE__)

}

#endif
