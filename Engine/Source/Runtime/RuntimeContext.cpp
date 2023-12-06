#include "Runtime/RuntimeContext.hpp"

namespace RendererDemo {

RuntimeContext::RuntimeContext() {
    m_log_system = std::make_shared<LogSystem>();
    m_game_world_manager = std::make_shared<GameWorldManager>();
    m_window_system = std::make_shared<WindowSystem>();
    m_renderer_system = std::make_shared<RendererSystem>();
    m_event_system = std::make_shared<EventSystem>();
    m_asset_manager = std::make_shared<AssetManager>();
}

void RuntimeContext::StartSystem() {
    m_window_system->Initialize();

    GameWorldManagerInitInfo game_world_manager_init_info;
    game_world_manager_init_info.m_window_system = m_window_system;
    m_game_world_manager->Initialize(game_world_manager_init_info);

    RendererSystemInitInfo render_system_init_info;
    render_system_init_info.graphics_api = GraphicsAPI::OpenGL;
    render_system_init_info.window_system = m_window_system;
    render_system_init_info.game_world_manager = m_game_world_manager;
    render_system_init_info.asset_manager = m_asset_manager;
    m_renderer_system->Initialize(render_system_init_info);

    m_event_system->Initialize(m_window_system);

    m_asset_manager->Initialize();
}

void RuntimeContext::ShutdownSystem() {
    m_asset_manager->Clear();
    m_asset_manager.reset();

    m_event_system->Clear();
    m_event_system.reset();

    m_renderer_system->Clear();
    m_renderer_system.reset();

    m_window_system->Clear();
    m_window_system.reset();

    m_game_world_manager->Clear();
    m_game_world_manager.reset();

    m_log_system.reset();
}

} // namespace RendererDemo
