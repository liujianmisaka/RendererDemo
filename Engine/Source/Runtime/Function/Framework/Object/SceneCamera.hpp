#pragma once

#include <entt/entity/fwd.hpp>
#include <glm/glm.hpp>
#include "Runtime/Function/Framework/Object/Object.hpp"

namespace RendererDemo {

class SceneCamera : public Object {
public:
    SceneCamera() = default;
    SceneCamera(entt::entity entity, std::shared_ptr<entt::registry> entt_register) : Object(entity, entt_register) {}
    virtual ~SceneCamera() = default;
};

} // namespace RendererDemo
