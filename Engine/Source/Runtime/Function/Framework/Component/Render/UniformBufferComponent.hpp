#pragma once

#include <glm/glm.hpp>
#include <string>
#include <unordered_map>
#include "Runtime/Function/Framework/Component/Component.hpp"
#include "Runtime/Function/Renderer/RHI/RHIStruct.hpp"
namespace RendererDemo {

struct MVP {
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
};

class UniformBufferComponent : public Component {
public:
    UniformBufferComponent() = default;
    virtual ~UniformBufferComponent() = default;

    void AddMat4UniformBuffer(std::string name, glm::mat4 mat4) { m_mat4_uniforms[name] = mat4; }
    const std::unordered_map<std::string, glm::mat4>& GetMat4UniformBuffers() const { return m_mat4_uniforms; }

    void SetShaderType(RHIShaderType shader_type) { m_shader_type = shader_type; }
    RHIShaderType GetShaderType() const { return m_shader_type; }

private:
    std::unordered_map<std::string, glm::mat4> m_mat4_uniforms{};
    RHIShaderType m_shader_type = RHIShaderType::KMesh;
};

} // namespace RendererDemo
