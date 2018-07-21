//
// Created by Huisama on 2018/4/20.
//

#include "OpenGL/Iris2D/OpenGLHelper.h"
#include "OpenGL/Common.h"

#include <iostream>
#include <codecvt>

#include <glew.h>
#include <glfw3.h>

#ifdef _WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#include <glfw3native.h>
#include <Windows.h>
#endif // _WIN32

namespace Iris2D {
	OpenGLHelper * OpenGLHelper::Instance() {
		static OpenGLHelper oglHelper;
		return &oglHelper;
	}

	bool OpenGLHelper::Initialze() {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
		return true;
	}

	bool OpenGLHelper::ShouldBeClosed() {
		return static_cast<bool>(glfwWindowShouldClose(this->m_pWindow));
	}

	void OpenGLHelper::Terminate() {
		glfwTerminate();
	}

	GLFWwindow *OpenGLHelper::GetWindow() const {
		return m_pWindow;
	}

	void OpenGLHelper::SetCursorEventCallback(GLFWcursorposfun fCallback) {
		glfwSetCursorPosCallback(this->GetWindow(), fCallback);
	}

	void OpenGLHelper::SetScrollEventCallback(GLFWscrollfun fCallback) {
		glfwSetScrollCallback(this->GetWindow(), fCallback);
	}

	bool OpenGLHelper::InitializeWindow(unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight,const std::wstring &strTitle) {
		using convert_type = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_type, wchar_t> converter;

		auto strConverted = converter.to_bytes(strTitle);
		// create pWindow
		auto pWindow = glfwCreateWindow(nWidth, nHeight, strConverted.c_str(), nullptr, nullptr);
		
#ifdef _WIN32
		RECT rcArea = { 0, 0, nWidth, nHeight};
		AdjustWindowRect(&rcArea, WS_OVERLAPPEDWINDOW, false);

		auto hHwnd = glfwGetWin32Window(pWindow);
		::SetWindowPos(hHwnd, HWND_TOP, nX, nY, rcArea.right - rcArea.left, rcArea.bottom - rcArea.top, 0);
#endif // _WIN32

		if (!pWindow) {
			std::cout << "Failed to create GLFW pWindow" << std::endl;
			glfwTerminate();
			return false;
		}

		// set pWindow to context
		glfwMakeContextCurrent(pWindow);

		glfwSetFramebufferSizeCallback(pWindow, [](GLFWwindow* window, int width, int height) -> void {
			glViewport(0, 0, width, height);
		});

		m_pWindow = pWindow;

		// glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		glewExperimental = GL_TRUE;
		glewInit();

		glEnable(GL_DEPTH_TEST);

		return true;
	}

	void OpenGLHelper::ShowWindow() {
		glfwShowWindow(m_pWindow);
	}
}
