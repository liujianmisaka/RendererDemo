#include "Runtime/Function/Renderer/RHI/OpenGL/OpenGLAPI.hpp"
#include <cstdint>
#include <iostream>

#include "Runtime/Function/Renderer/RHI/RHI_PreData.hpp"
#include "Runtime/Function/Renderer/RHI/RHI_Struct.hpp"
#include "Runtime/Function/Renderer/RHI/RHI_Types.hpp"

namespace RendererDemo {

uint32_t OpenGLAPI::CreateVertexBuffer(uint32_t buffer_size, const void* buffer_data) {
    // Generate a new buffer in gpu and get the buffer id
    GLuint vertex_buffer_id;
    glGenBuffers(1, &vertex_buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
    glBufferData(GL_ARRAY_BUFFER, buffer_size, buffer_data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Must unbind the buffer after use
    return vertex_buffer_id;
}

uint32_t OpenGLAPI::CreateIndexBuffer(uint32_t buffer_size, const void* buffer_data) {
    // Generate a new buffer in gpu and get the buffer id
    GLuint index_buffer_id;
    glGenBuffers(1, &index_buffer_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer_size, buffer_data, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Must unbind the buffer after use
    return index_buffer_id;
}

uint32_t OpenGLAPI::CreateUniformBuffer(uint32_t buffer_size, const void* buffer_data) {
    // Generate a new buffer in gpu and get the buffer id
    GLuint uniform_buffer_id;
    glGenBuffers(1, &uniform_buffer_id);
    glBindBuffer(GL_UNIFORM_BUFFER, uniform_buffer_id);
    glBufferData(GL_UNIFORM_BUFFER, buffer_size, buffer_data, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0); // Must unbind the buffer after use
    return uniform_buffer_id;
}

void OpenGLAPI::UnloadUniformBuffer(uint32_t buffer_id) {
    glDeleteBuffers(1, &buffer_id);
}

RHIVertexLayout OpenGLAPI::CreateVertexLayout(std::vector<RHIElementType> info) {
    RHIVertexLayout vertex_layout;
    vertex_layout.stride = 0;
    for (auto elem_type : info) {
        auto element_info = KPredefinedVertexAttributeMap.find(elem_type)->second;
        RHIVertexAttribute attribute;
        attribute.location = vertex_layout.attributes.size();
        attribute.count = element_info.count;
        attribute.data_type = element_info.data_type;
        attribute.normalized = element_info.normalized;
        attribute.offset = vertex_layout.stride;
        vertex_layout.stride += element_info.count * element_info.unit_size;
        vertex_layout.attributes.push_back(attribute);
    }
    return vertex_layout;
}

uint32_t OpenGLAPI::CreateVertexArray(uint32_t vertex_buffer_id, uint32_t index_buffer_id, RHIVertexLayout layout) {
    // Generate a new vertex array in gpu and get the vertex array id
    GLuint vertex_array_id;
    glGenVertexArrays(1, &vertex_array_id);
    glBindVertexArray(vertex_array_id);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_id);
    for (auto attribute : layout.attributes) {
        glEnableVertexAttribArray(attribute.location);
        GLenum data_type = GetOpenGLDataTypeFromRHIDataType(attribute.data_type);
        glVertexAttribPointer(attribute.location, attribute.count, data_type, attribute.normalized, layout.stride,
                              (void*)attribute.offset);
    }
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    return vertex_array_id;
}

uint32_t OpenGLAPI::CreateVertexShader(const char* shader_source) {
    GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader_id, 1, &shader_source, nullptr);
    glCompileShader(vertex_shader_id);
    GLint success;
    glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(vertex_shader_id, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    return vertex_shader_id;
}

uint32_t OpenGLAPI::CreateFragmentShader(const char* shader_source) {
    GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader_id, 1, &shader_source, nullptr);
    glCompileShader(fragment_shader_id);
    GLint success;
    glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(fragment_shader_id, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    return fragment_shader_id;
}

uint32_t OpenGLAPI::CreateProgram(uint32_t vertex_shader_id, uint32_t fragment_shader_id) {
    GLuint program_id = glCreateProgram();
    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);
    glLinkProgram(program_id);
    GLint success;
    glGetProgramiv(program_id, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program_id, 512, nullptr, infoLog);
        std::cout << "ERROR::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
    }
    return program_id;
}

/* -------------------------------------------------------------------------- */
/*                              Private Functions                             */
/* -------------------------------------------------------------------------- */

GLenum OpenGLAPI::GetOpenGLDataTypeFromRHIDataType(RHIDataType type) {
    switch (type) {
        case RHIDataType::Float: return GL_FLOAT;
        case RHIDataType::Int: return GL_INT;
        case RHIDataType::UInt: return GL_UNSIGNED_INT;
        case RHIDataType::Char: return GL_BYTE;
        case RHIDataType::UChar: return GL_UNSIGNED_BYTE;
        case RHIDataType::Int8: return GL_BYTE;
        case RHIDataType::UInt8: return GL_UNSIGNED_BYTE;
        case RHIDataType::Int16: return GL_SHORT;
        case RHIDataType::UInt16: return GL_UNSIGNED_SHORT;
        case RHIDataType::Boolean: return GL_BOOL;
        default: return 0;
    }
}

} // namespace RendererDemo
