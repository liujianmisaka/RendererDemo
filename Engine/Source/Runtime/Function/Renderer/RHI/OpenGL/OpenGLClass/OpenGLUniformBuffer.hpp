#pragma once

#include <cstdint>
#include "Runtime/Function/Renderer/RHI/RHIClass.hpp"
#include "Runtime/Function/Renderer/RHI/OpenGL/OpenGLAPI.hpp"

namespace RendererDemo {

class OpenGLUniformBuffer : public RHIUniformBuffer {
public:
    OpenGLUniformBuffer() {
        glGenBuffers(1, &m_ubo_id);
        glBindBuffer(GL_UNIFORM_BUFFER, m_ubo_id);
        glBufferData(GL_UNIFORM_BUFFER, 0, nullptr, GL_STATIC_DRAW);
    }
    virtual ~OpenGLUniformBuffer() { glDeleteBuffers(1, &m_ubo_id); }

    void Bind() { glBindBuffer(GL_UNIFORM_BUFFER, m_ubo_id); }
    void UnBind() { glBindBuffer(GL_UNIFORM_BUFFER, 0); }

    explicit operator uint32_t() const { return m_ubo_id; }

private:
    uint32_t m_ubo_id;
};

} // namespace RendererDemo
