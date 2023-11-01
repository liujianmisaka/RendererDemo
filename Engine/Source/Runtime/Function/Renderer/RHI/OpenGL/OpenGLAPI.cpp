#include "Runtime/Function/Renderer/RHI/OpenGL/OpenGLAPI.hpp"
#include "Runtime/Function/Renderer/RHI/Interface/Buffer.hpp"
#include "Runtime/Function/Renderer/RHI/OpenGL/OpenGL_Resource.hpp"

#include <iostream>

namespace RendererDemo {

OpenGLBuffer OpenGLAPI::CreateBuffer(BufferInfo buffer_info) {
    OpenGLBuffer opengl_buffer;

    opengl_buffer.buffer_byte_size = buffer_info.buffer_size;

    // Generate a new buffer in gpu and get the buffer id
    glGenBuffers(1, &opengl_buffer.buffer_id);

    // Determine the buffer target based on the buffer type
    GLenum buffer_target;
    switch (buffer_info.buffer_type) {
        case BufferType::VertexBuffer:
            buffer_target = GL_ARRAY_BUFFER;
            opengl_buffer.buffer_type = OpenGLBufferType::VertexBuffer;
			opengl_buffer.index_count = 0;
            break;
        case BufferType::IndexBuffer:
            buffer_target = GL_ELEMENT_ARRAY_BUFFER;
            opengl_buffer.buffer_type = OpenGLBufferType::IndexBuffer;
			opengl_buffer.index_count = buffer_info.buffer_size / sizeof(unsigned int);
            break;
        case BufferType::UniformBuffer:
            buffer_target = GL_UNIFORM_BUFFER;
            opengl_buffer.buffer_type = OpenGLBufferType::UniformBuffer;
			opengl_buffer.index_count = 0;
            break;
    }

    // bind the gpu buffer memory to the buffer type and map the buffer data from cpu to gpu
    glBindBuffer(buffer_target, opengl_buffer.buffer_id);
    glBufferData(buffer_target, buffer_info.buffer_size, buffer_info.buffer_data, GL_STATIC_DRAW);

    return opengl_buffer;
}

OpenGLVertexBufferLayout OpenGLAPI::CreateVertexLayout(RawVertexLayout raw_vertex_layout) {
    OpenGLVertexBufferLayout opengl_buffer_layout;
    for (auto element_info : raw_vertex_layout.GetElementInfoVector()) {
        OpenGLElementInfo opengl_element_info;

        opengl_element_info.index = element_info.index;
        opengl_element_info.size = element_info.size;
        opengl_element_info.normalized = element_info.normalized;
        opengl_element_info.stride = raw_vertex_layout.GetVertexByteSize();
        opengl_element_info.offset = element_info.offset;

        switch (element_info.type) {
            case MisakaTargetType::Float: opengl_element_info.type = GL_FLOAT; break;
            case MisakaTargetType::Int: opengl_element_info.type = GL_INT; break;
            case MisakaTargetType::UInt: opengl_element_info.type = GL_UNSIGNED_INT; break;
            case MisakaTargetType::Char: opengl_element_info.type = GL_BYTE; break;
            case MisakaTargetType::UChar: opengl_element_info.type = GL_UNSIGNED_BYTE; break;
            case MisakaTargetType::Int8: opengl_element_info.type = GL_BYTE; break;
            case MisakaTargetType::UInt8: opengl_element_info.type = GL_UNSIGNED_BYTE; break;
            case MisakaTargetType::Int16: opengl_element_info.type = GL_SHORT; break;
            case MisakaTargetType::UInt16: opengl_element_info.type = GL_UNSIGNED_SHORT; break;
            default: break;
        }

        opengl_buffer_layout.element_info_vector.push_back(opengl_element_info);
    }
    return opengl_buffer_layout;
}

OpenGLShader OpenGLAPI::CreateShader(RawShader raw_shader) {
    OpenGLShader opengl_shader_source;

    GLuint shader_id;
    switch (raw_shader.GetShaderType()) {
        case ShaderType::VertexShader:
            opengl_shader_source.shader_type = OpenGLShaderType::VertexShader;
            shader_id = glCreateShader(GL_VERTEX_SHADER);
            break;
        case ShaderType::FragmentShader:
            opengl_shader_source.shader_type = OpenGLShaderType::FragmentShader;
            shader_id = glCreateShader(GL_FRAGMENT_SHADER);
            break;
        default: break;
    }

    std::string shader_source = raw_shader.GetShaderSource();
    const char* shader_source_c_str = shader_source.c_str();
    glShaderSource(shader_id, 1, &shader_source_c_str, nullptr);

    glCompileShader(shader_id);

    GLint success;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader_id, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    opengl_shader_source.shader_id = shader_id;

    return opengl_shader_source;
}

OpenGLProgram OpenGLAPI::CreateProgram(std::vector<OpenGLShader> shader_vector) {
    OpenGLProgram opengl_program;

    GLuint program_id = glCreateProgram();
    for (auto shader_source : shader_vector) {
        glAttachShader(program_id, shader_source.shader_id);
    }
    glLinkProgram(program_id);

    GLint success;
    glGetProgramiv(program_id, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program_id, 512, nullptr, infoLog);
        std::cout << "ERROR::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
    }

    // TODO: the work of deleting shader will be done in another function, as the shader may be used by other programs
    // for (auto shader_source : shader_vector) {
    //     glDeleteShader(shader_source.shader_id);
    // }

    opengl_program.program_id = program_id;

    return opengl_program;
}

} // namespace RendererDemo
