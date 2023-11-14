#include "Runtime/Resource/Manager/AssetManager.hpp"
#include "Runtime/Resource/Shader/ShaderResource.hpp"

namespace RendererDemo {

void AssetManager::Initialize() {
    m_shader_hanlder = std::make_shared<ShaderResource>();
    m_shader_hanlder->Initialize();
}

} // namespace RendererDemo
