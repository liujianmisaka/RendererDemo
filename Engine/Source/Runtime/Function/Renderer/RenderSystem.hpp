#pragma once

#include <memory>

namespace RendererDemo {

class WindowSystem;
class GameWorldManager;
class RHI;
class AssetManager;

enum class GraphicsAPI { OpenGL, Vulkan };

struct RendererSystemInitInfo {
    GraphicsAPI graphics_api = GraphicsAPI::OpenGL;
    std::shared_ptr<WindowSystem> window_system;
    std::shared_ptr<GameWorldManager> game_world_manager;
    std::shared_ptr<AssetManager> asset_manager;
};

class RendererSystem {
public:
    RendererSystem() = default;
    ~RendererSystem() = default;

    void Initialize(RendererSystemInitInfo render_system_init_info);
    void Clear();

    void Tick(float ts);

    std::shared_ptr<RHI> GetRHI() {
        return m_rhi;
    }

private:
    std::shared_ptr<RHI> CreateGrapicsAPIInstance(GraphicsAPI api);

private:
    std::shared_ptr<RHI> m_rhi;
};

} // namespace RendererDemo
