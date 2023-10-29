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
    float m_Fov{45.0f};        // Field of View
    float m_AspectRatio{1.0f}; // height / width
    float m_NearClip{0.1f};
    float m_FarClip{100.0f};
    glm::vec3 m_Position{0.0f, 0.0f, 0.0f};
    glm::vec3 m_Up{0.0f, 1.0f, 0.0f};
    glm::vec3 m_Forward{0.0f, 0.0f, -1.0f};

    CameraMod m_CameraMod = CameraMod::Free;

    // Generated Parameter
    glm::mat4 m_ViewMatrix;
    glm::mat4 m_ProjectionMatrix;
};

} // namespace RendererDemo
