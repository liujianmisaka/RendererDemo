#pragma once
#include "Runtime/Core/IWindow.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace RendererDemo {

class Window : public IWindow {
public:
    Window() = default;
    virtual ~Window() = default;

    virtual void Create() override;
    virtual void Destroy() override;

    virtual bool ShouldClose() const override { return glfwWindowShouldClose(m_GLFWWindow); }
	virtual void SetEventCallback() override;
    virtual void OnUpdate() override;

    void* GetNativeWindow() const { return m_GLFWWindow; }

private:
    static void windowResizeCallback(GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); }

private:
    GLFWwindow* m_GLFWWindow;
};

} // namespace RendererDemo
