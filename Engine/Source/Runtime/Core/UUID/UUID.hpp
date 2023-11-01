#pragma once

#include <xhash>

namespace RendererDemo {

class UUID {
public:
    UUID();
    UUID(uint64_t uuid);
    UUID(const UUID&) = default;

    operator uint64_t() const { return m_UUID; }

private:
    uint64_t m_UUID;
};

} // namespace RendererDemo

namespace std {

template <>
struct hash<RendererDemo::UUID> {
    std::size_t operator()(const RendererDemo::UUID& uuid) const noexcept { return hash<uint64_t>()((uint64_t)uuid); }
};

} // namespace std
