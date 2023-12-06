#pragma once

#include <glm/glm.hpp>
#include "Runtime/Function/Framework/Component/Component.hpp"
#include "Runtime/Function/Framework/Component/Mesh/RawMesh.hpp"
#include "Runtime/Function/Renderer/RHI/RHIStruct.hpp"

namespace RendererDemo {

class MeshComponent;
class SquaComponent;

struct StaticMeshDataVertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 tangent;
    glm::vec3 bitangent;
    glm::vec2 uv;
};

class IndexDrawBufferComponent : public Component {
public:
    IndexDrawBufferComponent(std::shared_ptr<entt::registry> registry, entt::entity entity)
        : Component(registry, entity) {}
    virtual ~IndexDrawBufferComponent() = default;

    void GenerateIndexDrawBuffer(const RendererDemo::StaticMeshData& mesh_data);
    void GenerateIndexDrawBuffer();
    const std::vector<RHIIndexDrawBuffer>& GetDrawBuffers() const { return m_draw_buffers; }
    RHIShaderType GetDrawType() { return m_shader_type; }

private:
    std::vector<StaticMeshDataVertex> GenerateVertexData(const RendererDemo::StaticMeshData& mesh_data);

private:
    std::vector<RHIIndexDrawBuffer> m_draw_buffers;
    RHIShaderType m_shader_type = RHIShaderType::KMesh;
};

} // namespace RendererDemo
