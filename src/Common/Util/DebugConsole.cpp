#include "Common/Util/DebugUtil.h"
#include "Common/Iris2D/Graphics.h"
#include <boost/format.hpp>
#include "Common/Common.h"
#include "Common/Iris2D/AppFactory.h"
#include <cstdlib>
#include <Common/Util/DebugConsole.h>


#if defined(_WIN32) && defined(_DEBUG)
namespace Iris2D {

	DebugConsole* DebugConsole::Instance() {
		static DebugConsole console;
		return &console;
	}

	void DebugConsole::Create() {
#if defined(_WIN32) && defined(_DEBUG)
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
#endif
	}

	void DebugConsole::Release() {
#if defined(_WIN32) && defined(_DEBUG)
		FreeConsole();
#endif
	}

	void DebugConsole::AppendString(const std::string& strInfo) {
#if defined(_WIN32) && defined(_DEBUG)
		if (m_vcDebugBuffer.size() >= m_nMaxBufferSize) {
			m_vcDebugBuffer.pop();
		}

		m_vcDebugBuffer.push(strInfo);
		ShowInfo();
#endif
	}


	const std::string c_strDebugHeaderTemplate =
"\
 * =============================================================\n\
 * Iris 2D Debug Information Window\n\
 * Iris 2D Version : %1%\n\
 * Graphics Api Type : %2%\n\
 * Frame Per Second: %3%\n\
 * Draw Call Times Per Frame: %4%\n\
 * Shader Switch Times Per Frame: %5%\n\
 * =============================================================\n\
";

	void DebugConsole::ShowInfo() {
#if defined(_WIN32) && defined(_DEBUG)
		system("cls");

		boost::format ftFormatter(c_strDebugHeaderTemplate);
		ftFormatter % IR_VERSION;
		switch (AppFactory::GetApiType()) {
		case ApiType::OpenGL:
			ftFormatter % "OpenGL 3.3";
			break;
		case ApiType::DirectX:
			ftFormatter % "Direct3D 11, Direct2D";
			break;
		default: ;
		}

		ftFormatter % Graphics::Instance()->GetFrameRate();

		ftFormatter % DebugCounter::Instance()->GetDrawCallTimesPerFrame() % DebugCounter::Instance()->GetShaderSwitchTimesPerFrame();

		std::cout << ftFormatter.str() << std::endl;
#endif
	}
}

#else
Iris2D::DebugConsole *Iris2D::DebugConsole::Instance() {
    return nullptr;
}

void Iris2D::DebugConsole::Create() {

}

void Iris2D::DebugConsole::Release() {

}

void Iris2D::DebugConsole::AppendString(const std::string &strInfo) {

}

void Iris2D::DebugConsole::ShowInfo() {

}
#endif
