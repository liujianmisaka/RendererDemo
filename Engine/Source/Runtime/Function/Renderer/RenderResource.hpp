#pragma once

#include "Runtime/Function/Renderer/RHI/RHI_Struct.hpp"

namespace RendererDemo {

struct StorageBuffer {
    RHIBuffer* global_buffer;
};

struct GloablRenderResource {
    StorageBuffer storage_buffer;
};

class RenderResource {
public:
    RenderResource() = default;
    ~RenderResource() = default;

private:
};

} // namespace RendererDemo
