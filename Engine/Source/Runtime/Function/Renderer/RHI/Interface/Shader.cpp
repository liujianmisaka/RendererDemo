#include "Runtime/Function/Renderer/RHI/Interface/Shader.hpp"

#include <fstream>

namespace RendererDemo {

RawShader::RawShader(ShaderInfo shader_info)
    : m_shader_path(shader_info.shader_path), m_shader_type(shader_info.shader_type) {
    LoadShader();
}

void RawShader::LoadShader() {
    std::ifstream shader_file(m_shader_path, std::ios::in | std::ios::binary);
    if (shader_file.is_open()) {
        shader_file.seekg(0, std::ios::end);
        m_shader_source.resize(shader_file.tellg());
        shader_file.seekg(0, std::ios::beg);
        shader_file.read(&m_shader_source[0], m_shader_source.size());
        shader_file.close();
    }
}

} // namespace RendererDemo
