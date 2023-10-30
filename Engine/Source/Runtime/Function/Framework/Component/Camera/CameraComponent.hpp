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

class CameraComponent : public Componnet {
public:
    CameraComponent(float fov, float aspectRatio, float nearClip, float farClip);

    void Tick(float ts);

private:
    void UpdateViewMatrix();
    void UpdateProjectionMatrix();

private:
    // Original Camrea Parameter
    float m_fov{45.0f};        // Field of View
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
