#pragma once

#include <cstdint>
#include "Runtime/Function/Renderer/RHI/RHIClass.hpp"
#include "Runtime/Function/Renderer/RHI/OpenGL/OpenGLAPI.hpp"

namespace RendererDemo {

class OpenGLTexture1D : public RHIImage {
public:
    OpenGLTexture1D() = default;
    virtual ~OpenGLTexture1D() = default;

    void Create() {
        glGenTextures(1, &m_texture_id);
        glBindTexture(GL_TEXTURE_1D, m_texture_id);
        glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    }
    void Destroy() { glDeleteTextures(1, &m_texture_id); }

    void Bind() { glBindTexture(GL_TEXTURE_1D, m_texture_id); }
    void UnBind() { glBindTexture(GL_TEXTURE_1D, 0); }

    explicit operator uint32_t() const { return m_texture_id; }
    explicit operator uint64_t() const { return (uint64_t)m_texture_id; }

private:
    uint32_t m_texture_id;
};

class OpenGLTexture2D : public RHIImage {
public:
    OpenGLTexture2D() = default;
    virtual ~OpenGLTexture2D() = default;

    void Create() {
        glGenTextures(1, &m_texture_id);
        Bind();
    }
    void Destroy() { glDeleteTextures(1, &m_texture_id); }
    void Bind() { glBindTexture(GL_TEXTURE_2D, m_texture_id); }
    void UnBind() { glBindTexture(GL_TEXTURE_2D, 0); }

    void TexImage2D(int width, int height) {
        Bind();
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    }

    explicit operator uint32_t() const { return m_texture_id; }
    explicit operator uint64_t() const { return (uint64_t)m_texture_id; }

private:
    uint32_t m_texture_id = 0;
};

class OpenGLTexture3D : public RHIImage {
public:
    OpenGLTexture3D() = default;
    virtual ~OpenGLTexture3D() = default;

    void Create() {
        glGenTextures(1, &m_texture_id);
        glBindTexture(GL_TEXTURE_3D, m_texture_id);
        glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, 1, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    }
    void Destroy() { glDeleteTextures(1, &m_texture_id); }

    void Bind() { glBindTexture(GL_TEXTURE_3D, m_texture_id); }
    void UnBind() { glBindTexture(GL_TEXTURE_3D, 0); }

    explicit operator uint32_t() const { return m_texture_id; }
    explicit operator uint64_t() const { return (uint64_t)m_texture_id; }

private:
    uint32_t m_texture_id;
};

} // namespace RendererDemo
