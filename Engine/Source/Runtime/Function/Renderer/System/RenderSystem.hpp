#pragma once

#include <memory>

namespace RendererDemo {

class WindowSystem;
class RHI;

enum class GraphicsAPI { OpenGL, Vulkan };

struct RendererSystemInitInfo {
    GraphicsAPI graphics_api = GraphicsAPI::OpenGL;
    std::shared_ptr<WindowSystem> window_system;
};

class RendererSystem {
public:
    RendererSystem() = default;
    ~RendererSystem() = default;

    void Initialize(RendererSystemInitInfo render_system_init_info);
    void Clear();

    void Tick(float ts);

private:
    std::shared_ptr<RHI> CreateGrapicsAPIInstance(GraphicsAPI api);

private:
    std::shared_ptr<RHI> m_rhi;
};

} // namespace RendererDemo
