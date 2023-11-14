#pragma once

#include "Runtime/Function/Framework/Component/Component.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace RendererDemo {

enum class CameraMod {
    // clang-format off
	None = 0, 
	Free, FirstPerson, ThirdPerson
    // clang-format on
};

class CameraComponent : public Component {
public:
    CameraComponent() = default;
    CameraComponent(float fov, float aspectRatio, float nearClip, float farClip);
    ~CameraComponent() = default;

    glm::mat4 GetViewProjection() {
        return m_projection_matrix * m_view_matrix;
    }

    glm::mat4 GetViewMatrix() {
        return m_view_matrix;
    }

    glm::mat4 GetProjectionMatrix() {
        return m_projection_matrix;
    }

    glm::vec3 GetPosition() {
        return m_position;
    }

    glm::vec3 GetForward() {
        return m_forward;
    }

    glm::vec3 GetUp() {
        return m_up;
    }

    void SetPosition(const glm::vec3& position) {
        m_position = position;
        UpdateViewMatrix();
    }

    void SetForward(const glm::vec3& forward) {
        m_forward = forward;
        UpdateViewMatrix();
    }

    void SetUp(const glm::vec3& up) {
        m_up = up;
        UpdateViewMatrix();
    }

    void SetCameraMod(CameraMod cameraMod) {
        m_camera_mod = cameraMod;
    }

    CameraMod GetCameraMod() {
        return m_camera_mod;
    }

    void Tick(float ts){};

private:
    void UpdateViewMatrix();
    void UpdateProjectionMatrix();

private:
    // Original Camrea Parameter
    float m_fov{45.0f};         // Field of View
    float m_aspect_ratio{1.0f}; // height / width
    float m_near_clip{0.1f};
    float m_far_clip{100.0f};
    glm::vec3 m_position{0.0f, 0.0f, 0.0f};
    glm::vec3 m_up{0.0f, 1.0f, 0.0f};
    glm::vec3 m_forward{0.0f, 0.0f, -1.0f};

    CameraMod m_camera_mod = CameraMod::Free;

    // Generated Parameter
    glm::mat4 m_view_matrix;
    glm::mat4 m_projection_matrix;
};

} // namespace RendererDemo
