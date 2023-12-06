#pragma once

#include <glm/glm.hpp>
#include "Runtime/Function/Framework/Component/Component.hpp"
#include "Runtime/Function/Renderer/RHI/RHIStruct.hpp"

namespace RendererDemo {

class MeshComponent;

struct StaticMeshDataVertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 tangent;
    glm::vec3 bitangent;
    glm::vec2 uv;
};

class IndexDrawBufferComponent : public Component {
public:
    // must have a program id
    IndexDrawBufferComponent() = default;
    IndexDrawBufferComponent(RHIShaderType shader_type) : m_shader_type(shader_type) {}
    virtual ~IndexDrawBufferComponent() = default;

    void GenerateIndexDrawBuffer(const MeshComponent& component);
    void GenerateIndexDrawBuffer(const SquaComponent& component);
    const std::vector<RHIIndexDrawBuffer>& GetDrawBuffers() const { return m_draw_buffers; }
    RHIShaderType GetDrawType() { return m_shader_type; }

private:
    std::vector<StaticMeshDataVertex> GenerateVertexData(const MeshComponent& mesh_component);

private:
    std::vector<RHIIndexDrawBuffer> m_draw_buffers;
    RHIShaderType m_shader_type = RHIShaderType::KMesh;
};

} // namespace RendererDemo
