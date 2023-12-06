#pragma once

#include <cstdint>
#include "Runtime/Function/Renderer/RHI/RHIClass.hpp"
#include "Runtime/Function/Renderer/RHI/OpenGL/OpenGLAPI.hpp"

namespace RendererDemo {

class OpenGLFramebuffer : public RHIFramebuffer {
public:
    OpenGLFramebuffer() = default;

    virtual ~OpenGLFramebuffer() = default;

    void Create() {
        glGenFramebuffers(1, &m_fbo_id);
        Bind();
    }
    void Destroy() { glDeleteFramebuffers(1, &m_fbo_id); }
    void Bind() { glBindFramebuffer(GL_FRAMEBUFFER, m_fbo_id); }
    void UnBind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

    void Clear() {
        Bind();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 1.0f, 0.5f);
    }

    void BindTexture2D(uint32_t texture_id) {
        Bind();
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_id, 0);
    }

    explicit operator uint32_t() const { return m_fbo_id; }

private:
    uint32_t m_fbo_id;
};

} // namespace RendererDemo
