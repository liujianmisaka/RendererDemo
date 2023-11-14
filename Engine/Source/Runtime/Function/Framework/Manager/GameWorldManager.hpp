#pragma once

#include <memory>
#include <string>
#include <unordered_map>

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

    void AddScene(std::string name, std::shared_ptr<Scene> scene) {
        m_scenes[name] = scene;
        if (m_current_active_scene == nullptr) {
            m_current_active_scene = scene;
        }
    }

    std::shared_ptr<Scene> GetActivateScene() {
        return m_current_active_scene;
    }

private:
    std::shared_ptr<Scene> m_current_active_scene = nullptr;
    std::unordered_map<std::string, std::shared_ptr<Scene>> m_scenes;
};

} // namespace RendererDemo
