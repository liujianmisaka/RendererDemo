#include "Runtime/Function/Framework/Scene/Scene.hpp"
#include <entt/entity/fwd.hpp>
#include <memory>
#include "Runtime/Function/Framework/Component/MiniComponents.hpp"
#include "Runtime/Function/Framework/Component/State/StateComponent.hpp"
#include "Runtime/Function/Framework/Object/Object.hpp"

namespace RendererDemo {

void Scene::Tick(float ts) {
    for (auto entity : m_registry->view<entt::entity>()) {
        auto object = GetObject(entity);
        object.Tick(ts);
    }
}

Object Scene::AddObject(UUID uuid, std::string name) {
    entt::entity entity = m_registry->create();
    Object object = Object{entity, m_registry};
    object.AddComponent<IdComponent>();
    object.AddComponent<TagComponent>();
    object.AddComponent<StateComponent>(ObjectState::KRendereable);
    m_selected_object = Object{entity, m_registry};
    return Object{entity, m_registry};
}

Object Scene::GetObject(entt::entity entity) { return Object{entity, m_registry}; }

void Scene::DestroyObject(Object object) {
    entt::entity entity = static_cast<entt::entity>(object);
    m_registry->destroy(entity);
}

} // namespace RendererDemo
