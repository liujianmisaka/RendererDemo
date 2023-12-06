#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace RendererDemo {

class Camera {
public:
    Camera() = default;
    virtual ~Camera() = default;

    const glm::mat4 GetViewMatrix();
    const glm::mat4 GetPerspectiveProjectionMatrix();
    const glm::mat4 GetOrthographicProjectionMatrix();

    void SetPosition(const glm::vec3& position) { m_position = position; }
    void SetRotation(const glm::vec3& rotation) { m_rotation = rotation; }
    void SetFront(const glm::vec3& front) { m_front = front; }
    void SetUp(const glm::vec3& up) { m_up = up; }
    void SetRight(const glm::vec3& right) { m_right = right; }
    void SetWorldUp(const glm::vec3& world_up) { m_world_up = world_up; }
    void SetMovementSpeed(float movement_speed) { m_movement_speed = movement_speed; }
    void SetMouseSensitivity(float mouse_sensitivity) { m_mouse_sensitivity = mouse_sensitivity; }
    void SetFov(float fov) { m_fov = fov; }
    void SetAspectRatio(float aspect_ratio) { m_aspect_ratio = aspect_ratio; }
    void SetNearClip(float near_clip) { m_near_clip = near_clip; }
    void SetFarClip(float far_clip) { m_far_clip = far_clip; }

    const glm::vec3& GetPosition() const { return m_position; }
    const glm::vec3& GetRotation() const { return m_rotation; }
    const glm::vec3& GetFront() const { return m_front; }
    const glm::vec3& GetUp() const { return m_up; }
    const glm::vec3& GetRight() const { return m_right; }
    const glm::vec3& GetWorldUp() const { return m_world_up; }
    float GetMovementSpeed() const { return m_movement_speed; }
    float GetMouseSensitivity() const { return m_mouse_sensitivity; }
    float GetFov() const { return m_fov; }
    float GetAspectRatio() const { return m_aspect_ratio; }
    float GetNearClip() const { return m_near_clip; }
    float GetFarClip() const { return m_far_clip; }

private:
    void ReCalculateRotation();

private:
    // camera Attributes
    glm::vec3 m_position{0.0f, 0.0f, 0.0f};
    glm::vec3 m_front{0.0f, 0.0f, -1.0f};
    glm::vec3 m_up{0.0f, 1.0f, 0.0f};
    glm::vec3 m_right = glm::normalize(glm::cross(m_front, m_up));
    glm::vec3 m_world_up{0.0f, 1.0f, 0.0f};
    // euler Angles
    glm::vec3 m_rotation{0.0f, -90.0f, 0.0f}; // yaw, pitch, roll
    // camera options
    float m_movement_speed = 2.5f;
    float m_rotation_speed = 0.1f;
    float m_mouse_sensitivity = 0.1f;
    float m_fov = 45.0f;
    float m_aspect_ratio = 1.0f;
    float m_near_clip = 0.1f;
    float m_far_clip = 1000.0f;
};

} // namespace RendererDemo
