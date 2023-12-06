#include "Runtime/Core/UUID/UUID.hpp"
#include "Runtime/Function/Framework/Component/Component.hpp"
#include "Runtime/Function/Framework/Component/Render/IndexDrawBufferComponent.hpp"
#include "Runtime/Function/Framework/Component/State/StateComponent.hpp"

namespace RendererDemo {

class IdComponent : public Component {
public:
    IdComponent(std::shared_ptr<entt::registry> registry, entt::entity entity, UUID id = {})
        : Component(registry, entity), m_Id(id) {}
    virtual ~IdComponent() = default;
    IdComponent(const IdComponent &) = default;

    UUID GetId() { return m_Id; }

private:
    UUID m_Id{};
};

class TagComponent : public Component {
public:
    TagComponent(std::shared_ptr<entt::registry> registry, entt::entity entity, std::string tag = "Object")
        : Component(registry, entity), m_Tag(tag) {}
    virtual ~TagComponent() = default;
    TagComponent(const TagComponent &) = default;

    void SetTag(std::string tag) { m_Tag = tag; }
    std::string GetTag() { return m_Tag; }

private:
    std::string m_Tag;
};

class SquaComponent : public Component {
public:
    SquaComponent(std::shared_ptr<entt::registry> registry, entt::entity entity) : Component(registry, entity) {}
    virtual ~SquaComponent() = default;
    SquaComponent(const SquaComponent &) = default;

    virtual void Tick(float ts) override {
        auto state_component = ObjectGetComponent<StateComponent>();
        if (!ObjectHasComponent<IndexDrawBufferComponent>() && ObjectGetComponent<StateComponent>().IsRendereable()) {
            auto &draw_component = ObjectAddComponent<IndexDrawBufferComponent>();
            draw_component.GenerateIndexDrawBuffer(); // Use default vertex data
        }
    }

    float GetSqua() { return m_Squa; }

private:
    float m_Squa = 0.0f;
};

} // namespace RendererDemo
