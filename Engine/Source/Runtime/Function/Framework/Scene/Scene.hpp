#pragma once

#include <entt/entity/fwd.hpp>
#include <entt/entt.hpp>
#include <memory>
#include <string>
#include "Runtime/Core/UUID/UUID.hpp"
#include "Runtime/Function/Framework/Component/Camera/CameraComponent.hpp"
#include "Runtime/Function/Framework/Object/Object.hpp"

namespace RendererDemo {

class Scene {
public:
    Scene() {
        m_registry = std::make_shared<entt::registry>();
        m_scene_camera = AddObject();
        m_scene_camera.AddComponent<CameraComponent>();
    }

    ~Scene() = default;

    void Tick(float ts);

    std::shared_ptr<entt::registry> GetRegister() { return m_registry; }

public:
    // The Object does not have resource, while the entt::entity has. So it does not make sense to return Object&.
    Object AddObject(UUID uuid = {}, std::string name = "Object");
    Object GetObject(entt::entity entity);
    Object& GetSelectedObject() { return m_selected_object; }
    void DestroyObject(Object object);

    template <typename... Components>
    auto GetAllObjectWith() {
        return m_registry->view<Components...>();
    }

    // Functions about camera
    Object& GetSceneCamera() { return m_scene_camera; }

private:
    std::shared_ptr<entt::registry> m_registry = nullptr;
    Object m_selected_object{};
    Object m_scene_camera{};

    friend class SceneHierarchyPanel;
};

} // namespace RendererDemo
