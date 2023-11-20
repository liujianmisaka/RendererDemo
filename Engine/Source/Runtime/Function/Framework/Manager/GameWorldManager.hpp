#pragma once

#include <memory>
#include "Runtime/Function/Framework/Scene/Scene.hpp"

namespace RendererDemo {

class Scene;
class OpenGLRHI;

class GameWorldManager {
    friend class RendererDemo::OpenGLRHI;

public:
    GameWorldManager() = default;
    ~GameWorldManager() = default;

    void Initialize();
    void Clear();

    void Tick(float ts);

    std::shared_ptr<Scene> GetCurrentActivateScene() { return m_current_active_scene; }

private:
    std::shared_ptr<Scene> m_current_active_scene = nullptr;
};

} // namespace RendererDemo
