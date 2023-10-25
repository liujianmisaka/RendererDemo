#pragma once

#include <memory>
#include <string>
#include <unordered_map>

namespace RendererDemo {

class Object;

class Scene {
public:
    ~Scene() = default;

    void Tick(float ts);

public:
    std::unordered_map<std::string, std::shared_ptr<Object>> m_objects {};
};

} // namespace RendererDemo
