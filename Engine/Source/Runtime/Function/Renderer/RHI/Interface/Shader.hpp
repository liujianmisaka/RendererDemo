#pragma once

#include <string>
#include <fstream>

namespace RendererDemo {

enum class ShaderType { VertexShader, FragmentShader };
enum class ShaderFileType { Text, Binary };

class OpenGLAPI;
class OpenGLRHI;

class ShaderCreateInfoInfo {
    friend class RendererDemo::OpenGLAPI;
    friend class RendererDemo::OpenGLRHI;

public:
    ShaderCreateInfoInfo&& SetShaderType(ShaderType shader_type) {
        this->m_shader_type = shader_type;
        return std::move(*this);
    }

    ShaderCreateInfoInfo&& SetShaderFileType(ShaderFileType shader_file_type) {
        this->m_shader_file_type = shader_file_type;
        return std::move(*this);
    }

    ShaderCreateInfoInfo&& SetShaderPath(std::string shader_path) {
        LoadShader(shader_path);
        return std::move(*this);
    }

private:
    void LoadShader(std::string shader_path) {
        std::ifstream shader_file(shader_path, std::ios::in | std::ios::binary);
        if (shader_file.is_open()) {
            shader_file.seekg(0, std::ios::end);
            m_shader_source.resize(shader_file.tellg());
            shader_file.seekg(0, std::ios::beg);
            shader_file.read(&m_shader_source[0], m_shader_source.size());
            shader_file.close();
        }
    }

private:
    ShaderType m_shader_type;
    ShaderFileType m_shader_file_type = ShaderFileType::Text;
    std::string m_shader_source;
};

} // namespace RendererDemo
