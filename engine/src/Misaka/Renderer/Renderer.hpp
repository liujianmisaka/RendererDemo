#pragma once

#include "Misaka/Core/IRenderer.hpp"
#include "Misaka/World/Entity.hpp"
#include "Misaka/World/Scene.hpp"

namespace RendererDemo {

class Renderer : IRenderer {
public:
    virtual ~Renderer() = default;

    virtual void Initialize();
    virtual void Destroy();

    virtual void BeginFrame(){};
    virtual void EndFrame(){};

    virtual void Render(RendererDemo::Scene* scene = nullptr);
    virtual void Render(RendererDemo::Entity* entity = nullptr);

    virtual void LoadShader(){};
    virtual void SetShader(){};

    virtual void LoadTexture(){};
    virtual void BindTexturer(){};

    // draw a triangle in window.
    virtual void drawExample() = 0;
};

} // namespace RendererDemo
