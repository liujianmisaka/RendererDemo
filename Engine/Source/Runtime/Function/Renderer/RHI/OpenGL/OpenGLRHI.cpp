#include "Runtime/Function/Renderer/RHI/OpenGL/OpenGLRHI.hpp"
#include <cstdint>
#include <glm/fwd.hpp>
#include <iostream>
#include <memory>
#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Runtime/Function/Framework/Component/Camera/CameraComponent.hpp"
#include "Runtime/Function/Framework/Component/Render/IndexDrawBufferComponent.hpp"
#include "Runtime/Function/Framework/Component/Transform/TransformComponent.hpp"
#include "Runtime/Function/Framework/FrameworkHeader.hpp"
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
    glEnable(GL_DEPTH_TEST);

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

    // create camera ubo
    glGenBuffers(1, &m_camera_ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, m_camera_ubo);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4) * 3, NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_camera_ubo);
}

void OpenGLRHI::Clear() {}

void OpenGLRHI::GetTextureOfRenderResult(uint64_t& texture_id) { texture_id = m_texture; }

void OpenGLRHI::Tick() {
    auto scene = m_game_world_manager->GetCurrentActivateScene();
    BeginFrame(scene->GetSceneCamera());

    {
        auto view = scene->GetAllObjectWith<IndexDrawBufferComponent, TransformComponent>();
        for (auto entity : view) {
            const auto& draw_buffer_component = view.get<IndexDrawBufferComponent>(entity);
            const auto& draw_buffers = draw_buffer_component.GetDrawBuffers();
            {
                const auto& transform_component = view.get<TransformComponent>(entity);
                const auto& model_matrix = transform_component.GetModelMatrix();
                glBindBuffer(GL_UNIFORM_BUFFER, m_camera_ubo);
                glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(model_matrix));
                glBindBuffer(GL_UNIFORM_BUFFER, 0);
            }
            uint32_t program_id = m_asset_manager->GetProgram("mesh");
            glUseProgram(program_id);
            for (const auto& draw_buffer : draw_buffers) {
                glBindVertexArray(draw_buffer.vertex_array_id);
                glDrawElements(draw_buffer.draw_mode, draw_buffer.index_count, draw_buffer.index_type,
                               (void*)draw_buffer.index_offset);
                glBindVertexArray(0);
            }
            glUseProgram(0);
        }
    }

    EndFrame();
}

void OpenGLRHI::BeginFrame(Object& camera_object) {
    auto& view_matrix = camera_object.GetComponent<CameraComponent>().GetCamera().GetViewMatrix();
    auto& projection_matrix =
        camera_object.GetComponent<CameraComponent>().GetCamera().GetPerspectiveProjectionMatrix();
    // glm::mat4 view_matrix = glm::mat4(1.0f);
    // glm::mat4 projection_matrix = glm::mat4(1.0f);
    glBindBuffer(GL_UNIFORM_BUFFER, m_camera_ubo);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view_matrix));
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4) * 2, sizeof(glm::mat4), glm::value_ptr(projection_matrix));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    // glClearColor(0.0f, 0.0f, 1.0f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT);
}
void OpenGLRHI::EndFrame() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

} // namespace RendererDemo
