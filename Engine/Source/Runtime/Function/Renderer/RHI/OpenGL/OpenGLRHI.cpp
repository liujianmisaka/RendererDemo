#include "Runtime/Function/Renderer/RHI/OpenGL/OpenGLRHI.hpp"
#include <cstdint>
#include <iostream>
#include <memory>
#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Runtime/Function/Framework/Component/Render/IndexDrawBufferComponent.hpp"
#include "Runtime/Function/Framework/Component/Render/UniformBufferComponent.hpp"
#include "Runtime/Function/Framework/FrameworkHeader.hpp"
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

void OpenGLRHI::GetTextureOfRenderResult(uint64_t& texture_id) { texture_id = m_texture; }

void OpenGLRHI::Tick() {
    auto scene = m_game_world_manager->GetCurrentActivateScene();

    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glClearColor(0.0f, 0.0f, 1.0f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT);

    {
        auto view = scene->GetAllObjectWith<IndexDrawBufferComponent>();
        for (auto entity : view) {
            const auto& draw_buffer_component = view.get<IndexDrawBufferComponent>(entity);
            auto program_id = m_asset_manager->GetProgram("mesh");
            glUseProgram(program_id);
            const auto& draw_buffers = draw_buffer_component.GetDrawBuffers();
            for (const auto& draw_buffer : draw_buffers) {
                glBindVertexArray(draw_buffer.vertex_array_id);
                glDrawElements(draw_buffer.draw_mode, draw_buffer.index_count, draw_buffer.index_type,
                               (void*)draw_buffer.index_offset);
            }
        }
    }

    {
        auto view = scene->GetAllObjectWith<UniformBufferComponent>();
        for (auto entity : view) {
            const auto& uniform_component = view.get<UniformBufferComponent>(entity);
            auto program_id = m_asset_manager->GetProgram("mesh");
            MVP mvp = uniform_component.GetMVP();
            OpenGLAPI::UploadMat4(program_id, "u_model", mvp.model);
            OpenGLAPI::UploadMat4(program_id, "u_view", mvp.view);
            OpenGLAPI::UploadMat4(program_id, "u_projection", mvp.projection);
        }
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

} // namespace RendererDemo
