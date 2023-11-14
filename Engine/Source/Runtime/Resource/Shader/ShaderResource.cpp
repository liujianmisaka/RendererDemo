#include "Runtime/Resource/Shader/ShaderResource.hpp"
#include <cstdint>
#include <string>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <unordered_map>
#include "Runtime/Function/Renderer/RHI/opengl/OpenGLAPI.hpp"

namespace RendererDemo {

void ShaderResource::Initialize() {
    LoadPredefinedShaders();
};

void ShaderResource::AddVertexShader(std::string shader_name, uint32_t shader_id) {
    if (m_vertex_shaders.find(shader_name) != m_vertex_shaders.end()) {
        std::cerr << "Warn: Shader already exists, replaced!" << std::endl;
    }
    m_vertex_shaders[shader_name] = shader_id;
}

void ShaderResource::AddFragmentShader(std::string shader_name, uint32_t shader_id) {
    if (m_fragment_shaders.find(shader_name) != m_fragment_shaders.end()) {
        std::cerr << "Warn: Shader already exists, replaced!" << std::endl;
    }
    m_fragment_shaders[shader_name] = shader_id;
}

uint32_t ShaderResource::GetShaderWithName(std::string shader_name, int type) {
    if (type == 0) {
        return m_vertex_shaders[shader_name];
    } else {
        return m_fragment_shaders[shader_name];
    }
}

void ShaderResource::LoadPredefinedShaders() {
    std::filesystem::current_path("C:/dev/RendererDemo");
    std::string shader_dir = "C:/dev/RendererDemo/Engine/Shaders/GLSL/";
    for (const auto& entry : std::filesystem::directory_iterator(shader_dir)) {
        if (entry.is_regular_file()) {
            std::string shader_name = entry.path().stem().string();
            std::string shader_ext = entry.path().extension().string();
            std::string shader_path = entry.path().string();
            std::string shader_source = LoadFile(shader_path);
            uint32_t shader_id;
            if (shader_ext == ".vert") {
                shader_id = OpenGLAPI::CreateVertexShader(shader_source.c_str());
                AddVertexShader(shader_name, shader_id);
            } else if (shader_ext == ".frag") {
                shader_id = OpenGLAPI::CreateFragmentShader(shader_source.c_str());
                AddFragmentShader(shader_name, shader_id);
            }
        }
    }

    // create shader program if vertex and fragment shader exists
    for (auto& vertex_shader : m_vertex_shaders) {
        if (m_fragment_shaders.find(vertex_shader.first) != m_fragment_shaders.end()) {
            uint32_t shader_program_id =
                OpenGLAPI::CreateProgram(vertex_shader.second, m_fragment_shaders[vertex_shader.first]);
            m_programs[vertex_shader.first] = shader_program_id;
        }
    }
}

std::string ShaderResource::LoadFile(std::string path) {
    std::string source;
    std::ifstream shader_file(path, std::ios::in | std::ios::binary);
    if (shader_file.is_open()) {
        shader_file.seekg(0, std::ios::end);
        source.resize(shader_file.tellg());
        shader_file.seekg(0, std::ios::beg);
        shader_file.read(&source[0], source.size());
        shader_file.close();
    }
    return source;
}

} // namespace RendererDemo
