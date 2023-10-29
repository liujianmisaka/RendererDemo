#pragma once

namespace RendererDemo {

class RHI {
public:
    RHI() = default;
    virtual ~RHI() = default;

	virtual void Initialize();
};

} // namespace RendererDemo
