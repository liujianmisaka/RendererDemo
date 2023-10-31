#pragma once

#include <string>

namespace RendererDemo {

enum class ShaderType { VertexShader, FragmentShader };
enum class ShaderFileType { Text, Binary };

struct ShaderInfo {
    ShaderType shader_type;
    ShaderFileType shader_file_type;
    std::string shader_path;

    ShaderInfo&& SetShaderType(ShaderType shader_type) {
        this->shader_type = shader_type;
        return std::move(*this);
    }

    ShaderInfo&& SetShaderFileType(ShaderFileType shader_file_type) {
        this->shader_file_type = shader_file_type;
        return std::move(*this);
    }

    ShaderInfo&& SetShaderPath(std::string shader_path) {
        this->shader_path = shader_path;
        return std::move(*this);
    }
};

class RawShader {
public:
    // Shader() = default;   // TODO: add default shader
    RawShader(ShaderInfo shader_info);
    ~RawShader() = default;

    std::string GetShaderSource() {
        return m_shader_source;
    }
    ShaderType GetShaderType() {
        return m_shader_type;
    }
    std::string GetShaderPath() {
        return m_shader_path;
    }

private:
    void LoadShader();

private:
    std::string m_shader_path;
    ShaderType m_shader_type;
    std::string m_shader_source;
};

} // namespace RendererDemo
