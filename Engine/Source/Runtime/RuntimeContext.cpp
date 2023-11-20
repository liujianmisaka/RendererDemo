#include "Runtime/RuntimeContext.hpp"

#include <memory>
#include "Runtime/Core/Log/LogSystem.hpp"
#include "Runtime/Function/Framework/Manager/GameWorldManager.hpp"
#include "Runtime/Function/Renderer/RenderSystem.hpp"
#include "Runtime/Function/Window/WindowSystem.hpp"
#include "Runtime/Function/event/EventSystem.hpp"
#include "Runtime/Resource/Manager/AssetManager.hpp"

namespace RendererDemo {

RuntimeContext g_runtime_context;

void RuntimeContext::StartSystem() {
    m_log_system = std::make_shared<LogSystem>();
    m_game_world_manager = std::make_shared<GameWorldManager>();
    m_window_system = std::make_shared<WindowSystem>();
    m_renderer_system = std::make_shared<RendererSystem>();
    m_event_system = std::make_shared<EventSystem>();
    m_asset_manager = std::make_shared<AssetManager>();

    m_game_world_manager->Initialize();

    m_window_system->Initialize();

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
