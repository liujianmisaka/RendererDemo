#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdint>
#include <vector>

#include "Runtime/Function/Renderer/RHI/RHIStruct.hpp"

namespace RendererDemo {

class OpenGLAPI {
public:
    // Basic OpenGL API
    static uint32_t CreateVertexBuffer(uint32_t buffer_size, const void* buffer_data);
    static uint32_t CreateIndexBuffer(uint32_t buffer_size, const void* buffer_data);
    static uint32_t CreateUniformBuffer(uint32_t buffer_size, const void* buffer_data);
    static void UnloadUniformBuffer(uint32_t buffer_id);
    static RHIVertexLayout CreateVertexLayout(std::vector<RHIElementType> info);
    static uint32_t CreateVertexArray(uint32_t vertex_buffer_id, uint32_t index_buffer_id, RHIVertexLayout layout);
    static uint32_t CreateVertexShader(const char* shader_source);
    static uint32_t CreateFragmentShader(const char* shader_source);
    static uint32_t CreateProgram(uint32_t vertex_shader_id, uint32_t fragment_shader_id);
    // static uint32_t CreateTexture();

private:
    static GLenum GetOpenGLDataTypeFromRHIDataType(RHIDataType type);
};

} // namespace RendererDemo
