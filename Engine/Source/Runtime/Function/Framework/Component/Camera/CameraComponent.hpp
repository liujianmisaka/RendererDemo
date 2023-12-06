#pragma once

#include "Runtime/Function/Framework/Component/Component.hpp"
#include <glm/fwd.hpp>
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
    virtual ~CameraComponent() = default;

    // Setter and Getter
    void SetFov(float fov) { m_fov = fov; }
    void SetAspectRatio(float aspect_ratio) { m_aspect_ratio = aspect_ratio; }
    void SetNearClip(float near_clip) { m_near_clip = near_clip; }
    void SetFarClip(float far_clip) { m_far_clip = far_clip; }
    const float GetFov() const { return m_fov; }
    const float GetAspectRatio() const { return m_aspect_ratio; }
    const float GetNearClip() const { return m_near_clip; }
    const float GetFarClip() const { return m_far_clip; }

    void SetPosition(const glm::vec3& position) { m_position = position; }
    void SetForward(const glm::vec3& forward) { m_forward = forward; }
    void SetUp(const glm::vec3& up) { m_up = up; }
    void SetCameraMod(CameraMod camera_mod) { m_camera_mod = camera_mod; }
    const glm::vec3& GetPosition() const { return m_position; }
    const glm::vec3& GetForward() const { return m_forward; }
    const glm::vec3& GetUp() const { return m_up; }
    CameraMod GetCameraMod() const { return m_camera_mod; }

private:
    // Init Camrea Parameters
    float m_fov{45.0f};         // Field of View
    float m_aspect_ratio{1.0f}; // height / width
    float m_near_clip{0.1f};
    float m_far_clip{100.0f};

    // Camera State Parameters
    glm::vec3 m_position{0.0f, 0.0f, 0.0f};
    glm::vec3 m_up{0.0f, 1.0f, 0.0f};
    glm::vec3 m_forward{0.0f, 0.0f, -1.0f};
    CameraMod m_camera_mod = CameraMod::Free;
};

} // namespace RendererDemo
