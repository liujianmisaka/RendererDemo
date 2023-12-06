#pragma once

#include <entt/entity/fwd.hpp>
#include <entt/entt.hpp>
#include <memory>
#include <string>
#include "Runtime/Core/UUID/UUID.hpp"
#include "Runtime/Function/Framework/Object/Object.hpp"
#include "Runtime/Function/Framework/Object/SceneCamera.hpp"

namespace RendererDemo {

class Scene {
public:
    Scene() = default;
    ~Scene() = default;

    void Tick(float ts);

    std::shared_ptr<entt::registry> GetRegister() { return m_registry; }

public:
    // Functions about object
    Object CreateObject(UUID uuid = {}, std::string name = "Object");
    Object GetObject(entt::entity entity);
    Object& GetSelectedObject() { return m_selected_object; }
    void DestroyObject(Object object);

    template <typename... Components>
    auto GetAllObjectWith() {
        return m_registry->view<Components...>();
    }

public:
    // Functions about scene camera
    SceneCamera CreateSceneCamera(UUID uuid = {}, std::string name = "SceneCamera");
    SceneCamera& GetSceneCamera() { return m_scene_camera; }

private:
    std::shared_ptr<entt::registry> m_registry = std::make_shared<entt::registry>();
    Object m_selected_object{};

    SceneCamera m_scene_camera = CreateSceneCamera();

    friend class SceneHierarchyPanel;
};

} // namespace RendererDemo
