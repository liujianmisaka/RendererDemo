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
        throw std::runtime_error("Failed to Init glfw!");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    m_GLFWWindow = glfwCreateWindow(1280, 960, "Renderer Demo", nullptr, nullptr);

    if (!m_GLFWWindow) {
        glfwTerminate();
        throw std::runtime_error("Failed to create glfwwindow!");
    }

    glfwSetWindowUserPointer(m_GLFWWindow, this); // 设置用户指针, 使用 glfwGetWindowUserPointer(GLFWwindow *window) 获取 this 指针

    glfwMakeContextCurrent(m_GLFWWindow);

    // TODO: set input callbacks
    SetGLFWCallbacks(m_GLFWWindow);
}

void WindowSystem::Clear() {
    glfwDestroyWindow(m_GLFWWindow);
    glfwTerminate();
}

bool WindowSystem::ShouldClose() const { return glfwWindowShouldClose(m_GLFWWindow); }

void WindowSystem::PollEvents() const { glfwPollEvents(); }

void WindowSystem::SwapBuffers() const { glfwSwapBuffers(m_GLFWWindow); }

GLFWwindow* WindowSystem::GetNativeWindow() const { return m_GLFWWindow; }

void WindowSystem::SetGLFWCallbacks(GLFWwindow* m_window) {
    glfwSetWindowCloseCallback(m_window, WindowCloseCallback);
    glfwSetWindowSizeCallback(m_window, WindowResizeCallback);

    // glfwSetKeyCallback(m_window, keyCallback);
    // glfwSetCharCallback(m_window, charCallback);
    // glfwSetCharModsCallback(m_window, charModsCallback);
    // glfwSetMouseButtonCallback(m_window, mouseButtonCallback);
    // glfwSetCursorPosCallback(m_window, cursorPosCallback);
    // glfwSetCursorEnterCallback(m_window, cursorEnterCallback);
    // glfwSetScrollCallback(m_window, scrollCallback);
    // glfwSetDropCallback(m_window, dropCallback);
}

void WindowSystem::SetTransactionHandler() {
    m_window_event_handler.AddHandler<GLFWwindow*>(TransactionType::WindowClose, [](GLFWwindow* window) {
		std::cout << "window close" << std::endl;
	});

    m_window_event_handler.AddHandler<GLFWwindow*, int, int>(TransactionType::WindowResize, [](GLFWwindow* window, int width, int height) {});

    // m_window_event_handler.AddHandler<>(TransactionType::WindowFocus, []() {});

    // m_window_event_handler.AddHandler<>(TransactionType::WindowLostFocus, []() {});

    // m_window_event_handler.AddHandler<>(TransactionType::WindowMoved, []() {});

    // m_window_event_handler.AddHandler<>(TransactionType::KeyPressed, []() {});

    // m_window_event_handler.AddHandler<>(TransactionType::KeyReleased, []() {});

    // m_window_event_handler.AddHandler<>(TransactionType::KeyTyped, []() {});

    // m_window_event_handler.AddHandler<>(TransactionType::MouseButtonPressed, []() {});

    // m_window_event_handler.AddHandler<>(TransactionType::MouseButtonReleased, []() {});

    // m_window_event_handler.AddHandler<>(TransactionType::MouseMoved, []() {});

    // m_window_event_handler.AddHandler<>(TransactionType::MouseScrolled, []() {});
}

} // namespace RendererDemo
