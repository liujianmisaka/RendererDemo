#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

#include <vector>

#include "Runtime/Function/Framework/Component/Camera/Camera.hpp"
#include "Runtime/Function/Renderer/RHI/OpenGL/OpenGLClass/OpenGLSampler.hpp"
#include "Runtime/Function/Renderer/RHI/OpenGL/OpenGLClass/OpenGLTexture.hpp"
#include "Runtime/Function/Renderer/RHI/OpenGL/OpenGLClass/OpenGLFramebuffer.hpp"
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
    virtual void Initialize(RHIInitInfo rhi_init_info) override;
    virtual void Clear() override;
    virtual void Tick() override;

    virtual void GetImTextureID(ImTextureID& texture_id) override;
    virtual void SetViewport(int width, int height) override;

private:
    void BeginFrame(Camera& camera);
    void EndFrame();

    void CreateImageTextureForImGui();

private:
    std::shared_ptr<GameWorldManager> m_game_world_manager;
    std::shared_ptr<AssetManager> m_asset_manager;
    std::shared_ptr<WindowSystem> m_window_system;

    GLuint m_camera_ubo = 0;

    OpenGLTexture2D m_texture2d{};
    OpenGLSampler m_sampler{};
    OpenGLFramebuffer m_frame_buffer{};

    std::vector<RHIIndexDrawBuffer> m_draw_buffers;
};

} // namespace RendererDemo
