#include "Runtime/Function/Framework/Scene/Scene.hpp"
#include <entt/entity/fwd.hpp>
#include "Runtime/Function/Framework/Component/Mesh/MeshComponent.hpp"
#include "Runtime/Function/Framework/Component/Render/IndexDrawBufferComponent.hpp"
#include "Runtime/Function/Framework/Component/Render/UniformBufferComponent.hpp"
#include "Runtime/Function/Framework/Component/State/StateComponent.hpp"
#include "Runtime/Function/Framework/Component/Transform/TransformComponent.hpp"

namespace RendererDemo {

void Scene::Tick(float ts) {
    m_scene_camera.Tick(ts);

    {
        // First call component Tick
        auto view = m_registry->view<TransformComponent>();
        for (auto entity : view) {
            auto objct = GetObject(entity);
            objct.GetComponent<TransformComponent>().Tick(ts);
        }
    }

    {
        // Create IndexDrawBufferComponent if has MeshComponent but don't have IndexDrawBufferComponent
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
        // Set MVP for UniformBufferComponent
        auto view = m_registry->view<TransformComponent>();
        for (auto entity : view) {
            auto object = GetObject(entity);
            auto& uniform_buffer_component = object.AddComponentNotReplace<UniformBufferComponent>();
            auto& transform_component = object.GetComponent<TransformComponent>();
            MVP mvp;
            mvp.model = transform_component.GetModelMatrix();
            mvp.view = m_scene_camera.GetViewProjection();
            mvp.projection = m_scene_camera.GetProjection();
            uniform_buffer_component.SetMVP(mvp);
        }
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

SceneCamera Scene::CreateSceneCamera(UUID uuid, std::string name) {
    entt::entity entity = m_registry->create();
    m_registry->emplace<IdComponent>(entity, uuid);
    m_registry->emplace<TagComponent>(entity, name);
    m_registry->emplace<CameraComponent>(entity);
    return SceneCamera{entity, m_registry};
}

} // namespace RendererDemo
