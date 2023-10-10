#pragma once

#include <GLFW/glfw3.h>

namespace RendererDemo {

class Window {
public:
    Window();
    ~Window();

    void run();
    
private:
    GLFWwindow* m_GLFWWindow;
};

}