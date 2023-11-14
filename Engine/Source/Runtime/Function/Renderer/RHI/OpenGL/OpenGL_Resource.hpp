#pragma once

// This types are only used in OpenGLAPI and OpenGLRHI.
// To store the OpenGL resource, when created by raw create info.
// The rule is:
//     1.The OpenGLRHI use raw create info and OpenGLAPI.
//     2.The OpenGLAPI actually create the OpenGL resource, using both raw create info and opengl create info.
//     3.The OpenGLRHI store the OpenGL resource, using opengl create info.

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdint>
#include <vector>

namespace RendererDemo {

enum class OpenGLBufferType { VertexBuffer, IndexBuffer, UniformBuffer };

/* -------------------------------------------------------------------------- */
/*                                OpenGLBuffer                                */
/* -------------------------------------------------------------------------- */
struct OpenGLBuffer {
    OpenGLBufferType buffer_type;
    uint32_t buffer_id;
    uint32_t buffer_byte_size;    // the byte size of this buffer
    uint32_t buffer_unit_size;    // the size of a single element in this buffer
                                  // for index buffer, this is the size of a single index
                                  // for uniform buffer, this is the size of a single uniform
                                  // for vertex buffer, this is the size of a single vertex
    uint32_t buffer_number_count; // for index buffer, this is the number of indices;
                                  // for uniform buffer, this is the number of uniforms
                                  // for vertex buffer, this is the number of vertices
};

/* -------------------------------------------------------------------------- */
/*                          OpenGLVertexBufferLayout                          */
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
/*                              OpenGLVertexArray                             */
/* -------------------------------------------------------------------------- */
struct OpenGLVertexArrayCreateInfo {
    OpenGLVertexBufferLayout vertex_buffer_layout;
    OpenGLBuffer vertex_buffer;
    OpenGLBuffer index_buffer;
};

struct OpenGLVertexArray {
    uint32_t vertex_array_id;
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

/* -------------------------------------------------------------------------- */
/*                       OpenGLIndexDrawBufferCreateInfo                      */
/* -------------------------------------------------------------------------- */
struct OpenGLIndexDrawBufferCreateInfo {
    OpenGLBuffer index_buffer;
    OpenGLProgram program;
    OpenGLVertexArray vertex_array;
    GLenum draw_mode; // GL_TRIANGLES, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, etc.
};

/* -------------------------------------------------------------------------- */
/*                            OpenGLIndexDrawBuffer                           */
/* -------------------------------------------------------------------------- */
struct OpenGLIndexDrawBuffer {
    GLenum draw_mode;      // GL_TRIANGLES, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, etc.
    uint32_t index_count;  // the number of indices
    GLenum index_type;     // GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, GL_UNSIGNED_INT
    uint64_t index_offset; // the offset of the first index in the index buffer
    uint32_t vertex_array_id;
    uint32_t program_id;
};

} // namespace RendererDemo
