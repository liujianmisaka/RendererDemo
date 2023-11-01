#pragma once

namespace RendererDemo {

class Componnet {
public:
    virtual ~Componnet() = default;

    virtual void Tick(float ts) = 0;
};

} // namespace RendererDemo
