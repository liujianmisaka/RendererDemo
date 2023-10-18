#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace RendererDemo {

class Window {
public:
    Window();
    ~Window();

    virtual void Init();

    virtual void Close();

    virtual void Update();

    virtual bool ShouldClose() const;

    void* GetNativeWindow() const { return m_GLFWWindow; }

private:
    static void windowResizeCallback(GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); }

private:
    GLFWwindow* m_GLFWWindow;
};

} // namespace RendererDemo
