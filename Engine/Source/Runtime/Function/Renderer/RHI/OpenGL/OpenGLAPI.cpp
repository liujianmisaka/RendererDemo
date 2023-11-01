#include "Runtime/Function/Renderer/RHI/OpenGL/OpenGLAPI.hpp"
#include "Runtime/Function/Renderer/RHI/Interface/Buffer.hpp"
#include "Runtime/Function/Renderer/RHI/OpenGL/OpenGL_Resource.hpp"

#include <cassert>
#include <cstdint>
#include <iostream>

namespace RendererDemo {

OpenGLBuffer OpenGLAPI::CreateBuffer(BufferCreateInfo create_info) {
    OpenGLBuffer opengl_buffer;

    opengl_buffer.buffer_byte_size = create_info.m_buffer_byte_size;
    opengl_buffer.buffer_unit_size = GetUnitSizeFromDataType(create_info.m_buffer_data_type);

    // Generate a new buffer in gpu and get the buffer id
    glGenBuffers(1, &opengl_buffer.buffer_id);

    // Determine the buffer target based on the buffer type
    GLenum buffer_target;
    switch (create_info.m_buffer_type) {
        case BufferType::VertexBuffer:
            buffer_target = GL_ARRAY_BUFFER;
            opengl_buffer.buffer_type = OpenGLBufferType::VertexBuffer;
            if (opengl_buffer.buffer_unit_size == 0) opengl_buffer.buffer_unit_size = sizeof(float);
            break;
        case BufferType::IndexBuffer:
            buffer_target = GL_ELEMENT_ARRAY_BUFFER;
            opengl_buffer.buffer_type = OpenGLBufferType::IndexBuffer;
            if (opengl_buffer.buffer_unit_size == 0) opengl_buffer.buffer_unit_size = sizeof(unsigned int);
            break;
        case BufferType::UniformBuffer:
            buffer_target = GL_UNIFORM_BUFFER;
            opengl_buffer.buffer_type = OpenGLBufferType::UniformBuffer;
            // TODO: the buffer_unit_size of uniform buffer may not determined yet
            break;
    }

    assert(opengl_buffer.buffer_unit_size != 0);

    opengl_buffer.buffer_number_count =
        create_info.m_buffer_byte_size / opengl_buffer.buffer_unit_size; // data size / data unit size = data number

    // bind the gpu buffer memory to the buffer type and map the buffer data from cpu to gpu
    glBindBuffer(buffer_target, opengl_buffer.buffer_id);
    glBufferData(buffer_target, create_info.m_buffer_byte_size, create_info.m_buffer_data, GL_STATIC_DRAW);

    return opengl_buffer;
}

OpenGLVertexBufferLayout OpenGLAPI::CreateVertexLayout(VertexLayoutCreateInfo create_info) {
    OpenGLVertexBufferLayout opengl_buffer_layout;
    for (auto element_info : create_info.m_element_info_vector) {
        OpenGLElementInfo opengl_element_info;

        opengl_element_info.index = element_info.index;
        opengl_element_info.size = element_info.size;
        opengl_element_info.normalized = element_info.normalized;
        opengl_element_info.stride = create_info.m_vertex_byte_size;
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

OpenGLVertexArray OpenGLAPI::CreateVertexArray(OpenGLVertexArrayCreateInfo create_info) {
    OpenGLVertexArray vertex_array;

    glGenVertexArrays(1, &vertex_array.vertex_array_id);
    glBindVertexArray(vertex_array.vertex_array_id);
    glBindBuffer(GL_ARRAY_BUFFER, create_info.vertex_buffer.buffer_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, create_info.index_buffer.buffer_id);
    for (auto& element_info : create_info.vertex_buffer_layout.element_info_vector) {
        glEnableVertexAttribArray(element_info.index);
        glVertexAttribPointer(element_info.index, element_info.size, element_info.type, element_info.normalized,
                              element_info.stride, (void*)element_info.offset);
    }
    glBindVertexArray(0);
    return vertex_array;
}

OpenGLShader OpenGLAPI::CreateShader(ShaderCreateInfoInfo create_info) {
    OpenGLShader opengl_shader_source;

    GLuint shader_id;
    switch (create_info.m_shader_type) {
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

    std::string shader_source = create_info.m_shader_source;
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

OpenGLIndexDrawBuffer OpenGLAPI::CreateIndexDrawBuffer(OpenGLIndexDrawBufferCreateInfo create_info) {
    OpenGLIndexDrawBuffer draw_buffer;

    draw_buffer.draw_mode = create_info.draw_mode;
    draw_buffer.index_count = create_info.index_buffer.buffer_number_count;
    draw_buffer.index_offset = 0; // TODO: support index offset in glDrawElements
    draw_buffer.vertex_array_id = create_info.vertex_array.vertex_array_id;
    draw_buffer.program_id = create_info.program.program_id;
    // draw_buffer.index_type = create_info.index_buffer.buffer_data_type;
    assert(create_info.index_buffer.buffer_type == OpenGLBufferType::IndexBuffer);
    switch (sizeof(create_info.index_buffer.buffer_unit_size)) {
        case 2: {
            draw_buffer.index_type = GL_UNSIGNED_SHORT;
            break;
        }
        case 4: {
            draw_buffer.index_type = GL_UNSIGNED_INT;
            break;
        }
        default: assert(false); break;
    }

    return draw_buffer;
}

/* -------------------------------------------------------------------------- */
/*                              Private Functions                             */
/* -------------------------------------------------------------------------- */

uint32_t OpenGLAPI::GetUnitSizeFromDataType(MisakaDataType data_type) {
    switch (data_type) {
        case MisakaDataType::Float: return sizeof(float);
        case MisakaDataType::Int: return sizeof(int);
        case MisakaDataType::UInt: return sizeof(unsigned int);
        case MisakaDataType::Char: return sizeof(char);
        case MisakaDataType::UChar: return sizeof(unsigned char);
        case MisakaDataType::Int8: return sizeof(int8_t);
        case MisakaDataType::UInt8: return sizeof(uint8_t);
        case MisakaDataType::Int16: return sizeof(int16_t);
        case MisakaDataType::UInt16: return sizeof(uint16_t);
        default: return 0;
    }
}

} // namespace RendererDemo
