#pragma once

#include <memory>

#include "Runtime/Function/Renderer/RHI/Interface/Buffer.hpp"
#include "Runtime/Function/Renderer/RHI/Interface/Layout.hpp"
#include "Runtime/Function/Renderer/RHI/Interface/Shader.hpp"

namespace RendererDemo {

class WindowSystem;

struct RHIInitInfo {
    std::shared_ptr<WindowSystem> window_system;
};

class RHI {
public:
    virtual ~RHI() = default;

    virtual void Initialize(RHIInitInfo rhi_init_info) = 0;

    virtual void CreateBuffer(BufferInfo buffer_info) = 0;
    // virtual void CreateBuffer(BufferType buffer_type, uint32_t buffer_size, void* buffer_data) = 0;
    virtual void CreateVertexLayout(RawVertexLayout raw_vertex_buffer_layout) = 0;
	virtual void CreateVertexArray() = 0;
    virtual void CreateShader(ShaderInfo shader_info) = 0;
    virtual void CreateProgram() = 0;

	virtual void DrawExample() {}

    virtual void Tick() = 0;
};

} // namespace RendererDemo
