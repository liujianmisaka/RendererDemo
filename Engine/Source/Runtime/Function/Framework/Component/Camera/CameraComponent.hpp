#pragma once

#include "Runtime/Function/Framework/Component/Camera/camera.hpp"
#include "Runtime/Function/Framework/Component/Component.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace RendererDemo {

class CameraComponent : public Component {
public:
    CameraComponent(std::shared_ptr<entt::registry> registry, entt::entity entity) : Component(registry, entity) {}
    virtual ~CameraComponent() = default;
    virtual void Tick(float ts) override;

    Camera& GetCamera() { return m_camera; }
    const Camera& GetCamera() const { return m_camera; }

private:
    Camera m_camera{};
};

} // namespace RendererDemo
