#pragma once

#include <glm/glm.hpp>
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

    void SetMVP(const MVP& mvp) { m_mvp = mvp; }
    const MVP& GetMVP() const { return m_mvp; }

private:
    MVP m_mvp;
    RHIShaderType m_shader_type = RHIShaderType::KMesh;
};

} // namespace RendererDemo
