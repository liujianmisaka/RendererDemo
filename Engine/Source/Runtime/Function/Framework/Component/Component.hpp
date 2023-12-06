#pragma once

#include <entt/entity/fwd.hpp>
#include <memory>
#include <entt/entt.hpp>

namespace RendererDemo {

class Component {
public:
    Component(std::shared_ptr<entt::registry> registry, entt::entity entity) : m_registry(registry), m_entity(entity) {}
    virtual ~Component() = default;

    virtual void Tick(float ts) {}

    void SetDirty(bool dirty) { m_dirty = dirty; }
    bool IsDirty() { return m_dirty; }

protected:
    template <typename T>
    T &ObjectAddComponent() {
        assert(!ObjectHasComponent<T>());
        T &component = m_registry->emplace<T>(m_entity, m_registry, m_entity);
        return component;
    }

    template <typename T>
    T &ObjectGetComponent() {
        return m_registry->get<T>(m_entity);
    }

    template <typename T>
    bool ObjectHasComponent() {
        return m_registry->all_of<T>(m_entity);
    }

    std::shared_ptr<entt::registry> m_registry = nullptr;
    entt::entity m_entity = entt::null;
    bool m_dirty = false;
};

} // namespace RendererDemo
