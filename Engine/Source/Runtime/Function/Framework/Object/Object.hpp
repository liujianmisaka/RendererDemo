#pragma once

#include <memory>
#include <vector>
#include "Runtime/Core/UUID/UUID.hpp"

namespace RendererDemo {

class Componnet;

class Object {
public:
    ~Object() = default;

    void Tick(float ts);

private:
    UUID m_object_id;

    std::vector<std::shared_ptr<Componnet>> m_components;
};

} // namespace RendererDemo
