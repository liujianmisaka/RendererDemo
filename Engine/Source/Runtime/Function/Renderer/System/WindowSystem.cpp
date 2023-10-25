#include "Runtime/Function/Renderer/System/WindowSystem.hpp"
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

    glfwMakeContextCurrent(m_GLFWWindow);

    // TODO: set input callbacks
    glfwSetFramebufferSizeCallback(m_GLFWWindow, windowResizeCallback);
}

void WindowSystem::Clear() {
    glfwDestroyWindow(m_GLFWWindow);
    glfwTerminate();
}

bool WindowSystem::ShouldClose() const { return glfwWindowShouldClose(m_GLFWWindow); }

void WindowSystem::PollEvents() const { glfwPollEvents(); }

void WindowSystem::SwapBuffers() const { glfwSwapBuffers(m_GLFWWindow); }

GLFWwindow* WindowSystem::GetNativeWindow() const { return m_GLFWWindow; }

} // namespace RendererDemo
