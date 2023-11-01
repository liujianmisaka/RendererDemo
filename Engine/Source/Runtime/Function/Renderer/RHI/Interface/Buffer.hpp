#pragma once

#include <cstdint>
#include <utility>

#include "runtime/core/Base/Types.hpp"

namespace RendererDemo {

enum class BufferType { VertexBuffer, IndexBuffer, UniformBuffer };

class OpenGLAPI;
class OpenGLRHI;

class BufferCreateInfo {
    friend class RendererDemo::OpenGLAPI;
    friend class RendererDemo::OpenGLRHI;

public:
    BufferCreateInfo() = default;
    ~BufferCreateInfo() = default;

    // vertex buffer, index buffer, uniform buffer
    BufferCreateInfo&& SetBufferType(BufferType type) {
        m_buffer_type = type;
        return std::move(*this);
    }

    // buffer data pointer
    BufferCreateInfo&& SetBufferData(void* data) {
        m_buffer_data = data;
        return std::move(*this);
    }

    // buffer data type, use MisakaDataType
    BufferCreateInfo&& SetBufferDataType(MisakaDataType data_type) {
        m_buffer_data_type = data_type;
        return std::move(*this);
    }

    // buffer size in bytes
    BufferCreateInfo&& SetBufferByteSize(uint32_t size) {
        m_buffer_byte_size = size;
        return std::move(*this);
    }

private:
    BufferType m_buffer_type;
    uint32_t m_buffer_byte_size;
    void* m_buffer_data;
    MisakaDataType m_buffer_data_type;
};

} // namespace RendererDemo
