#pragma once

#include <entt/entt.hpp>

namespace RendererDemo {

class Object {
public:
    Object() = default;
    Object(entt::entity entity) : m_entity(entity) {}
    ~Object() = default;

    explicit operator bool() const { return m_entity != entt::null; }
    explicit operator entt::entity() const { return m_entity; }

private:
    entt::entity m_entity{entt::null};
};

} // namespace RendererDemo
