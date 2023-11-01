#include "Editor/Editor.hpp"
#include <memory>
#include <filesystem>
#include <iostream>
#include "Runtime/Core/Base/Types.hpp"
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
    ShaderCreateInfoInfo vertex_shader_info;
    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
    vertex_shader_info.SetShaderType(ShaderType::VertexShader)
        .SetShaderPath("C:/dev/RendererDemo/Engine/Shaders/GLSL/base.vert");

    ShaderCreateInfoInfo fragment_shader_info;
    fragment_shader_info.SetShaderType(ShaderType::FragmentShader)
        .SetShaderPath("C:/dev/RendererDemo/Engine/Shaders/GLSL/base.frag");

    rhi->CreateShader(vertex_shader_info);
    rhi->CreateShader(fragment_shader_info);
    rhi->CreateProgram();

    BufferCreateInfo vertex_buffer_info;
    vertex_buffer_info.SetBufferData(vertices.data())
        .SetBufferByteSize(sizeof(float) * vertices.size())
        .SetBufferType(BufferType::VertexBuffer)
        .SetBufferDataType(MisakaDataType::Float);
    rhi->CreateBuffer(vertex_buffer_info);

    BufferCreateInfo index_buffer_info1;
    index_buffer_info1.SetBufferData(indices1.data())
        .SetBufferByteSize(sizeof(unsigned int) * indices1.size())
        .SetBufferType(BufferType::IndexBuffer)
        .SetBufferDataType(MisakaDataType::UInt);
    rhi->CreateBuffer(index_buffer_info1);

    VertexLayoutCreateInfo layout1{};
    layout1.SetVertexByteSize(sizeof(float) * 6)
        .AddElementInfo({0, 3, MisakaTargetType::Float})
        .AddElementInfo({1, 3, MisakaTargetType::Float});
    // .AddElementInfo({2, 2, MisakaTargetType::Float});
    rhi->CreateVertexLayout(layout1);

    rhi->CreateVertexArray();

    rhi->CreateIndexDrawBuffer();

    BufferCreateInfo index_buffer_info2;
    index_buffer_info2.SetBufferData(indices2.data())
        .SetBufferByteSize(sizeof(unsigned int) * indices2.size())
        .SetBufferType(BufferType::IndexBuffer)
        .SetBufferDataType(MisakaDataType::UInt);
    rhi->CreateBuffer(index_buffer_info2);

    VertexLayoutCreateInfo layout2{};
    layout2.SetVertexByteSize(sizeof(float) * 6)
        .AddElementInfo({0, 3, MisakaTargetType::Float})
        .AddElementInfo({1, 3, MisakaTargetType::Float});
    // .AddElementInfo({2, 2, MisakaTargetType::Float});
    rhi->CreateVertexLayout(layout2);

    rhi->CreateVertexArray();

    rhi->CreateIndexDrawBuffer();
}

} // namespace RendererDemo
