#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "Runtime/Function/Renderer/RHI/OpenGL/OpenGL_Resource.hpp"
#include "Runtime/Function/Renderer/RHI/RHI.hpp"
#include "Runtime/Function/Renderer/RHI/OpenGL/OpenGLAPI.hpp"

namespace RendererDemo {

class OpenGLRHI : public RHI {
public:
    OpenGLRHI(){};
    virtual ~OpenGLRHI() = default;

    virtual void Initialize(RHIInitInfo rhi_init_info) override;

    virtual void CreateBuffer(BufferCreateInfo create_info) override;
    virtual void CreateVertexLayout(VertexLayoutCreateInfo create_info) override;
    virtual void CreateVertexArray() override;

    virtual void CreateShader(ShaderCreateInfoInfo create_info) override;
    virtual void CreateProgram() override;
	virtual void CreateIndexDrawBuffer() override;

    virtual void Tick() override;

    virtual void DrawExample() override;

private:
    GLFWwindow* m_window;

    OpenGLBuffer m_vertex_buffer;
    OpenGLBuffer m_index_buffer;
    OpenGLBuffer m_uniform_buffer;
    OpenGLVertexArray m_vertex_array;
    OpenGLVertexBufferLayout m_vertex_buffer_layout;
    std::vector<OpenGLShader> m_shaders;
    OpenGLProgram m_program;
	std::vector<OpenGLIndexDrawBuffer> m_draw_buffers;
	int m_draw_buffer_index = 0;
};

} // namespace RendererDemo
