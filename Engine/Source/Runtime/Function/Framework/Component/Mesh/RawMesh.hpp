#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace RendererDemo {

enum class PrimitiveType { None, point, line, triangle, quad };

struct RawVertexBuffer {
    uint32_t vertex_count{0};
    std::vector<float> positions;  // vertex_count * 3
    std::vector<float> normals;    // vertex_count * 3
    std::vector<float> tangents;   // vertex_count * 3
    std::vector<float> bitangents; // vertex_count * 3
    std::vector<float> uvs;        // vertex_count * 2
};

struct RawIndexBuffer {
    PrimitiveType primitive_type{PrimitiveType::triangle};
    uint32_t primitive_count{0};
    std::vector<uint32_t> indices; // primitive_count * 3 as default
};

struct MaterialTexture {
    std::string base_color;
    std::string metallic_roughness;
    std::string normal;
};

struct MeshData {
    RawVertexBuffer vertex_buffer;
    RawIndexBuffer index_buffer;
};

struct StaticMeshData {
    RawVertexBuffer vertex_buffer;
    RawIndexBuffer index_buffer;
    MaterialTexture material_texture;
};

} // namespace RendererDemo
