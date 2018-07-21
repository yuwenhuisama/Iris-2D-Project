//
// Created by Huisama on 2018/4/20.
//

#ifndef _H_OPENGL_HELPER_
#define _H_OPENGL_HELPER_

#include <functional>
#include <string>

struct GLFWwindow;

namespace Iris2D {
	typedef void(*GLFWcursorposfun)(GLFWwindow*, double, double);
	typedef void(*GLFWscrollfun)(GLFWwindow*, double, double);

	class OpenGLHelper {
	private:
		GLFWwindow * m_pWindow = nullptr;

	public:
		GLFWwindow * GetWindow() const;

	private:
		OpenGLHelper() = default;
		virtual ~OpenGLHelper() = default;

	public:
		static OpenGLHelper * Instance();

		bool Initialze();
		bool InitializeWindow(unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight, const std::wstring& strTitle);
		void ShowWindow();

		bool ShouldBeClosed();

		void Terminate();

		void SetCursorEventCallback(GLFWcursorposfun fCallbacks);
		void SetScrollEventCallback(GLFWscrollfun fCallback);
	};
}

#endif //_H_OPENGL_HELPER_
