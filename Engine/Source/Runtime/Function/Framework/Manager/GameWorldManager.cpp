#include "Runtime/Function/Framework/Manager/GameWorldManager.hpp"
#include "Runtime/Function/Framework/Scene/Scene.hpp"

namespace RendererDemo {

void GameWorldManager::Initialize(GameWorldManagerInitInfo init_info) {
    m_window_system = init_info.m_window_system;
    m_current_active_scene = std::make_shared<Scene>();
}

void GameWorldManager::Clear() {}

void GameWorldManager::Tick(float ts) { m_current_active_scene->Tick(ts); }

} // namespace RendererDemo
