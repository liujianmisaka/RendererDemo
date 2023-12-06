#include "Runtime/Function/Framework/Component/Transform/TransformComponent.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace RendererDemo {

void TransformComponent::Tick(float ts) {
    m_model_matrix = glm::translate(glm::mat4(1.0f), m_position) *
                     glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.x), glm::vec3(1, 0, 0)) *
                     glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.y), glm::vec3(0, 1, 0)) *
                     glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.z), glm::vec3(0, 0, 1)) *
                     glm::scale(glm::mat4(1.0f), m_scale);
}

} // namespace RendererDemo
