#include "Runtime/Function/Framework/Component/Transform/TransformComponent.hpp"
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace RendererDemo {

void TransformComponent::Tick(float ts) {
    if (m_dirty) {
        m_model_matrix = glm::translate(glm::mat4(1.0f), m_position) * glm::toMat4(glm::quat(m_rotation)) *
                         glm::scale(glm::mat4(1.0f), m_scale);
        m_dirty = false;
    }
}

} // namespace RendererDemo
