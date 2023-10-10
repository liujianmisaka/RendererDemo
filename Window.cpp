#include "Window.hpp"

#include "Log.hpp"
#include <GLFW/glfw3.h>

namespace RendererDemo {

Window::Window(WindowProps prop) {

    if(!glfwInit()) {
        LOGGER_CORE_ERROR("Failed to init GLFW!");
        exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    m_GLFWWindow = glfwCreateWindow(prop.width, prop.height, prop.title.c_str(), nullptr, nullptr);

    if(!m_GLFWWindow) {
        LOGGER_CORE_ERROR("Failed to create GLFW window!");
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(m_GLFWWindow);
}

Window::~Window() {
    glfwDestroyWindow(m_GLFWWindow);
    glfwTerminate();
}

void Window::run() {
    while(!glfwWindowShouldClose(m_GLFWWindow)) {
        // Render here

        // 交换缓冲区与处理事件
        glfwSwapBuffers(m_GLFWWindow);
        glfwPollEvents();
    }
}

}