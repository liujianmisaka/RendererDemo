#include "Runtime/Function/RuntimeContext/RuntimeContext.hpp"

#include <memory>
#include "Runtime/Core/Log/LogSystem.hpp"
#include "Runtime/Function/Framework/Manager/GameWorldManager.hpp"
#include "Runtime/Function/Renderer/System/RenderSystem.hpp"
#include "Runtime/Function/Renderer/System/WindowSystem.hpp"

namespace RendererDemo {

RuntimeContext g_runtime_context;

void RuntimeContext::StartSystem() {
    m_log_system = std::make_shared<LogSystem>();

    m_game_world_manager = std::make_shared<GameWorldManager>();
    m_game_world_manager->Initialize();

    m_window_system = std::make_shared<WindowSystem>();
    m_window_system->Initialize();

    RendererSystemInitInfo render_system_init_info;
    render_system_init_info.window_system = m_window_system;
	render_system_init_info.graphics_api = GraphicsAPI::OpenGL;
    m_renderer_system = std::make_shared<RendererSystem>();
    m_renderer_system->Initialize(render_system_init_info);
}

void RuntimeContext::ShutdownSystem() {
    m_renderer_system->Clear();
    m_renderer_system.reset();

    m_window_system->Clear();
    m_window_system.reset();

    m_game_world_manager->Clear();
    m_game_world_manager.reset();

    m_log_system.reset();
}

} // namespace RendererDemo
