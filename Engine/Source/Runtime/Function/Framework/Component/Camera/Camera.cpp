#include "Runtime/Function/Framework/Component/Camera/Camera.hpp"

namespace RendererDemo {

const glm::mat4 Camera::GetViewMatrix() {
    ReCalculateRotation();
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

const glm::mat4 Camera::GetPerspectiveProjectionMatrix() {
    ReCalculateRotation();
    return glm::perspective(glm::radians(m_fov), m_aspect_ratio, m_near_clip, m_far_clip);
}

const glm::mat4 Camera::GetOrthographicProjectionMatrix() {
    ReCalculateRotation();
    // Orthographic projection matrix = glm::ortho(left, right, bottom, top, near, far)
    return glm::ortho(-m_aspect_ratio, m_aspect_ratio, -1.0f, 1.0f, m_near_clip, m_far_clip);
}

void Camera::ReCalculateRotation() {
    // the camera front needs to be re-calculated when the camera is rotated
    glm::vec3 front;
    front.x = cos(glm::radians(m_rotation.y)) * cos(glm::radians(m_rotation.x));
    front.y = sin(glm::radians(m_rotation.x));
    front.z = sin(glm::radians(m_rotation.y)) * cos(glm::radians(m_rotation.x));
    m_front = glm::normalize(front);
    // re-calculate the camera right and up which are dependent on the camera front
    m_right = glm::normalize(glm::cross(m_front, m_world_up));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}
} // namespace RendererDemo
