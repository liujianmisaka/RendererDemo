#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdint>
#include <memory>

#include <vector>

#include "Runtime/Function/Framework/Object/Object.hpp"
#include "Runtime/Function/Renderer/RHI/RHI.hpp"

namespace RendererDemo {

class GameWorldManager;
class AssetManager;
class MeshComponent;
class MeshData;

// TODO: make a better renderer data manager
struct RenderData {};

class OpenGLRHI : public RHI {
public:
    OpenGLRHI(){};
    virtual ~OpenGLRHI() = default;
    virtual void Clear() override;
    virtual void Initialize(RHIInitInfo rhi_init_info) override;

    virtual void GetTextureOfRenderResult(uint64_t& texture_id) override;

    virtual void Tick() override;

private:
    void BeginFrame(Object& camera_object);
    void EndFrame();

private:
    std::shared_ptr<GameWorldManager> m_game_world_manager;
    std::shared_ptr<AssetManager> m_asset_manager;
    std::shared_ptr<WindowSystem> m_window_system;

    GLuint m_fbo = 0;
    GLuint m_texture = 0; // TODO: advance this
    GLuint m_camera_ubo = 0;

    std::vector<RHIIndexDrawBuffer> m_draw_buffers;
};

} // namespace RendererDemo
