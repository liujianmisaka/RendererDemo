#pragma once

#include <memory>
#include <vector>
#include "Runtime/Core/UUID/UUID.hpp"
#include "Runtime/Function/Framework/Component/Component.hpp"

namespace RendererDemo {

class Component;
class OpenGLRHI;

class Object {
    friend class RendererDemo::OpenGLRHI;

public:
    Object() = default;
    ~Object() = default;

    template <typename T>
    void AddComponent(std::shared_ptr<T> component) {
        m_components.push_back(std::dynamic_pointer_cast<Component>(component));
    }

    // TODO: Fix it
    template <typename T>
    std::shared_ptr<T> GetComponent() {
        for (auto& component : m_components) {
            std::shared_ptr<T> derived = std::dynamic_pointer_cast<T>(component);
            if (derived) {
                return derived;
            }
        }
        return nullptr;
    }

    template <typename T>
    void RemoveComponent(){};

    void Tick(float ts);

private:
    UUID m_object_id;

    std::vector<std::shared_ptr<Component>> m_components;
};

} // namespace RendererDemo
