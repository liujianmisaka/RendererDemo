#include "Runtime/Function/Framework/Component/Camera/CameraComponent.hpp"

namespace RendererDemo {

CameraComponent::CameraComponent(float fov, float aspectRatio, float nearClip, float farClip)
    : m_Fov(fov), m_AspectRatio(aspectRatio), m_NearClip(nearClip), m_FarClip(farClip) {
    UpdateViewMatrix();
    UpdateViewMatrix();
}

void CameraComponent::Tick(float ts) {
    UpdateViewMatrix();
    UpdateProjectionMatrix();
}

void CameraComponent::UpdateViewMatrix() {
    m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Forward, m_Up);
}

void CameraComponent::UpdateProjectionMatrix() {
    m_ProjectionMatrix = glm::perspective(glm::radians(m_Fov), m_AspectRatio, m_NearClip, m_FarClip);
}

} // namespace RendererDemo
