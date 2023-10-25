#pragma once

#include <memory>
#include <string>
#include <unordered_map>

namespace RendererDemo {

class Scene;

class GameWorldManager {
public:
    ~GameWorldManager() = default;

    void Initialize();
    void Clear();

    void Tick(float ts);

private:
    std::shared_ptr<Scene> m_current_active_scene;
    std::unordered_map<std::string, std::shared_ptr<Scene>> m_scenes;
};

} // namespace RendererDemo
