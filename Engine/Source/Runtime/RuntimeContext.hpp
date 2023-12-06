#pragma once

#include <memory>
#include "Runtime/Core/Log/LogSystem.hpp"
#include "Runtime/Function/Framework/Manager/GameWorldManager.hpp"
#include "Runtime/Function/Renderer/RenderSystem.hpp"
#include "Runtime/Function/Window/WindowSystem.hpp"
#include "Runtime/Function/event/EventSystem.hpp"
#include "Runtime/Resource/Manager/AssetManager.hpp"

namespace RendererDemo {

class RuntimeContext {
public:
    RuntimeContext();
    ~RuntimeContext() = default;

    void StartSystem();
    void ShutdownSystem();

private:
    std::shared_ptr<LogSystem> m_log_system;
    std::shared_ptr<GameWorldManager> m_game_world_manager;
    std::shared_ptr<RendererSystem> m_renderer_system;
    std::shared_ptr<WindowSystem> m_window_system;
    std::shared_ptr<EventSystem> m_event_system;
    std::shared_ptr<AssetManager> m_asset_manager;

    friend class MisakaEngine;
    friend class EditorContext;
};

} // namespace RendererDemo
