#pragma once

#include <memory>
#include <string>

#include "Runtime/Resource/Shader/ShaderResource.hpp"

namespace RendererDemo {

class ShaderResource;

class AssetManager {
public:
    AssetManager() = default;
    ~AssetManager() = default;

    void Initialize();
    void Clear(){};

    uint32_t GetProgram(std::string name) {
        return m_shader_hanlder->GetProgram(name);
    }

private:
    std::shared_ptr<ShaderResource> m_shader_hanlder;
};

} // namespace RendererDemo
