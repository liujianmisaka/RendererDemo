#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdint>
#include <vector>

namespace RendererDemo {

enum class OpenGLBufferType { VertexBuffer, IndexBuffer, UniformBuffer };

/* -------------------------------------------------------------------------- */
/*                             OpenGLBuffer Struct                            */
/* -------------------------------------------------------------------------- */
struct OpenGLBuffer {
    uint32_t buffer_id;
    uint32_t buffer_byte_size; // the size of this buffer in bytes
    uint32_t index_count;      // only for index buffer, the size of this buffer in elements
    OpenGLBufferType buffer_type;
};

/* -------------------------------------------------------------------------- */
/*                       OpenGLVertexBufferLayout Struct                      */
/* -------------------------------------------------------------------------- */
struct OpenGLElementInfo {
    uint32_t index;          // the location of this element in the buffer(both in struct and in shader)
    uint32_t size;           // the size of this element, like 3 for vec3, 1 for int
    GLenum type;             // the type of this element, like GL_FLOAT, GL_INT, etc.
    bool normalized = false; // whether the data should be normalized or not
    uint32_t stride = 0;     // the total size of a single vertex
    uint64_t offset = 0;     // the start byte of this element(like glm::vec2) in a vertex buffer
};

struct OpenGLVertexBufferLayout {
    std::vector<OpenGLElementInfo> element_info_vector;
};

/* -------------------------------------------------------------------------- */
/*                                OpenGLShader                                */
/* -------------------------------------------------------------------------- */
enum class OpenGLShaderType { VertexShader, FragmentShader };

struct OpenGLShader {
    uint32_t shader_id;
    OpenGLShaderType shader_type;
};

/* -------------------------------------------------------------------------- */
/*                                OpenGLProgram                               */
/* -------------------------------------------------------------------------- */
struct OpenGLProgram {
    uint32_t program_id;
};

} // namespace RendererDemo
