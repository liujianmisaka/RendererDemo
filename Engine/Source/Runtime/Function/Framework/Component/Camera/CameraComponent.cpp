#include "Runtime/Function/Framework/Component/Camera/CameraComponent.hpp"

namespace RendererDemo {

CameraComponent::CameraComponent(float fov, float aspectRatio, float nearClip, float farClip)
    : m_fov(fov), m_aspect_ratio(aspectRatio), m_near_clip(nearClip), m_far_clip(farClip) {
    UpdateViewMatrix();
    UpdateViewMatrix();
}

void CameraComponent::Tick(float ts) {
    UpdateViewMatrix();
    UpdateProjectionMatrix();
}

void CameraComponent::UpdateViewMatrix() { m_view_matrix = glm::lookAt(m_position, m_position + m_forward, m_up); }

void CameraComponent::UpdateProjectionMatrix() {
    m_projection_matrix = glm::perspective(glm::radians(m_fov), m_aspect_ratio, m_near_clip, m_far_clip);
}

} // namespace RendererDemo
