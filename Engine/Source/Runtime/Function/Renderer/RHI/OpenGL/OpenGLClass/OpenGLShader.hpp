#pragma once

#include <string>
#include "Runtime/Function/Renderer/RHI/RHIClass.hpp"
#include "Runtime/Function/Renderer/RHI/OpenGL/OpenGLAPI.hpp"

namespace RendererDemo {

class OpenGLShader : public RHIShader {
public:
    OpenGLShader() = default;
    virtual ~OpenGLShader() = default;

    void Create(const std::string& vertex_shader_source, const std::string& fragment_shader_source) {
        auto vertex_shader_id = OpenGLAPI::CreateVertexShader(vertex_shader_source.c_str());
        auto fragment_shader_id = OpenGLAPI::CreateFragmentShader(fragment_shader_source.c_str());
        m_program_id = OpenGLAPI::CreateProgram(vertex_shader_id, fragment_shader_id);
    }
    void Destroy() { glDeleteProgram(m_program_id); }

    void Bind() const { glUseProgram(m_program_id); }
    void Unbind() const { glUseProgram(0); }

    explicit operator uint32_t() const { return m_program_id; }

private:
    uint32_t m_program_id;
};

} // namespace RendererDemo
