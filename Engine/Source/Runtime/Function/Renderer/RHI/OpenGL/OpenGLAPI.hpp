#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "Runtime/Core/Base/Types.hpp"
#include "Runtime/Function/Renderer/RHI/Interface/Buffer.hpp"
#include "Runtime/Function/Renderer/RHI/Interface/Layout.hpp"
#include "Runtime/Function/Renderer/RHI/Interface/Shader.hpp"
#include "Runtime/Function/Renderer/RHI/OpenGL/OpenGL_Resource.hpp"

namespace RendererDemo {

class OpenGLAPI {
public:
    static OpenGLBuffer CreateBuffer(BufferCreateInfo create_info);

    static OpenGLVertexBufferLayout CreateVertexLayout(VertexLayoutCreateInfo create_info);

	static OpenGLVertexArray CreateVertexArray(OpenGLVertexArrayCreateInfo create_info);

    static OpenGLShader CreateShader(ShaderCreateInfoInfo create_info);

    static OpenGLProgram CreateProgram(std::vector<OpenGLShader> shader_vector);

    static OpenGLIndexDrawBuffer CreateIndexDrawBuffer(OpenGLIndexDrawBufferCreateInfo create_info);

private:
    static uint32_t GetUnitSizeFromDataType(MisakaDataType data_type);
};

} // namespace RendererDemo
