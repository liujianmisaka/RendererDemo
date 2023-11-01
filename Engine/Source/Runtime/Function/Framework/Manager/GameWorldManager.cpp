#include "Runtime/Function/Framework/Manager/GameWorldManager.hpp"
#include "Runtime/Function/Framework/Scene/Scene.hpp"

namespace RendererDemo {

void GameWorldManager::Initialize() {}

void GameWorldManager::Clear() {}

void GameWorldManager::Tick(float ts) {
    if (m_current_active_scene) {
        m_current_active_scene->Tick(ts);
    }
}

} // namespace RendererDemo
