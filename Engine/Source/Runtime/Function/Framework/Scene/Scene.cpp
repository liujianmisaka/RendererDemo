#include "Runtime/Function/Framework/Scene/Scene.hpp"
#include <entt/entity/fwd.hpp>
#include "Runtime/Function/Framework/Component/Mesh/MeshComponent.hpp"
#include "Runtime/Function/Framework/Component/Render/IndexDrawBufferComponent.hpp"
#include "Runtime/Function/Framework/Component/State/StateComponent.hpp"
#include "Runtime/Function/Framework/Component/Transform/TransformComponent.hpp"

namespace RendererDemo {

void Scene::Tick(float ts) {
    {
        // First call component Tick
        auto view = m_registry->view<TransformComponent>();
        for (auto entity : view) {
            auto objct = GetObject(entity);
            objct.GetComponent<TransformComponent>().Tick(ts);
            auto& model_matrix = objct.GetComponent<TransformComponent>().GetModelMatrix();
        }
    }

    {
        // Create IndexDrawBufferComponent of MeshComponent
        auto view = m_registry->view<MeshComponent>();
        for (auto entity : view) {
            auto object = GetObject(entity);
            if (!object.HasComponent<IndexDrawBufferComponent>() &&
                object.GetComponent<StateComponent>().IsRendereable()) {
                auto& draw_component = object.AddComponent<IndexDrawBufferComponent>();
                auto& mesh_component = object.GetComponent<MeshComponent>();
                draw_component.GenerateIndexDrawBuffer(mesh_component);
            }
        }
    }

    {
        // Create IndexDrawBufferComponent of SquaComponent
        auto view = m_registry->view<SquaComponent>();
        for (auto entity : view) {
            auto object = GetObject(entity);
            if (!object.HasComponent<IndexDrawBufferComponent>() &&
                object.GetComponent<StateComponent>().IsRendereable()) {
                auto& draw_component = object.AddComponent<IndexDrawBufferComponent>();
                auto& squa_component = object.GetComponent<SquaComponent>();
                draw_component.GenerateIndexDrawBuffer(squa_component);
            }
        }
    }

    {
        // Create UniformBufferComponent of TransformComponent
    }
}

Object Scene::CreateObject(UUID uuid, std::string name) {
    entt::entity entity = m_registry->create();
    m_registry->emplace<IdComponent>(entity, uuid);
    m_registry->emplace<TagComponent>(entity, name);
    m_registry->emplace<StateComponent>(entity, ObjectState::KRendereable);
    m_selected_object = Object{entity, m_registry};
    return Object{entity, m_registry};
}

Object Scene::GetObject(entt::entity entity) { return Object{entity, m_registry}; }

void Scene::DestroyObject(Object object) {
    entt::entity entity = static_cast<entt::entity>(object);
    m_registry->destroy(entity);
}

} // namespace RendererDemo
