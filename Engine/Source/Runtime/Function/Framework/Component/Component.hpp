#pragma once

namespace RendererDemo {

class Componnet {
public:
    Componnet() = default;
    virtual ~Componnet() = default;

    virtual void Tick(float ts){};
};

} // namespace RendererDemo
