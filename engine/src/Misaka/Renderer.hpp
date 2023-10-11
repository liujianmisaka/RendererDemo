#pragma once


namespace RendererDemo {

class Renderer {
public:
    Renderer() {};
    virtual ~Renderer() {};

    virtual void init() = 0;

    virtual void close() = 0;

    // draw a triangle in window.
    virtual void drawExample() = 0;
    
    virtual void update() = 0;
};

} // namespace RendererDemo