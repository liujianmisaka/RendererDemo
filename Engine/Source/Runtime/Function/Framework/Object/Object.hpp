#pragma once

#include <cassert>
#include <entt/entity/fwd.hpp>
#include <entt/entt.hpp>

namespace RendererDemo {

class Scene;

class Object {
public:
    Object() = default;
    Object(entt::entity entity, std::shared_ptr<entt::registry> entt_register)
        : m_entity(entity), m_registry(entt_register) {}
    Object(entt::entity entity, std::shared_ptr<Scene> scene);
    virtual ~Object() = default;

    explicit operator bool() const { return m_entity != entt::null; }
    explicit operator entt::entity() const { return m_entity; }
    explicit operator uint32_t() const { return static_cast<uint32_t>(m_entity); }

    // bool operator==(const Object& other) const { return m_entity == other.m_entity; }
    // bool operator!=(const Object& other) const { return !(*this == other); }

public:
    template <typename T, typename... Args>
    T& AddComponent(Args&&... args) {
        assert(!HasComponent<T>());
        T& component = m_registry->emplace<T>(m_entity, std::forward<Args>(args)...);
        this->OnComponentAdded<T>(*this, component);
        return component;
    }

    template <typename T, typename... Args>
    T& AddOrReplaceComponent(Args&&... args) {
        T& component = m_registry->emplace_or_replace<T>(m_entity, std::forward<Args>(args)...);
        this->OnComponentAdded<T>(*this, component);
        return component;
    }

    template <typename T>
    T& GetComponent() {
        assert(HasComponent<T>());
        return m_registry->get<T>(m_entity);
    }

    template <typename T>
    bool HasComponent() {
        return m_registry->all_of<T>(m_entity);
    }

    template <typename T>
    void RemoveComponent() {
        assert(HasComponent<T>());
        m_registry->remove<T>(m_entity);
    }

private:
    template <typename T>
    void OnComponentAdded(Object object, T& component) {}

private:
    entt::entity m_entity{entt::null};
    std::shared_ptr<entt::registry> m_registry;
};

} // namespace RendererDemo
