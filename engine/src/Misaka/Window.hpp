#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace RendererDemo {

class Window {
public:
    Window();
    ~Window();

    void init();

    void close();

    bool shouldClose() const;

    void update();

    void* GetNativeWindow() const { return m_GLFWWindow; }

private:
    static void windowResizeCallback(GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); }

private:
    GLFWwindow* m_GLFWWindow;
};

} // namespace RendererDemo