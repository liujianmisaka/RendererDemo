#pragma once

#include "Misaka/World/LayerStack.hpp"

namespace RendererDemo {

class Scene {
public:
    Scene() = default;
    ~Scene() = default;

    void Init();
    void Destroy();

    void OnUpdate();

	void OnRender();

private:
    RendererDemo::LayerStack m_LayerStack;
};

} // namespace RendererDemo
