#include "Runtime/Function/Framework/Component/Camera/CameraComponent.hpp"

namespace RendererDemo {

CameraComponent::CameraComponent(float fov, float aspectRatio, float nearClip, float farClip)
    : m_fov(fov), m_aspect_ratio(aspectRatio), m_near_clip(nearClip), m_far_clip(farClip) {}

} // namespace RendererDemo
