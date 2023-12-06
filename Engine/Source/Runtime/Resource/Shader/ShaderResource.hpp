#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>
namespace RendererDemo {

// TODO: now can only load shader when initialize, need to support load shader at runtime.
// TODO: now use OpenGLAPI directly, need to abstract to support other graphics api.
class ShaderResource {
public:
    ShaderResource() = default;
    ~ShaderResource() = default;

    void Initialize();

    // TODO: export those function to editor
    void AddVertexShader(std::string shader_name, uint32_t shader_id);
    void AddFragmentShader(std::string shader_name, uint32_t shader_id);
    uint32_t GetShaderWithName(std::string shader_name, int type);
    uint32_t GetProgram(std::string name) { return m_programs[name]; }

    std::vector<uint32_t> GetProgramVector() {
        std::vector<uint32_t> program_vector;
        for (auto& program : m_programs) {
            program_vector.push_back(program.second);
        }
        return program_vector;
    }

private:
    // NOTE: load all pre-defined shaders
    void LoadPredefinedShaders();

    std::string LoadFile(std::string path);

private:
    // TODO: use binary shader
    std::unordered_map<std::string, uint32_t> m_vertex_shaders;
    std::unordered_map<std::string, uint32_t> m_fragment_shaders;
    std::unordered_map<std::string, uint32_t> m_programs;
};

} // namespace RendererDemo
