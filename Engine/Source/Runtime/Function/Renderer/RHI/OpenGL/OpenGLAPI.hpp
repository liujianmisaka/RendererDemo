#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "Runtime/Function/Renderer/RHI/Interface/Buffer.hpp"
#include "Runtime/Function/Renderer/RHI/Interface/Layout.hpp"
#include "Runtime/Function/Renderer/RHI/Interface/Shader.hpp"
#include "Runtime/Function/Renderer/RHI/OpenGL/OpenGL_Resource.hpp"

namespace RendererDemo {

class OpenGLAPI {
public:
    static OpenGLBuffer CreateBuffer(BufferInfo buffer_info);

    static OpenGLVertexBufferLayout CreateVertexLayout(RawVertexLayout raw_vertex_layout);

	static OpenGLShader CreateShader(RawShader raw_shader);

	static OpenGLProgram CreateProgram(std::vector<OpenGLShader> shader_vector);
};

} // namespace RendererDemo
