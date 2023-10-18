#pragma once

#include "Misaka/Core/Scene.hpp"

namespace RendererDemo {

class Renderer {
public:
    virtual ~Renderer() = default;

    virtual void Init() = 0;

    virtual void Close() = 0;

	virtual void Render(RendererDemo::Scene* scene = nullptr);
    
    // draw a triangle in window.
    virtual void drawExample() = 0;
    
};

} // namespace RendererDemo
