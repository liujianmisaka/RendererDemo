#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Runtime/Function/Renderer/RHI/RHI.hpp"

namespace RendererDemo {

class OpenGLRHI : public RHI {
public:
    OpenGLRHI(){};
    virtual ~OpenGLRHI() = default;

    virtual void Initialize(RHIInitInfo rhi_init_info) override;

    virtual void Render() override;

private:
    GLFWwindow* m_window;
	
};

} // namespace RendererDemo
