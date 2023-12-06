#include "Runtime/Function/Framework/Component/Render/IndexDrawBufferComponent.hpp"
#include <cstdint>
#include <vector>
#include "Runtime/Function/Framework/Component/Component.hpp"
#include "Runtime/Function/Framework/Component/Mesh/MeshComponent.hpp"
#include "Runtime/Function/Renderer/RHI/OpenGL/OpenGLAPI.hpp"
#include "Runtime/Function/Renderer/RHI/RHIPredefined.hpp"
#include "Runtime/Function/Renderer/RHI/RHIStruct.hpp"

namespace RendererDemo {

void IndexDrawBufferComponent::GenerateIndexDrawBuffer(const MeshComponent& component) {
    const RendererDemo::StaticMeshData& mesh_data = component.MeshData();

    std::vector<StaticMeshDataVertex> vertices = GenerateVertexData(component);
    const auto& index_buffer = mesh_data.index_buffer;

    uint32_t vertex_id = OpenGLAPI::CreateVertexBuffer(vertices.size() * sizeof(StaticMeshDataVertex), vertices.data());

    uint32_t index_id =
        OpenGLAPI::CreateIndexBuffer(index_buffer.primitive_count * sizeof(unsigned int), index_buffer.indices.data());

    uint32_t vertex_array_id = OpenGLAPI::CreateVertexArray(vertex_id, index_id, KOpenGLMeshVertexLayout);

    RHIIndexDrawBuffer draw_buffer;
    draw_buffer.draw_mode = GL_TRIANGLES;
    draw_buffer.index_count = index_buffer.primitive_count;
    draw_buffer.index_type = GL_UNSIGNED_INT;
    draw_buffer.index_offset = 0;
    draw_buffer.vertex_array_id = vertex_array_id;
    draw_buffer.shader_type = m_shader_type;

    m_draw_buffers.emplace_back(draw_buffer);
}

void IndexDrawBufferComponent::GenerateIndexDrawBuffer(const SquaComponent& component) {
    const float vertices[] = {
        // four vertices
        -0.5f, -0.5f, 0.0f, // bottom left
        0.5f,  -0.5f, 0.0f, // bottom right
        0.5f,  0.5f,  0.0f, // top right
        -0.5f, 0.5f,  0.0f, // top left
    };

    const unsigned int indices[] = {
        0, 1, 2, // first triangle
        2, 3, 0, // second triangle
    };

    uint32_t vertex_id = OpenGLAPI::CreateVertexBuffer(sizeof(vertices), vertices);

    uint32_t index_id = OpenGLAPI::CreateIndexBuffer(sizeof(indices), indices);

    RHIVertexLayout layout = {
        .attributes =
            {
                {
                    // position
                    .location = 0,
                    .offset = 0,
                    .count = 3,
                    .data_type = RHIDataType::Float,
                    .normalized = false,
                },
            },
        .stride = 3 * sizeof(float),
    };

    uint32_t vertex_array_id = OpenGLAPI::CreateVertexArray(vertex_id, index_id, layout);

    RHIIndexDrawBuffer draw_buffer;
    draw_buffer.draw_mode = GL_TRIANGLES;
    draw_buffer.index_count = sizeof(indices) / sizeof(unsigned int);
    draw_buffer.index_type = GL_UNSIGNED_INT;
    draw_buffer.index_offset = 0;
    draw_buffer.vertex_array_id = vertex_array_id;
    draw_buffer.shader_type = RHIShaderType::KTriangle;

    m_draw_buffers.emplace_back(draw_buffer);
}

std::vector<StaticMeshDataVertex> IndexDrawBufferComponent::GenerateVertexData(const MeshComponent& mesh_component) {
    const RendererDemo::StaticMeshData& mesh_data = mesh_component.MeshData();
    const RawVertexBuffer& vertex_buffer = mesh_data.vertex_buffer;
    std::vector<StaticMeshDataVertex> vertices(vertex_buffer.vertex_count);
    for (int i = 0; i < vertex_buffer.vertex_count; ++i) {
        vertices[i].position = {vertex_buffer.positions[i * 3], vertex_buffer.positions[i * 3 + 1],
                                vertex_buffer.positions[i * 3 + 2]};
        vertices[i].normal = {vertex_buffer.normals[i * 3], vertex_buffer.normals[i * 3 + 1],
                              vertex_buffer.normals[i * 3 + 2]};
        vertices[i].tangent = {vertex_buffer.tangents[i * 3], vertex_buffer.tangents[i * 3 + 1],
                               vertex_buffer.tangents[i * 3 + 2]};
        vertices[i].bitangent = {vertex_buffer.bitangents[i * 3], vertex_buffer.bitangents[i * 3 + 1],
                                 vertex_buffer.bitangents[i * 3 + 2]};
        vertices[i].uv = {vertex_buffer.uvs[i * 2], vertex_buffer.uvs[i * 2 + 1]};
    }
    return vertices;
}

} // namespace RendererDemo
