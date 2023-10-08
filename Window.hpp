#pragma once

#include <string>

#include <GLFW/glfw3.h>

namespace RendererDemo {

struct WindowProps {
    int width = 1280;
    int height = 960;
    std::string title = "RendererDemo";
};

class Window {
public:
    Window(WindowProps prop);
    ~Window();


private:
    GLFWwindow* m_GLFWWindow;
};

}