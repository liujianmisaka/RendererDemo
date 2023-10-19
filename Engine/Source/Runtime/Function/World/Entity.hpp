#pragma once

#include <string>
namespace RendererDemo {

class Entity {
public:
    Entity() = default;
    ~Entity() = default;

    template <typename T>
    T& AddComponent(T& component);

    template <typename T>
    T& RemoveComponent(T& component);

    template <typename T>
    bool HasComponent(T& component);

    const std::string GetClassName() { return m_ClassName; }

private:
    std::string m_ClassName = "Entity";
};

} // namespace RendererDemo
