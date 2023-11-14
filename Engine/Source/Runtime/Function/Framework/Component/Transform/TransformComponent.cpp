#include "Runtime/Function/Framework/Component/Transform/TransformComponent.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace RendererDemo {

void TransformComponent::UpdateModelMatrix() {
    m_model_matrix = glm::mat4(1.0f);
    m_model_matrix = glm::translate(m_model_matrix, m_position);
    m_model_matrix = glm::rotate(m_model_matrix, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    m_model_matrix = glm::rotate(m_model_matrix, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    m_model_matrix = glm::rotate(m_model_matrix, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    m_model_matrix = glm::scale(m_model_matrix, m_scale);
}

} // namespace RendererDemo
