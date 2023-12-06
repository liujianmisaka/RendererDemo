#pragma once

#include <cstdint>
#include "Runtime/Function/Renderer/RHI/RHIClass.hpp"
#include "Runtime/Function/Renderer/RHI/OpenGL/OpenGLAPI.hpp"

namespace RendererDemo {

class OpenGLSampler : public RHISampler {
public:
    OpenGLSampler() = default;
    virtual ~OpenGLSampler() = default;

    void Create() {
        glGenSamplers(1, &m_sampler_id);
        // glSamplerParameteri(m_sampler_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
        // glSamplerParameteri(m_sampler_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // glSamplerParameteri(m_sampler_id, GL_TEXTURE_WRAP_R, GL_REPEAT);
        glSamplerParameteri(m_sampler_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        // glSamplerParameteri(m_sampler_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    void Destroy() { glDeleteSamplers(1, &m_sampler_id); }
    void Bind(uint32_t texture_id) { glBindSampler(texture_id, m_sampler_id); }
    void UnBind(uint32_t texture_id) { glBindSampler(texture_id, 0); }

    explicit operator uint32_t() const { return m_sampler_id; }

private:
    uint32_t m_sampler_id;
};

} // namespace RendererDemo
