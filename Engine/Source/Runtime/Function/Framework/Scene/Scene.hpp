#pragma once

#include <entt/entity/fwd.hpp>
#include <entt/entt.hpp>
#include <memory>
#include <string>
#include "Runtime/Core/UUID/UUID.hpp"
#include "Runtime/Function/Framework/Component/Camera/CameraComponent.hpp"
#include "Runtime/Function/Framework/Component/Component.hpp"
#include "Runtime/Function/Framework/Component/Transform/TransformComponent.hpp"
#include "Runtime/Function/Framework/Object/Object.hpp"
#include "Runtime/Function/Framework/Object/SceneCamera.hpp"

namespace RendererDemo {

class Object;

class Scene {
public:
    Scene() = default;
    ~Scene() = default;

    void Tick(float ts) {}

    std::shared_ptr<entt::registry> GetRegister() { return m_registry; }

    Object CreateObject(UUID uuid = {}, std::string name = "Object") {
        entt::entity entity = m_registry->create();
        m_registry->emplace<IdComponent>(entity, uuid);
        m_registry->emplace<TagComponent>(entity, name);
        return Object{entity, m_registry};
    }

    SceneCamera CreateSceneCamera(UUID uuid = {}, std::string name = "SceneCamera") {
        entt::entity entity = m_registry->create();
        m_registry->emplace<IdComponent>(entity, uuid);
        m_registry->emplace<TagComponent>(entity, name);
        m_registry->emplace<CameraComponent>(entity);
        m_registry->emplace<TransformComponent>(entity);
        return SceneCamera{entity, m_registry};
    }

    void DestroyObject(Object object) {
        entt::entity entity = static_cast<entt::entity>(object);
        m_registry->destroy(entity);
    }

    template <typename... Components>
    auto GetAllObjectWith() {
        return m_registry->view<Components...>();
    }

    glm::mat4 GetViewProjection() {
        CameraComponent& camera_component = m_scene_camera.GetComponent<CameraComponent>();
        return camera_component.GetViewProjection();
    }

    glm::mat4 GetViewMatrix() {
        CameraComponent& camera_component = m_scene_camera.GetComponent<CameraComponent>();
        return camera_component.GetViewMatrix();
    }

    glm::mat4 GetProjectionMatrix() {
        CameraComponent& camera_component = m_scene_camera.GetComponent<CameraComponent>();
        return camera_component.GetProjectionMatrix();
    }

    glm::mat4 GetModelMatrix() {
        TransformComponent& transform_component = m_scene_camera.GetComponent<TransformComponent>();
        return transform_component.GetModelMatrix();
    }

    glm::vec3& GetRotation() {
        TransformComponent& transform_component = m_scene_camera.GetComponent<TransformComponent>();
        return transform_component.GetRotation();
    }

private:
    std::shared_ptr<entt::registry> m_registry = std::make_shared<entt::registry>();
    Object m_selected_object{};

    SceneCamera m_scene_camera = CreateSceneCamera();

    friend class SceneHierarchyPanel;
};

} // namespace RendererDemo
