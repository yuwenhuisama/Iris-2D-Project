#ifndef	_H_DEBUG_UTIL_
#define _H_DEBUG_UTIL_

#include <string>
#include <iostream>

#include <boost/format.hpp>

#ifdef _WIN32
#include <WinString.h>
#include <Windows.h>
#endif

namespace Iris2D {
	inline void _PrintDebugMessageW(const std::wstring& strMsg, unsigned int strLineNumber = 0, const char* strFileNumber = nullptr) {
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
		std::cout << "=======================\n";
#endif // _WIN32
#endif // _DEBUG
	}

	inline void _PrinFormatDebugMessageW(const boost::wformat& wftFormatter) {}

	template<typename T, typename... Args>
	void _PrinFormatDebugMessageW(boost::wformat& wftFormatter, T head, Args... args) {
		wftFormatter % head;
		_PrinFormatDebugMessageW(wftFormatter, args...);
	}

	template<typename... Args>
	void _PrinFormatDebugMessageW(unsigned int strLineNumber, const char* strFileNumber, const std::wstring& strFormat, Args... args) {
		boost::wformat wftFormatter(strFormat);
		_PrinFormatDebugMessageW(wftFormatter, args...);
		_PrintDebugMessageW(wftFormatter.str(), strLineNumber, strFileNumber);
	}

	inline void _PrintDebugMessageA(const std::string& strMsg, unsigned int strLineNumber = 0, const char* strFileNumber = nullptr) {
#ifdef _DEBUG
		const auto strOutput = std::string("Debug: ") + strMsg.c_str() + "\n";

#ifdef _WIN32
		::OutputDebugStringA("=======================\n");
		::OutputDebugStringA("Iris 2D Debug Message :\n");
		::OutputDebugStringA(strOutput.c_str());
		if (strLineNumber && strFileNumber) {
			boost::format ftFormatter("At line %1%, file %2%");
			ftFormatter % strLineNumber % strFileNumber;
			::OutputDebugStringA(ftFormatter.str().c_str());
			::OutputDebugStringA("\n");
		}
		::OutputDebugString("=======================\n");
#else
		std::cout << "=======================\n";
		std::cout << "Iris 2D Debug Message :\n";
		std::cout << strOutput;
		if (strLineNumber && strFileNumber) {
			boost::format ftFormatter("At line %1%, file %2%");
			ftFormatter % strLineNumber % strFileNumber;
			std::cout << ftFormatter.str() << std::endl;
		}
		std::cout << "=======================\n";
#endif // _WIN32
#endif // _DEBUG
	}

	inline void _PrinFormatDebugMessageA(const boost::format& ftFormatter) {}

	template<typename T, typename... Args>
	void _PrinFormatDebugMessageA(boost::format& ftFormatter, T head, Args... args) {
		ftFormatter % head;
		_PrinFormatDebugMessageA(ftFormatter, args...);
	}

	template<typename... Args>
	void _PrinFormatDebugMessageA(unsigned int strLineNumber, const char* strFileNumber, const std::string& strFormat, Args... args) {
		boost::format ftFormatter(strFormat);
		_PrinFormatDebugMessageA(ftFormatter, args...);
		_PrintDebugMessageA(ftFormatter.str(), strLineNumber, strFileNumber);
	}

#ifdef _DEBUG
#define PrintFormatDebugMessageW(wstrFormat, ...) _PrinFormatDebugMessageW(__LINE__, __FILE__, wstrFormat, __VA_ARGS__)
#define PrintDebugMessageW(wstrMessage) _PrintDebugMessageW(wstrMessage, __LINE__, __FILE__)

#define PrintFormatDebugMessageA(strFormat, ...) _PrinFormatDebugMessageA(__LINE__, __FILE__, strFormat, __VA_ARGS__)
#define PrintDebugMessageA(strMessage) _PrintDebugMessageA(strMessage, __LINE__, __FILE__)
#else
#define PrintFormatDebugMessageW(wstrFormat, ...)
#define PrintDebugMessageW(wstrMessage)

#define PrintFormatDebugMessageA(strFormat, ...)
#define PrintDebugMessageA(strMessage)
#endif

#if defined(_WIN32) && defined(_DEBUG)
	class DebugConsole {
	private:
		HANDLE m_hOutput = nullptr;

	public:
		void Create() {
			AllocConsole();
			m_hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTitle("Debug Information");
			SetConsoleTextAttribute(m_hOutput, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

			HWND hWnd = nullptr;
			while (nullptr == hWnd) {
				hWnd = FindWindowA(nullptr, "Debug Information");
			}

			auto hMenu = ::GetSystemMenu(hWnd, false);
			DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);

			freopen("CONOUT$", "w", stdout);
			std::cout << "Iris 2D Debug Information Window." << std::endl;
		}

		void Release() {
			FreeConsole();
		}

	};
#endif

}

#endif
