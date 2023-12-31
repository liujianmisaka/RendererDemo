#pragma once

#include <glm/glm.hpp>

#include "Runtime/Function/Framework/Component/Component.hpp"

namespace RendererDemo {

class TransformComponent : public Component {
public:
    TransformComponent(std::shared_ptr<entt::registry> registry, entt::entity entity) : Component(registry, entity) {}
    TransformComponent(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);
    virtual ~TransformComponent() override = default;

    virtual void Tick(float ts) override;

    // Getters and Setters
    const glm::vec3& GetPosition() const { return m_position; }
    const glm::vec3& GetRotation() const { return m_rotation; }
    const glm::vec3& GetScale() const { return m_scale; }

    void SetPosition(const glm::vec3& position) {
        m_dirty = true;
        m_position = position;
    }
    void SetRotation(const glm::vec3& rotation) {
        m_dirty = true;
        m_rotation = rotation;
    }
    void SetScale(const glm::vec3& scale) {
        m_dirty = true;
        m_scale = scale;
    }

    const glm::mat4& GetModelMatrix() const { return m_model_matrix; }

private:
    glm::vec3 m_position = glm::vec3(0.0f);
    glm::vec3 m_rotation = glm::vec3(0.0f);
    glm::vec3 m_scale = glm::vec3(1.0f);

    glm::mat4 m_model_matrix = glm::mat4(1.0f);
};

} // namespace RendererDemo
