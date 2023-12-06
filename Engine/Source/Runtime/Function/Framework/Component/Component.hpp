#pragma once

#include <string>
#include "Runtime/Core/UUID/UUID.hpp"

namespace RendererDemo {

class Component {
public:
    Component() = default;
    virtual ~Component() = default;

    virtual void Tick(float ts) {}
};

class IdComponent : public Component {
public:
    IdComponent() = default;
    virtual ~IdComponent() = default;
    IdComponent(UUID uuid) : m_Id(uuid) {}
    IdComponent(const IdComponent &) = default;

    UUID GetId() { return m_Id; }

private:
    UUID m_Id{};
};

class TagComponent : public Component {
public:
    TagComponent() = default;
    virtual ~TagComponent() = default;
    TagComponent(const TagComponent &) = default;
    TagComponent(std::string tag) : m_Tag(std::move(tag)) {}

    std::string GetTag() { return m_Tag; }

private:
    std::string m_Tag;
};

class SquaComponent : public Component {
public:
    SquaComponent() = default;
    virtual ~SquaComponent() = default;
    SquaComponent(const SquaComponent &) = default;
    SquaComponent(float squa) : m_Squa(squa) {}

    float GetSqua() { return m_Squa; }

private:
    float m_Squa = 0.0f;
};

} // namespace RendererDemo
