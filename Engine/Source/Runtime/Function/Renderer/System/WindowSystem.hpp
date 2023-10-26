#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

#include "Runtime/Core/Handler/TransactionHandler.hpp"

namespace RendererDemo {

class WindowSystem {
public:
    WindowSystem() = default;
    ~WindowSystem() = default;

    void Initialize(int width = 1280, int height = 960, const std::string& title = "Misaka Engine");
    void Clear();

    bool ShouldClose() const;
    void PollEvents() const;
    void SwapBuffers() const;
    GLFWwindow* GetNativeWindow() const;

private:
    static void SetGLFWCallbacks(GLFWwindow* m_window);
    static void SetTransactionHandler();

private:
    GLFWwindow* m_GLFWWindow;
    int m_width = 0;
    int m_height = 0;
    std::string m_title = "Misaka Engine";

    static TransactionHandler m_window_event_handler;

private:
    // window callback functions

    static void WindowCloseCallback(GLFWwindow* window) {
        m_window_event_handler.ProcessTransaction(TransactionType::WindowClose);
        glfwSetWindowShouldClose(window, true);
    }

    static void WindowResizeCallback(GLFWwindow* window, int width, int height) {
        m_window_event_handler.ProcessTransaction(TransactionType::WindowResize, window, width, height);
        glViewport(0, 0, width, height);
    }
};

} // namespace RendererDemo
