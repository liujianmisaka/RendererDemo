#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdint>
#include <vector>

#include "runtime/core/Base/Types.hpp"

namespace RendererDemo {

enum class OpenGLLayoutType { VertexBufferLayout, UniformBufferLayout };

// TODO: change to use api-independent type
// this is the layout of a single element in a buffer
// a element should be a single type, like int, and the elemen type should be like vec3
struct ElementInfo {
    uint32_t index;          // the location of this element in the buffer(both in struct and in shader)
    uint32_t size;           // the size of this element, like 3 for vec3, 1 for int
    MisakaTargetType type;   // the type of this element, use MisakaTypes abstract type
    bool normalized = false; // whether the data should be normalized or not
    uint32_t offset = 0;     // the start byte of this element(like glm::vec2) in a vertex buffer
};

class RawVertexLayout {
public:
    RawVertexLayout() = default;
    virtual ~RawVertexLayout() = default;

    // you should give the element info of index, size, type
    RawVertexLayout&& AddElementInfo(ElementInfo element_info);
    RawVertexLayout&& SetVertexByteSize(uint32_t vertex_byte_size);

    std::vector<ElementInfo> GetElementInfoVector();
	uint32_t GetVertexByteSize();

private:
    uint32_t SizeofType(MisakaTargetType type);

private:
    std::vector<ElementInfo> m_element_info_vector;
    uint32_t m_vertex_byte_size = 0; // the total byte size of a single vertex
};

} // namespace RendererDemo
