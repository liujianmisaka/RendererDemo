#include "Runtime/Function/Framework/Scene/Scene.hpp"
#include <entt/entity/fwd.hpp>

namespace RendererDemo {

Object::Object(entt::entity entity, std::shared_ptr<Scene> scene) : m_entity(entity) {
    m_registry = scene->GetRegister();
}

} // namespace RendererDemo
