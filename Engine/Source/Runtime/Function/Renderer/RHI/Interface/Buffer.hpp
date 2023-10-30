#pragma once

namespace RendererDemo {

// data size
class VertexBuffer {
public:
    virtual ~VertexBuffer() = default;
};

// data size
class IndexBuffer {
public:
    virtual ~IndexBuffer() = default;
};

// {offset, location}
class BufferLayout {
public:
    virtual ~BufferLayout() = default;
};

} // namespace RendererDemo
