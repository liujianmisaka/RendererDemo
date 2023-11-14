#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Runtime/Function/Renderer/RHI/RHI_Struct.hpp"

namespace RendererDemo {

class OpenGLBuffer : public RHIBuffer {
public:
    void SetResource(GLuint res) { m_resource = res; }
    GLuint GetResource() { return m_resource; }

private:
    GLuint m_resource;
};

} // namespace RendererDemo
