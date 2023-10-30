#pragma once

#include <memory>

namespace RendererDemo {

class WindowSystem;

struct RHIInitInfo {
    std::shared_ptr<WindowSystem> window_system;
};

class RHI {
public:
    virtual ~RHI() = default;

    virtual void Initialize(RHIInitInfo rhi_init_info) = 0;

    virtual void Render() = 0;
};

} // namespace RendererDemo
