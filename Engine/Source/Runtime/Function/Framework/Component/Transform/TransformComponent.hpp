#pragma once

#include <glm/glm.hpp>

#include "Runtime/Function/Framework/Component/Component.hpp"

namespace RendererDemo {

class TransformComponent : public Component {
public:
    TransformComponent() = default;
    TransformComponent(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);
    ~TransformComponent() = default;

    glm::mat4 GetModelMatrix() {
        return m_model_matrix;
    }

    glm::vec3 GetPosition() {
        return m_position;
    }

    glm::vec3 GetRotation() {
        return m_rotation;
    }

    glm::vec3 GetScale() {
        return m_scale;
    }

    void SetPosition(const glm::vec3& position) {
        m_position = position;
        UpdateModelMatrix();
    }

    void SetRotation(const glm::vec3& rotation) {
        m_rotation = rotation;
        UpdateModelMatrix();
    }

    void SetScale(const glm::vec3& scale) {
        m_scale = scale;
        UpdateModelMatrix();
    }

private:
    void UpdateModelMatrix();

private:
    glm::mat4 m_model_matrix = glm::mat4(1.0f);
    glm::vec3 m_position = glm::vec3(0.0f);
    glm::vec3 m_rotation = glm::vec3(0.0f);
    glm::vec3 m_scale = glm::vec3(1.0f);
};

} // namespace RendererDemo
