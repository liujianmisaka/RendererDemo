#pragma once

namespace RendererDemo {

class Component {
public:
    Component() = default;
    virtual ~Component() = default;

    virtual void Tick(float ts){};
};

} // namespace RendererDemo
