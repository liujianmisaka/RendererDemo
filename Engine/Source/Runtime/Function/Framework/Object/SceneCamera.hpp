#pragma once

#include <entt/entity/fwd.hpp>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include "Runtime/Function/Framework/Component/Camera/CameraComponent.hpp"
#include "Runtime/Function/Framework/Object/Object.hpp"

namespace RendererDemo {

enum class ProjectionType { Perspective = 0, Orthographic = 1 };

class SceneCamera : public Object {
public:
    SceneCamera() = default;
    SceneCamera(entt::entity entity, std::shared_ptr<entt::registry> entt_register);
    SceneCamera(const CameraComponent& camera_component) {} // TODO: Init camera from camera component
    virtual ~SceneCamera() override = default;

    virtual void Tick(float ts) override;

    // Getter and Setter
    ProjectionType GetProjectionType() const { return m_projection_type; }
    void SetProjectionType(ProjectionType projection_type) { m_projection_type = projection_type; }

    glm::vec3 GetPosition() const { return m_position; }
    glm::vec3 GetUp() const { return m_up; }
    glm::vec3 GetForward() const { return m_forward; }
    void SetPosition(const glm::vec3& position) {
        m_position = position;
        GetComponent<CameraComponent>().SetPosition(position);
    }
    void SetUp(const glm::vec3& up) {
        m_up = up;
        GetComponent<CameraComponent>().SetUp(up);
    }
    void SetForward(const glm::vec3& forward) {
        m_forward = forward;
        GetComponent<CameraComponent>().SetForward(forward);
    }

    float GetPerspectiveFOV() const { return m_perspective_fov; }
    float GetPerspectiveNear() const { return m_perspective_near; }
    float GetPerspectiveFar() const { return m_perspective_far; }
    void SetPerspectiveFOV(float fov) {
        m_perspective_fov = fov;
        GetComponent<CameraComponent>().SetFov(fov);
    }
    void SetPerspectiveNear(float near) {
        m_perspective_near = near;
        GetComponent<CameraComponent>().SetNearClip(near);
    }
    void SetPerspectiveFar(float far) {
        m_perspective_far = far;
        GetComponent<CameraComponent>().SetFarClip(far);
    }

    float GetOrthographicSize() const { return m_orthographic_size; }
    float GetOrthographicNear() const { return m_orthographic_near; }
    float GetOrthographicFar() const { return m_orthographic_far; }
    void SetOrthographicSize(float size) {
        m_orthographic_size = size;
        GetComponent<CameraComponent>().SetFov(size);
    }
    void SetOrthographicNear(float near) {
        m_orthographic_near = near;
        GetComponent<CameraComponent>().SetNearClip(near);
    }
    void SetOrthographicFar(float far) {
        m_orthographic_far = far;
        GetComponent<CameraComponent>().SetFarClip(far);
    }

    void SetViewportSize(float width, float height) {
        m_aspect_ratio = width / height;
        GetComponent<CameraComponent>().SetAspectRatio(m_aspect_ratio);
    }

    const glm::mat4& GetViewMatrix() const { return m_view_matrix; }
    const glm::mat4& GetProjection() const { return m_projection_matrix; }
    glm::mat4 GetViewProjection() const { return m_view_projection_matrix; }

private:
    void CalculateViewMatrix();
    void CalculateProjectionMatrix();

private:
    // Parameters used in editor to changed camera
    ProjectionType m_projection_type = ProjectionType::Perspective;

    glm::vec3 m_position{0.0f, 0.0f, 0.0f};
    glm::vec3 m_up{0.0f, 1.0f, 0.0f};
    glm::vec3 m_forward{0.0f, 0.0f, -1.0f};

    float m_aspect_ratio = 1.0f;

    float m_perspective_fov = glm::radians(45.0f);
    float m_perspective_near = 0.1f;
    float m_perspective_far = 100.0f;

    float m_orthographic_size = 10.0f;
    float m_orthographic_near = -1.0f;
    float m_orthographic_far = 1.0f;

    glm::mat4 m_view_matrix = glm::mat4(1.0f);
    glm::mat4 m_projection_matrix = glm::mat4(1.0f);
    glm::mat4 m_view_projection_matrix = glm::mat4(1.0f);
};

} // namespace RendererDemo
