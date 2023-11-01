#include "Editor/Editor.hpp"
#include <memory>
#include <filesystem>
#include <iostream>
#include "Runtime/Engine.hpp"
#include "Runtime/Function/Renderer/RHI/RHI.hpp"
#include "Runtime/Function/RuntimeContext/RuntimeContext.hpp"
#include "Runtime/Function/Renderer/System/RenderSystem.hpp"
#include "Runtime/Function/Renderer/RHI/Interface/Buffer.hpp"
#include "Runtime/Function/Renderer/RHI/Interface/Shader.hpp"
#include "Runtime/Function/Renderer/RHI/Interface/Layout.hpp"

namespace RendererDemo {

void MisakaEditor::Initialize(RendererDemo::MisakaEngine* runtime_engine) {
    m_runtime_engine = runtime_engine;
    Process();
}

void MisakaEditor::Clear() {
}
void MisakaEditor::Run() {
    m_runtime_engine->Run();
}

void MisakaEditor::Process() {
    std::shared_ptr<RHI> rhi = g_runtime_context.m_renderer_system->GetRHI();
    /* -------------------------------------------------------------------------- */
    /*                               Test OpenGLRHI                               */
    /* -------------------------------------------------------------------------- */
    ShaderInfo vertex_shader_info;
    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
    vertex_shader_info.SetShaderFileType(ShaderFileType::Text)
        .SetShaderType(ShaderType::VertexShader)
        .SetShaderPath("C:/dev/RendererDemo/Engine/Shaders/GLSL/base.vert");

    ShaderInfo fragment_shader_info;
    fragment_shader_info.SetShaderFileType(ShaderFileType::Text)
        .SetShaderType(ShaderType::FragmentShader)
        .SetShaderPath("C:/dev/RendererDemo/Engine/Shaders/GLSL/base.frag");

    rhi->CreateShader(vertex_shader_info);
    rhi->CreateShader(fragment_shader_info);
    rhi->CreateProgram();

    BufferInfo vertex_buffer_info;
    vertex_buffer_info.SetBufferData(vertices.data())
        .SetBufferSize(sizeof(float) * vertices.size())
        .SetBufferType(BufferType::VertexBuffer);
    rhi->CreateBuffer(vertex_buffer_info);

    BufferInfo index_buffer_info;
    index_buffer_info.SetBufferData(indices.data())
        .SetBufferSize(sizeof(unsigned int) * indices.size())
        .SetBufferType(BufferType::IndexBuffer);
    rhi->CreateBuffer(index_buffer_info);

    RawVertexLayout layout{};
    layout.SetVertexByteSize(sizeof(float) * 6)
        .AddElementInfo({0, 3, MisakaTargetType::Float})
        .AddElementInfo({1, 3, MisakaTargetType::Float});
    // .AddElementInfo({2, 2, MisakaTargetType::Float});
    rhi->CreateVertexLayout(layout);

    rhi->CreateVertexArray();
}

} // namespace RendererDemo
