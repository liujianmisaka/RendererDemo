#include "Runtime/Engine.hpp"
#include <iostream>

// #include "Runtime/Core/Base/macro.hpp"
#include "Runtime/Function/RuntimeContext/RuntimeContext.hpp"
// #include "Runtime/Core/Log/LogSystem.hpp"
#include "Runtime/Function/Framework/Manager/GameWorldManager.hpp"
#include "Runtime/Function/Renderer/System/RenderSystem.hpp"
#include "Runtime/Function/Renderer/System/WindowSystem.hpp"

namespace RendererDemo {

void MisakaEngine::StartEngine() {
    g_runtime_context.StartSystem();
    std::cout << "engine start!" << std::endl;
    // g_runtime_context.m_log_system->log(LogSystem::LogLevel::info, "engine start!");
}

void MisakaEngine::ShutdownEngine() {
    g_runtime_context.ShutdownSystem();
    std::cout << "engine close!" << std::endl;
    // LOG_INFO("Misaka Engine Shutdown!");
}

void MisakaEngine::Run() {
    while (!g_runtime_context.m_window_system->ShouldClose()) {
        float timestep = 0;
        g_runtime_context.m_game_world_manager->Tick(timestep);
        g_runtime_context.m_renderer_system->Tick(timestep);

		g_runtime_context.m_window_system->SwapBuffers();
		g_runtime_context.m_window_system->PollEvents();
    }
}

} // namespace RendererDemo
