#pragma once

#include <cassert>
#include <entt/entt.hpp>
#include <string>
#include "Runtime/Core/UUID/UUID.hpp"
#include "Runtime/Function/Framework/Component/Component.hpp"
#include "Runtime/Function/Framework/Object/Object.hpp"

namespace RendererDemo {

class Object;

class Scene {
public:
    Scene() = default;
    ~Scene() = default;

    void Tick(float ts) {}

    Object CreateObject(UUID uuid = {}, std::string name = "Object") {
        entt::entity entity = m_registry.create();
        m_registry.emplace<IdComponent>(entity, uuid);
        m_registry.emplace<TagComponent>(entity, name);
        return Object{entity};
    }

    void DestroyObject(Object object) {
        entt::entity entity = static_cast<entt::entity>(object);
        m_registry.destroy(entity);
    }

    template <typename T, typename... Args>
    T& AddComponent(Object object, Args&&... args) {
        assert(!HasComponent<T>(object));
        entt::entity entity = static_cast<entt::entity>(object);
        T& component = m_registry.emplace<T>(entity, std::forward<Args>(args)...);
        return component;
    }

    template <typename T, typename... Args>
    T& AddOrReplaceComponent(Object object, Args&&... args) {
        entt::entity entity = static_cast<entt::entity>(object);
        T& component = m_registry.emplace_or_replace<T>(entity, std::forward<Args>(args)...);
        return component;
    }

    template <typename T>
    T& GetComponent(Object object) {
        assert(HasComponent<T>(object));
        entt::entity entity = static_cast<entt::entity>(object);
        return m_registry.get<T>(entity);
    }

    template <typename T>
    bool HasComponent(Object object) {
        entt::entity entity = static_cast<entt::entity>(object);
        return m_registry.all_of<T>(entity);
    }

    template <typename T>
    void RemoveComponent(Object object) {
        assert(HasComponent<T>(object));
        entt::entity entity = static_cast<entt::entity>(object);
        m_registry.remove<T>(entity);
    }

    template <typename... Components>
    auto GetAllObjectWith() {
        return m_registry.view<Components...>();
    }

private:
    entt::registry m_registry;

    friend class Object;
};

} // namespace RendererDemo
