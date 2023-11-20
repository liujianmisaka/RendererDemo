#include "Runtime/Function/Renderer/RHI/OpenGL/OpenGLRHI.hpp"
#include <cassert>
#include <cstdint>
#include <iostream>
#include <memory>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Runtime/Function/Framework/FrameworkHeader.hpp"
#include "Runtime/Function/Renderer/RHI/RHIPredefined.hpp"
#include "Runtime/Function/Renderer/RHI/OpenGL/OpenGLAPI.hpp"
#include "Runtime/Resource/Manager/AssetManager.hpp"

namespace RendererDemo {

void OpenGLRHI::Initialize(RHIInitInfo rhi_init_info) {
    m_game_world_manager = rhi_init_info.game_world_manager;
    m_asset_manager = rhi_init_info.asset_manager;
    m_window_system = rhi_init_info.window_system;

    // 初始化 glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize glad" << std::endl;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glDisable(GL_CULL_FACE);

    // 创建一个帧缓冲对象（FBO）和一个纹理
    glGenFramebuffers(1, &m_fbo);
    glGenTextures(1, &m_texture);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_window_system->GetWidth(), m_window_system->GetHeight(), 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGLRHI::Clear() {}

void OpenGLRHI::CreateBuffer(RHIBufferCreateInfo create_info) {
    uint32_t buffer_id = 0;
    switch (create_info.buffer_type) {
        case RHIBufferType::VertexBuffer: {
            buffer_id = OpenGLAPI::CreateVertexBuffer(create_info.byte_size, create_info.data);
            m_vertex_buffers[create_info.name] = buffer_id;
            break;
        }
        case RHIBufferType::IndexBuffer: {
            buffer_id = OpenGLAPI::CreateIndexBuffer(create_info.byte_size, create_info.data);
            m_index_buffers[create_info.name] = buffer_id;
            break;
        }
        case RHIBufferType::UniformBuffer: {
            buffer_id = OpenGLAPI::CreateUniformBuffer(create_info.byte_size, create_info.data);
            m_uniform_buffers[create_info.name] = buffer_id;
            break;
        }
        default: {
            std::cerr << "Unhandled buffer type in switch statement" << std::endl;
            break;
        }
    }
}

std::vector<RHIIndexDrawBuffer> OpenGLRHI::RenderMesh(std::vector<MeshData> meshs_data) {
    std::vector<RHIIndexDrawBuffer> draw_buffers;
    uint32_t program_id = m_asset_manager->GetProgram("mesh");
    for (MeshData mesh_data : meshs_data) {
        const RawVertexBuffer& vertex_buffer = mesh_data.vertex_buffer;
        const RawIndexBuffer& index_buffer = mesh_data.index_buffer;

        uint32_t position_id = OpenGLAPI::CreateVertexBuffer(vertex_buffer.vertex_count * sizeof(float) * 3,
                                                             vertex_buffer.positions.data());
        uint32_t normal_id =
            OpenGLAPI::CreateVertexBuffer(vertex_buffer.vertex_count * sizeof(float) * 3, vertex_buffer.normals.data());
        uint32_t index_id = OpenGLAPI::CreateIndexBuffer(index_buffer.primitive_count * sizeof(unsigned int),
                                                         index_buffer.indices.data());

        uint32_t position_vertex_array_id =
            OpenGLAPI::CreateVertexArray(position_id, index_id, KOpenGLMeshVertexLayout);
        uint32_t normal_vertex_array_id = OpenGLAPI::CreateVertexArray(normal_id, index_id, KOpenGLMeshVertexLayout);

        RHIIndexDrawBuffer position_draw_buffer;
        position_draw_buffer.draw_mode = GL_TRIANGLES;
        position_draw_buffer.index_count = index_buffer.primitive_count;
        position_draw_buffer.index_type = GL_UNSIGNED_INT;
        position_draw_buffer.index_offset = 0;
        position_draw_buffer.vertex_array_id = position_vertex_array_id;
        position_draw_buffer.program_id = program_id;

        RHIIndexDrawBuffer normal_draw_buffer;
        normal_draw_buffer.draw_mode = GL_TRIANGLES;
        normal_draw_buffer.index_count = index_buffer.primitive_count;
        normal_draw_buffer.index_type = GL_UNSIGNED_INT;
        normal_draw_buffer.index_offset = 0;
        normal_draw_buffer.vertex_array_id = normal_vertex_array_id;
        normal_draw_buffer.program_id = program_id;

        draw_buffers.emplace_back(position_draw_buffer);
        draw_buffers.emplace_back(normal_draw_buffer);
    }
    return draw_buffers;
}

void OpenGLRHI::RenderCamera() {}

void OpenGLRHI::GetTextureOfRenderResult(uint64_t& texture_id) { texture_id = m_texture; }

void OpenGLRHI::Tick() {
    auto scene = m_game_world_manager->GetActivateScene();
    for (auto& object : scene->GetObjects()) {
        if (object.first == "basic_object") {
            auto mesh_component = object.second->GetComponent<MeshComponent>();
            if (mesh_component == nullptr || mesh_component->Flag()) continue;
            const std::vector<MeshData>& meshs_data = mesh_component->GetMeshData();
            m_draw_buffers = RenderMesh(meshs_data);
            mesh_component->SetFlag(true);
        }
    }

    glClear(GL_COLOR_BUFFER_BIT);

    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    // TODO: Add default draw buffer when no draw buffer is created
    assert(m_draw_buffers.size() > 0);

    for (int i = 0; i < m_draw_buffers.size(); i++) {
        RHIIndexDrawBuffer draw_buffer = m_draw_buffers[i];
        glBindVertexArray(draw_buffer.vertex_array_id);
        glUseProgram(draw_buffer.program_id);
        glDrawElements(draw_buffer.draw_mode, draw_buffer.index_count, draw_buffer.index_type,
                       (void*)draw_buffer.index_offset);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

} // namespace RendererDemo
