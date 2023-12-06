#include "Runtime/Engine.hpp"
#include <iostream>

namespace RendererDemo {

void MisakaEngine::StartEngine() {
    m_runtime_context.StartSystem();
    std::cout << "engine start!" << std::endl;
}

void MisakaEngine::ShutdownEngine() {
    m_runtime_context.ShutdownSystem();
    std::cout << "engine close!" << std::endl;
}

bool MisakaEngine::Run() {
    float timestep = 0; // TODO: Get timestep from window system
    m_runtime_context.m_event_system->Tick();
    m_runtime_context.m_game_world_manager->Tick(timestep);

    // TODO: Swap render data before render
    m_runtime_context.m_renderer_system->Tick(timestep);
    m_runtime_context.m_window_system->Tick();

    bool is_running = !m_runtime_context.m_window_system->ShouldClose();
    return is_running;
}

} // namespace RendererDemo
