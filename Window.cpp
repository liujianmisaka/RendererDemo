#include "Window.hpp"
#include <cstdlib>

namespace RendererDemo {

Window::Window(WindowProps prop) {

    if(!glfwInit()) {
        exit(-1);
    }
    
    m_GLFWWindow = glfwCreateWindow(prop.width, prop.height, prop.title.c_str(), nullptr, nullptr);

    if(!m_GLFWWindow) {

    }
}

}