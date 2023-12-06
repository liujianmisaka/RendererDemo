#include "Runtime/Function/Framework/Object/Object.hpp"
#include <entt/entity/fwd.hpp>
#include <entt/entity/registry.hpp>
#include "Runtime/Function/Framework/Component/Camera/CameraComponent.hpp"
#include "Runtime/Function/Framework/Component/Mesh/MeshComponent.hpp"
#include "Runtime/Function/Framework/Component/Render/IndexDrawBufferComponent.hpp"
#include "Runtime/Function/Framework/Component/Transform/TransformComponent.hpp"
#include "Runtime/Function/Framework/Component/MiniComponents.hpp"

namespace RendererDemo {

Object::Object(entt::entity entity, std::shared_ptr<entt::registry> entt_register)
    : m_entity(entity), m_registry(entt_register) {}

void Object::Tick(float ts) {
    if (this->HasComponent<TransformComponent>()) {
        this->GetComponent<TransformComponent>().Tick(ts);
    }

    if (this->HasComponent<CameraComponent>()) {
        this->GetComponent<CameraComponent>().Tick(ts);
    }

    if (this->HasComponent<MeshComponent>()) {
        this->GetComponent<MeshComponent>().Tick(ts);
    }

    if (this->HasComponent<SquaComponent>()) {
        this->GetComponent<SquaComponent>().Tick(ts);
    }
}

} // namespace RendererDemo
