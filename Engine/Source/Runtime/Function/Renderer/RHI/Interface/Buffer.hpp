#pragma once

#include <cstdint>
#include <utility>

namespace RendererDemo {

enum class BufferType { VertexBuffer, IndexBuffer, UniformBuffer };

struct BufferInfo {
    BufferType buffer_type;
    uint32_t buffer_size;
    void* buffer_data;

    BufferInfo&& SetBufferType(BufferType type) {
        buffer_type = type;
        return std::move(*this);
    }

    BufferInfo&& SetBufferSize(uint32_t size) {
        buffer_size = size;
        return std::move(*this);
    }

    BufferInfo&& SetBufferData(void* data) {
        buffer_data = data;
        return std::move(*this);
    }
};

} // namespace RendererDemo
