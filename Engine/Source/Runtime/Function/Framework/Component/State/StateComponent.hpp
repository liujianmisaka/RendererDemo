#pragma once

#include "Runtime/Function/Framework/Component/Component.hpp"
namespace RendererDemo {

enum class ObjectState : uint32_t {
    kNone = 0,
    KRendereable = 1 << 0,
};

class StateComponent : public Component {
public:
    StateComponent(std::shared_ptr<entt::registry> registry, entt::entity entity,
                   ObjectState state = ObjectState::kNone)
        : Component(registry, entity), m_state(static_cast<uint32_t>(state)) {}
    virtual ~StateComponent() = default;

    void SetState(ObjectState state) { m_state |= static_cast<uint32_t>(state); }
    const uint32_t& GetState() const { return m_state; }

    bool IsRendereable() { return m_state & static_cast<uint32_t>(ObjectState::KRendereable); }

private:
    uint32_t m_state = 0;
};
} // namespace RendererDemo
