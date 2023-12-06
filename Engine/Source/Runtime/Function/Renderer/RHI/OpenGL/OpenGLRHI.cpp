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
    // glDisable(GL_CULL_FACE);
    // glEnable(GL_DEPTH_TEST);

    CreateImageTextureForImGui();

    // create camera ubo
    glGenBuffers(1, &m_camera_ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, m_camera_ubo);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4) * 3, NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_camera_ubo);
}

void OpenGLRHI::Clear() {}

void OpenGLRHI::GetImTextureID(ImTextureID& texture_id) { texture_id = (ImTextureID)(uint64_t)m_texture2d; }

void OpenGLRHI::SetViewport(int width, int height) {
    glViewport(0, 0, width, height);
    m_texture2d.TexImage2D(width, height);
}

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

    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glClearColor(0.0f, 0.0f, 1.0f, 0.5f);
    m_frame_buffer.Clear();
}
void OpenGLRHI::EndFrame() { m_frame_buffer.UnBind(); }

void OpenGLRHI::CreateImageTextureForImGui() {
    m_frame_buffer.Create();
    m_texture2d.Create();
    m_sampler.Create();

    m_texture2d.TexImage2D(m_window_system->GetWidth(), m_window_system->GetHeight());
    // m_sampler.Bind((uint32_t)m_texture2d);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // TODO: use sampler
    m_frame_buffer.BindTexture2D((uint32_t)m_texture2d);

    m_texture2d.UnBind();
    m_frame_buffer.UnBind();
}

} // namespace RendererDemo
