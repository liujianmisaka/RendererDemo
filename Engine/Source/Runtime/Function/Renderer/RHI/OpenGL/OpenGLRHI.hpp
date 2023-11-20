#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "Runtime/Function/Framework/Scene/Scene.hpp"
#include "Runtime/Function/Renderer/RHI/RHI.hpp"

namespace RendererDemo {

class GameWorldManager;
class AssetManager;
class MeshData;

class OpenGLRHI : public RHI {
public:
    OpenGLRHI(){};
    virtual ~OpenGLRHI() = default;
    virtual void Clear() override;
    virtual void Initialize(RHIInitInfo rhi_init_info) override;
    virtual void CreateBuffer(RHIBufferCreateInfo create_info) override;

    // Renderer Component level
    std::vector<RHIIndexDrawBuffer> RenderMesh(std::vector<MeshData> meshs_data);

    // Renderer Object level
    void RenderSceneCamera(Scene& scene);

    virtual void GetTextureOfRenderResult(uint64_t& texture_id) override;

    virtual void Tick() override;

private:
    std::shared_ptr<GameWorldManager> m_game_world_manager;
    std::shared_ptr<AssetManager> m_asset_manager;
    std::shared_ptr<WindowSystem> m_window_system;

    GLuint m_fbo = 0;
    GLuint m_texture = 0; // TODO: advance this

    std::unordered_map<std::string, uint32_t> m_vertex_buffers;
    std::unordered_map<std::string, uint32_t> m_index_buffers;
    std::unordered_map<std::string, uint32_t> m_uniform_buffers;
    std::unordered_map<std::string, RHIVertexLayout> m_vertex_layouts;
    std::unordered_map<std::string, uint32_t> m_vertex_arrays;

    std::vector<RHIIndexDrawBuffer> m_draw_buffers;
    int m_draw_buffer_index = 0;
};

} // namespace RendererDemo
