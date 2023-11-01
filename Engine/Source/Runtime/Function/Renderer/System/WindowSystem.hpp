#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

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
    static void windowResizeCallback(GLFWwindow* window, int width, int height) { std::cout << "Window Resize: " << width << " " << height << std::endl; }

private:
    GLFWwindow* m_GLFWWindow;
    int m_width = 0;
    int m_height = 0;
    std::string m_title = "Misaka Engine";
};

} // namespace RendererDemo
