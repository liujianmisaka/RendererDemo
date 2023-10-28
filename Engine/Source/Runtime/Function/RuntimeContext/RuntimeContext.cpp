#include "Runtime/Function/RuntimeContext/RuntimeContext.hpp"

#include <memory>
#include "GLFW/glfw3.h"
#include "Runtime/Core/Log/LogSystem.hpp"
#include "Runtime/Function/Framework/Manager/GameWorldManager.hpp"
#include "Runtime/Function/Renderer/System/RendererSystem.hpp"
#include "Runtime/Function/Renderer/System/WindowSystem.hpp"

namespace RendererDemo {

RuntimeContext g_runtime_context;

void RuntimeContext::StartSystem() {
    m_log_system = std::make_shared<LogSystem>();

    m_game_world_manager = std::make_shared<GameWorldManager>();
    m_game_world_manager->Initialize();

    m_renderer_system = std::make_shared<RendererSystem>();
    m_renderer_system->Initialize();

    m_window_system = std::make_shared<WindowSystem>();
    m_window_system->Initialize();

    m_window_system->AddTransactionHandler<TransactionType::WindowClose>([](GLFWwindow* window) { std::cout << "window close" << std::endl; });
    m_window_system->AddTransactionHandler<TransactionType::WindowResize>(
        [](GLFWwindow* window, int width, int height) { std::cout << "window resize" << std::endl; });
    m_window_system->AddTransactionHandler<TransactionType::KeyPressed>([](GLFWwindow* window, int key, int scancode, int action, int mods) {
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
        [](GLFWwindow* window, int key, int scancode, int action, int mods) { std::cout << "key repeated" << std::endl; });
}

void RuntimeContext::ShutdownSystem() {
    m_window_system->Clear();
    m_window_system.reset();

    m_renderer_system->Clear();
    m_renderer_system.reset();

    m_game_world_manager->Clear();
    m_game_world_manager.reset();

    m_log_system.reset();
}

} // namespace RendererDemo
