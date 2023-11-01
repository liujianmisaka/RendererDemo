#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdint>
#include <vector>

#include "runtime/core/Base/Types.hpp"

namespace RendererDemo {

class OpenGLAPI;
class OpenGLRHI;

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

class VertexLayoutCreateInfo {
    friend class RendererDemo::OpenGLAPI;
    friend class RendererDemo::OpenGLRHI;

public:
    VertexLayoutCreateInfo() = default;
    virtual ~VertexLayoutCreateInfo() = default;

    // you should give the element info of index, size, type at least in order.
    VertexLayoutCreateInfo&& AddElementInfo(ElementInfo element_info) {
        // Calculate the offset of the new element
        if (!m_element_info_vector.empty()) {
            const ElementInfo& lastElement = m_element_info_vector.back();
            element_info.offset = lastElement.offset + lastElement.size * SizeofType(lastElement.type);
        }

        // Add the new element to the vector
        m_element_info_vector.push_back(element_info);

        return std::move(*this);
    }

    VertexLayoutCreateInfo&& SetVertexByteSize(uint32_t vertex_byte_size) {
        m_vertex_byte_size = vertex_byte_size;
        return std::move(*this);
    }

private:
    uint32_t SizeofType(MisakaTargetType type) {
        switch (type) {
            case MisakaTargetType::Float: return sizeof(GLfloat);
            case MisakaTargetType::Int: return sizeof(GLint);
            case MisakaTargetType::UInt: return sizeof(GLuint);
            case MisakaTargetType::Boolean: return sizeof(GLboolean);
            case MisakaTargetType::Double: return sizeof(GLdouble);
            case MisakaTargetType::Int8: return sizeof(GLbyte);
            case MisakaTargetType::UInt8: return sizeof(GLubyte);
            case MisakaTargetType::Int16: return sizeof(GLshort);
            case MisakaTargetType::UInt16: return sizeof(GLushort);
            default: return 0;
        }
    }

private:
    std::vector<ElementInfo> m_element_info_vector;
    uint32_t m_vertex_byte_size = 0; // the total byte size of a single vertex
};

} // namespace RendererDemo
