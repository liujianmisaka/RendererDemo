#include "Runtime/Function/Renderer/System/WindowSystem.hpp"
#include <iostream>
#include <stdexcept>
#include <utility>

namespace RendererDemo {

void WindowSystem::Initialize(int width, int height, const std::string& title) {
    m_width = width;
    m_height = height;
    m_title = std::move(title);

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        throw std::runtime_error("Failed to Init glfw!");
    }

    m_GLFWWindow = glfwCreateWindow(1280, 960, "Renderer Demo", nullptr, nullptr);

    if (!m_GLFWWindow) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        throw std::runtime_error("Failed to create glfwwindow!");
    }

    glfwSetErrorCallback(errorCallback);
    glfwSetWindowUserPointer(m_GLFWWindow, this); // 设置用户指针, 使用 glfwGetWindowUserPointer(GLFWwindow *window) 获取 this 指针

    // TODO: set input callbacks
    SetGLFWCallbacks();

    glfwMakeContextCurrent(m_GLFWWindow);
}

void WindowSystem::Clear() {
    glfwDestroyWindow(m_GLFWWindow);
    glfwTerminate();
}

bool WindowSystem::ShouldClose() const { return glfwWindowShouldClose(m_GLFWWindow); }

void WindowSystem::PollEvents() const { glfwPollEvents(); }

void WindowSystem::SwapBuffers() const { glfwSwapBuffers(m_GLFWWindow); }

GLFWwindow* WindowSystem::GetNativeWindow() const { return m_GLFWWindow; }

WindowDelegateData& WindowSystem::GetWindowDelegateData() { return m_window_delegate_data; }

void WindowSystem::SetGLFWCallbacks() {
    glfwSetWindowCloseCallback(m_GLFWWindow, WindowCloseCallback);
    glfwSetWindowSizeCallback(m_GLFWWindow, WindowResizeCallback);
    glfwSetKeyCallback(m_GLFWWindow, KeyCallback);
    glfwSetCharCallback(m_GLFWWindow, KeyTypedCallbackCallback);
    glfwSetMouseButtonCallback(m_GLFWWindow, MouseButtonCallback);
    glfwSetScrollCallback(m_GLFWWindow, MouseScrolledCallback);
    glfwSetCursorPosCallback(m_GLFWWindow, MouseMovedCallback);

    // glfwSetCharModsCallback(m_GLFWWindow, charModsCallback);
    // glfwSetCursorEnterCallback(m_GLFWWindow, cursorEnterCallback);
    // glfwSetDropCallback(m_GLFWWindow, dropCallback);
}

} // namespace RendererDemo
