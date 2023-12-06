#include "Runtime/Function/Framework/Component/Camera/CameraComponent.hpp"

namespace RendererDemo {

void CameraComponent::Tick(float ts) {
    if (m_dirty) {
        m_camera.ReCalculateRotation();
        m_dirty = false;
    }
}

} // namespace RendererDemo
