#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdint>
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

    virtual void CreateBuffer(BufferInfo buffer_info) override;
    virtual void CreateVertexLayout(RawVertexLayout raw_vertex_buffer_layout) override;
	virtual void CreateVertexArray() override;

    virtual void CreateShader(ShaderInfo shader_info) override;
    virtual void CreateProgram() override;

    virtual void Tick() override;

	virtual void DrawExample() override;

private:
    GLFWwindow* m_window;

    OpenGLBuffer m_vertex_buffer;
    OpenGLBuffer m_index_buffer;
    OpenGLBuffer m_uniform_buffer;
	uint32_t m_vertex_array;
    OpenGLVertexBufferLayout m_vertex_buffer_layout;
	std::vector<OpenGLShader> m_shaders;
	OpenGLProgram m_program;
};

} // namespace RendererDemo
