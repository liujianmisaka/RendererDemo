#pragma once

#include <glm/glm.hpp>

#include "Runtime/Function/Framework/Component/Component.hpp"

namespace RendererDemo {

class TransformComponent : public Component {
public:
    TransformComponent() = default;
    TransformComponent(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);
    virtual ~TransformComponent() override = default;

    virtual void Tick(float ts) override;

    // Getters and Setters
    const glm::vec3& GetPosition() const { return m_position; }
    const glm::vec3& GetRotation() const { return m_rotation; }
    const glm::vec3& GetScale() const { return m_scale; }

    void SetPosition(const glm::vec3& position) { m_position = position; }
    void SetRotation(const glm::vec3& rotation) { m_rotation = rotation; }
    void SetScale(const glm::vec3& scale) { m_scale = scale; }

    glm::mat4 GetModelMatrix() { return m_model_matrix; }

private:
    glm::vec3 m_position = glm::vec3(0.0f);
    glm::vec3 m_rotation = glm::vec3(0.0f);
    glm::vec3 m_scale = glm::vec3(1.0f);

    glm::mat4 m_model_matrix = glm::mat4(1.0f);
};

} // namespace RendererDemo
