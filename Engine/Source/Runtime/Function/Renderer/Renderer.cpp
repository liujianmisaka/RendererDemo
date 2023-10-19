#include "Runtime/Function/Renderer/Renderer.hpp"

namespace RendererDemo {

void Renderer::Render(RendererDemo::Scene* scene) {
    if (scene) {
        scene->OnRender();

    } else {
        drawExample();
    }
}

void Renderer::drawExample() {}

} // namespace RendererDemo
