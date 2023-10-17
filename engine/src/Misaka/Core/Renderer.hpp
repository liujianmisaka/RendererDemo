#pragma once

#include "Misaka/Core/Scene.hpp"

namespace RendererDemo {

class Renderer {
public:
    virtual ~Renderer() = default;

    virtual void init() = 0;

    virtual void close() = 0;

    virtual void update() = 0;

	virtual void Render(Scene* scene);
    
    // draw a triangle in window.
    virtual void drawExample() = 0;
    
};

} // namespace RendererDemo
