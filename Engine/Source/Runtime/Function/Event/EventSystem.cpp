#include "Runtime/Function/Event/EventSystem.hpp"

namespace RendererDemo {

void EventSystem::Initialize(std::shared_ptr<WindowSystem> window_system) {
    m_window_system = window_system;
    AddHandlers();
}

void EventSystem::Clear() {
}

void EventSystem::AddHandlers() {
    /* -------------------------------------------------------------------------- */
    /*                             Default GLFW Event                             */
    /* -------------------------------------------------------------------------- */
    m_window_system->AddTransactionHandler<TransactionType::WindowClose>(
        [](GLFWwindow* window) { std::cout << "window close" << std::endl; });
    m_window_system->AddTransactionHandler<TransactionType::WindowResize>(
        [](GLFWwindow* window, int width, int height) { std::cout << "window resize" << std::endl; });
    m_window_system->AddTransactionHandler<TransactionType::KeyPressed>(
        [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            if (key == GLFW_KEY_LEFT_SHIFT || key == GLFW_KEY_RIGHT_SHIFT) {
                return;
            }
            if (key == GLFW_KEY_LEFT_CONTROL || key == GLFW_KEY_RIGHT_CONTROL) {
                return;
            }
            if (key == GLFW_KEY_LEFT_ALT || key == GLFW_KEY_RIGHT_ALT) {
                return;
            }
            const char* keyName = glfwGetKeyName(key, scancode);
            std::cout << keyName << std::endl;
        });
    m_window_system->AddTransactionHandler<TransactionType::KeyRepeated>(
        [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            std::cout << "key repeated" << std::endl;
        });
}

} // namespace RendererDemo
