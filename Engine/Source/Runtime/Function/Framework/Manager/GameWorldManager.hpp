#pragma once

#include <memory>
#include "Runtime/Function/Framework/Scene/Scene.hpp"
#include "Runtime/Function/Window/WindowSystem.hpp"

namespace RendererDemo {

class Scene;
class OpenGLRHI;

struct GameWorldManagerInitInfo {
    std::shared_ptr<WindowSystem> m_window_system;
};

class GameWorldManager {
    friend class RendererDemo::OpenGLRHI;

public:
    GameWorldManager() = default;
    ~GameWorldManager() = default;

    void Initialize(GameWorldManagerInitInfo init_info);
    void Clear();

    void Tick(float ts);

    std::shared_ptr<Scene> GetCurrentActivateScene() { return m_current_active_scene; }

private:
    std::shared_ptr<Scene> m_current_active_scene = nullptr;
    std::shared_ptr<WindowSystem> m_window_system = nullptr;
};

} // namespace RendererDemo
