//
// Created by Huisama on 2018/4/20.
//

#include "OpenGL/Iris2D/IrisOpenGLHelper.h"

#include <iostream>
#include <codecvt>

#include <glew.h>
#include <glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "OpenGL/OpenGLUtil/stb_image.h"

IrisOpenGLHelper* IrisOpenGLHelper::Instance() {
    static IrisOpenGLHelper oglHelper;
    return &oglHelper;
}

bool IrisOpenGLHelper::Initialze() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    stbi_set_flip_vertically_on_load(true);

    return true;
}

bool IrisOpenGLHelper::ShouldBeClosed() {
    return static_cast<bool>(glfwWindowShouldClose(this->m_pWindow));
}

void IrisOpenGLHelper::Terminate() {
    glfwTerminate();
}

GLFWwindow *IrisOpenGLHelper::getWindow() const {
    return m_pWindow;
}

void IrisOpenGLHelper::SetCursorEventCallback(GLFWcursorposfun fCallback) {
    glfwSetCursorPosCallback(this->getWindow(), fCallback);
}

void IrisOpenGLHelper::SetScrollEventCallback(GLFWscrollfun fCallback) {
    glfwSetScrollCallback(this->getWindow(), fCallback);
}

bool IrisOpenGLHelper::CreateWindow(unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight,
                                    const std::wstring &strTitle) {
    using convert_type = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_type, wchar_t> converter;

    auto strConverted = converter.to_bytes(strTitle);
    // create pWindow
    auto pWindow = glfwCreateWindow(nWidth, nHeight, strConverted.c_str(), nullptr, nullptr);
    glfwSetWindowPos(pWindow, nX, nY);

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

    this->m_pWindow = pWindow;

    glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glewExperimental = GL_TRUE;
    glewInit();

    glEnable(GL_DEPTH_TEST);

    return true;
}
