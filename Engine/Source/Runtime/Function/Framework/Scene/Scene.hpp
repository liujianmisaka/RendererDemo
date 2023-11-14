#pragma once

#include <memory>
#include <string>
#include <unordered_map>

namespace RendererDemo {

class Object;
class OpenGLRHI;

class Scene {
    friend class RendererDemo::OpenGLRHI;

public:
    Scene() = default;
    ~Scene() = default;

    void Tick(float ts);

    void AddObject(std::string name, std::shared_ptr<Object> object) {
        m_objects[name] = object;
    }

    const std::unordered_map<std::string, std::shared_ptr<Object>>& GetObjects() {
        return m_objects;
    }

public:
    std::unordered_map<std::string, std::shared_ptr<Object>> m_objects{};
};

} // namespace RendererDemo
