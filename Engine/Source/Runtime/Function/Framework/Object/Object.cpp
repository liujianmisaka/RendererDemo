#include "Runtime/Function/Framework/Object/Object.hpp"

namespace RendererDemo {

Object::Object(entt::entity entity, std::shared_ptr<entt::registry> entt_register)
    : m_entity(entity), m_registry(entt_register) {}

} // namespace RendererDemo
