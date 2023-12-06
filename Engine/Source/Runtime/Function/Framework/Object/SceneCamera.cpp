#include "Runtime/Function/Framework/Object/SceneCamera.hpp"
#include <glm/ext/matrix_transform.hpp>
#include "Runtime/Function/Framework/Component/Camera/CameraComponent.hpp"

namespace RendererDemo {

SceneCamera::SceneCamera(entt::entity entity, std::shared_ptr<entt::registry> entt_register)
    : Object(entity, entt_register) {
    auto& camera_component = GetComponent<CameraComponent>();

    m_position = camera_component.GetPosition();
    m_up = camera_component.GetUp();
    m_forward = camera_component.GetForward();

    m_aspect_ratio = camera_component.GetAspectRatio();

    m_perspective_far = camera_component.GetFarClip();
    m_perspective_near = camera_component.GetNearClip();
    m_perspective_fov = camera_component.GetFov();
    m_orthographic_far = camera_component.GetFarClip();
    m_orthographic_near = camera_component.GetNearClip();
    // default orthographic size is the vertical length of the far clip plane
    m_orthographic_size = camera_component.GetFarClip() * glm::tan(camera_component.GetFov() / 2.0f);

    CalculateViewMatrix();
    CalculateProjectionMatrix();
    m_view_projection_matrix = m_projection_matrix * m_view_matrix;
}

void SceneCamera::Tick(float ts) {
    CalculateViewMatrix();
    CalculateProjectionMatrix();
    m_view_projection_matrix = m_projection_matrix * m_view_matrix;
}

void SceneCamera::CalculateViewMatrix() {
    auto& camera_component = GetComponent<CameraComponent>();

    m_view_matrix = glm::lookAt(GetComponent<CameraComponent>().GetPosition(),
                                GetComponent<CameraComponent>().GetPosition() + camera_component.GetForward(),
                                camera_component.GetUp());
}

void SceneCamera::CalculateProjectionMatrix() {
    auto& camera_component = GetComponent<CameraComponent>();

    glm::mat4 projection_matrix = glm::mat4(1.0f);
    if (m_projection_type == ProjectionType::Perspective) {
        projection_matrix = glm::perspective(m_perspective_fov, m_aspect_ratio, m_perspective_near, m_perspective_far);
    } else if (m_projection_type == ProjectionType::Orthographic) {
        float ortho_left = -m_orthographic_size * m_aspect_ratio * 0.5f;
        float ortho_right = m_orthographic_size * m_aspect_ratio * 0.5f;
        float ortho_bottom = -m_orthographic_size * 0.5f;
        float ortho_top = m_orthographic_size * 0.5f;
        projection_matrix =
            glm::ortho(ortho_left, ortho_right, ortho_bottom, ortho_top, m_orthographic_near, m_orthographic_far);
    }

    m_projection_matrix = projection_matrix;
}

} // namespace RendererDemo
