#pragma once
#include <GLFW/glfw3.h>
// #include <glad/glad.h>
#include <iostream>
#include <string>
#include <iostream>

#include "Runtime/Core/Handler/TransactionHandler.hpp"

namespace RendererDemo {

struct WindowDelegateData {
    Delegate<GLFWwindow*> m_window_close_delegate;
    Delegate<GLFWwindow*, int, int> m_window_resize_delegate;
    // Delegate<GLFWwindow*, int, int> m_window_focus_delegate;
    // Delegate<GLFWwindow*, int, int> m_window_lost_focus_delegate;
    // Delegate<GLFWwindow*, int, int> m_window_moved_delegate;
    Delegate<GLFWwindow*, int, int, int, int> m_key_pressed_delegate;
    Delegate<GLFWwindow*, int, int, int, int> m_key_released_delegate;
    Delegate<GLFWwindow*, int, int, int, int> m_key_repeated_delegate;
    Delegate<GLFWwindow*, int> m_key_typed_delegate;
    Delegate<GLFWwindow*, int, int, int> m_mouse_button_pressed_delegate;
    Delegate<GLFWwindow*, int, int, int> m_mouse_button_released_delegate;
    Delegate<GLFWwindow*, double, double> m_mouse_scrolled_delegate;
    Delegate<GLFWwindow*, double, double> m_mouse_moved_delegate;
};

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
    WindowDelegateData& GetWindowDelegateData();

private:
    void SetGLFWCallbacks();

private:
    GLFWwindow* m_GLFWWindow;
    int m_width = 0;
    int m_height = 0;
    std::string m_title = "Misaka Engine";

    WindowDelegateData m_window_delegate_data;

public:
    template <TransactionType T, typename FuncType>
    void AddTransactionHandler(FuncType function) {
        if constexpr (T == TransactionType::WindowClose) {
            m_window_delegate_data.m_window_close_delegate.Add(function);
        } else if constexpr (T == TransactionType::WindowResize) {
            m_window_delegate_data.m_window_resize_delegate.Add(function);
        } else if constexpr (T == TransactionType::KeyPressed) {
            m_window_delegate_data.m_key_pressed_delegate.Add(function);
        } else if constexpr (T == TransactionType::KeyReleased) {
            m_window_delegate_data.m_key_released_delegate.Add(function);
        } else if constexpr (T == TransactionType::KeyRepeated) {
            m_window_delegate_data.m_key_repeated_delegate.Add(function);
        } else if constexpr (T == TransactionType::KeyTyped) {
            m_window_delegate_data.m_key_typed_delegate.Add(function);
        } else if constexpr (T == TransactionType::MouseButtonPressed) {
            m_window_delegate_data.m_mouse_button_pressed_delegate.Add(function);
        } else if constexpr (T == TransactionType::MouseButtonPressed) {
            m_window_delegate_data.m_mouse_button_released_delegate.Add(function);
        } else if constexpr (T == TransactionType::MouseScrolled) {
            m_window_delegate_data.m_mouse_scrolled_delegate.Add(function);
        } else if constexpr (T == TransactionType::MouseMoved) {
            m_window_delegate_data.m_mouse_moved_delegate.Add(function);
        }
    }

private:
    // -----------------------------------
    // NOTE: GLFW callback functions
    // -----------------------------------

    static void errorCallback(int error, const char* description) { std::cerr << "GLFW Error " << error << ": " << description << std::endl; }

    static void WindowCloseCallback(GLFWwindow* window) {
        WindowSystem* system = static_cast<WindowSystem*>(glfwGetWindowUserPointer(window));
        system->m_window_delegate_data.m_window_close_delegate.Broadcast(window);
        glfwSetWindowShouldClose(window, true);
    }

    static void WindowResizeCallback(GLFWwindow* window, int width, int height) {
        WindowSystem* system = static_cast<WindowSystem*>(glfwGetWindowUserPointer(window));
        system->m_window_delegate_data.m_window_resize_delegate.Broadcast(window, width, height);
    }

    // static void WindowFocusCallback(GLFWwindow* window, int width, int height) {
    //     WindowSystem* system = static_cast<WindowSystem*>(glfwGetWindowUserPointer(window));
    //     system->m_window_delegate_data.m_window_focus_delegate.Broadcast(window, width, height);
    // }

    // static void WindowLostFocusCallback(GLFWwindow* window, int width, int height) {
    //     WindowSystem* system = static_cast<WindowSystem*>(glfwGetWindowUserPointer(window));
    //     system->m_window_delegate_data.m_window_lost_focus_delegate.Broadcast(window, width, height);
    // }

    // static void WindowMovedCallback(GLFWwindow* window, int width, int height) {
    //     WindowSystem* system = static_cast<WindowSystem*>(glfwGetWindowUserPointer(window));
    //     system->m_window_delegate_data.m_window_moved_delegate.Broadcast(window, width, height);
    // }

    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        std::cout << "key pressed" << std::endl;
        WindowSystem* system = static_cast<WindowSystem*>(glfwGetWindowUserPointer(window));
        switch (action) {
            case GLFW_PRESS: {
                system->m_window_delegate_data.m_key_pressed_delegate.Broadcast(window, key, scancode, action, mods);
                break;
            }
            case GLFW_RELEASE: {
                system->m_window_delegate_data.m_key_released_delegate.Broadcast(window, key, scancode, action, mods);
                break;
            }
            case GLFW_REPEAT: {
                system->m_window_delegate_data.m_key_repeated_delegate.Broadcast(window, key, scancode, action, mods);
                break;
            }
            default: {
                // TODO: change to log system
                std::cerr << "No such GLFE key action" << std::endl;
            }
        }
    }

    static void KeyTypedCallbackCallback(GLFWwindow* window, unsigned int keycode) {
        WindowSystem* system = static_cast<WindowSystem*>(glfwGetWindowUserPointer(window));
        system->m_window_delegate_data.m_key_typed_delegate.Broadcast(window, keycode);
    }

    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
        WindowSystem* system = static_cast<WindowSystem*>(glfwGetWindowUserPointer(window));
        switch (action) {
            case GLFW_PRESS: {
                system->m_window_delegate_data.m_mouse_button_pressed_delegate.Broadcast(window, button, action, mods);
                break;
            }
            case GLFW_RELEASE: {
                system->m_window_delegate_data.m_mouse_button_released_delegate.Broadcast(window, button, action, mods);
                break;
            }
            default: {
                // TODO: change to log system
                std::cerr << "No such GLFE mosue button action" << std::endl;
            }
        }
    }

    static void MouseScrolledCallback(GLFWwindow* window, double xOffset, double yOffset) {
        WindowSystem* system = static_cast<WindowSystem*>(glfwGetWindowUserPointer(window));
        system->m_window_delegate_data.m_mouse_scrolled_delegate.Broadcast(window, xOffset, yOffset);
    }

    static void MouseMovedCallback(GLFWwindow* window, double xPos, double yPos) {
        WindowSystem* system = static_cast<WindowSystem*>(glfwGetWindowUserPointer(window));
        system->m_window_delegate_data.m_mouse_moved_delegate.Broadcast(window, xPos, yPos);
    }
};

} // namespace RendererDemo
