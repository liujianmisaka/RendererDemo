#pragma once

#include <string>

#include <GLFW/glfw3.h>

namespace RendererDemo {

struct WindowProps {
    int width = 1280;
    int height = 960;
    std::string title = "RendererDemo Window";
};

class Window {
public:
    Window(WindowProps prop = WindowProps{});
    ~Window();

    void run();

private:
    GLFWwindow* m_GLFWWindow;
};

}