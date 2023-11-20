#pragma once

#include <memory>

namespace RendererDemo {

class LogSystem;
class GameWorldManager;
class RendererSystem;
class WindowSystem;
class EventSystem;
class AssetManager;

struct EventStatus;

class RuntimeContext {
public:
    void StartSystem();
    void ShutdownSystem();

public:
    std::shared_ptr<LogSystem> m_log_system;
    std::shared_ptr<GameWorldManager> m_game_world_manager;
    std::shared_ptr<RendererSystem> m_renderer_system;
    std::shared_ptr<WindowSystem> m_window_system;
    std::shared_ptr<EventSystem> m_event_system;
    std::shared_ptr<AssetManager> m_asset_manager;
};

extern RuntimeContext g_runtime_context;
} // namespace RendererDemo
