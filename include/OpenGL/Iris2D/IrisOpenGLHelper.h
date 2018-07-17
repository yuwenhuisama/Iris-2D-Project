//
// Created by Huisama on 2018/4/20.
//

#ifndef OPENGL_LEARNING_OPENGLHELPER_H
#define OPENGL_LEARNING_OPENGLHELPER_H

#include <functional>
#include <string>

#ifdef _WIN32
#undef CreateWindow
#endif // _WIN32

class GLFWwindow;
typedef void (* GLFWcursorposfun)(GLFWwindow*,double,double);
typedef void (* GLFWscrollfun)(GLFWwindow*,double,double);

class IrisOpenGLHelper {
private:
    GLFWwindow* m_pWindow = nullptr;

private:
public:
    GLFWwindow *getWindow() const;

private:
    IrisOpenGLHelper() = default;
    virtual ~IrisOpenGLHelper() = default;

public:
    static IrisOpenGLHelper* Instance();

    bool Initialze();
    bool CreateWindow(unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight, const std::wstring& strTitle);

    bool ShouldBeClosed();

    void Terminate();

    void SetCursorEventCallback(GLFWcursorposfun fCallbacks);
    void SetScrollEventCallback(GLFWscrollfun fCallback);
};


#endif //OPENGL_LEARNING_OPENGLHELPER_H
