#include "Runtime/Function/Renderer/RenderSystem.hpp"
#include <memory>
#include <stdexcept>

#include "Runtime/Function/Renderer/RHI/RHI.hpp"
#include "Runtime/Function/Renderer/RHI/OpenGL/OpenGLRHI.hpp"

namespace RendererDemo {

void RendererSystem::Initialize(RendererSystemInitInfo render_system_init_info) {
    m_rhi = CreateGrapicsAPIInstance(render_system_init_info.graphics_api);
    RHIInitInfo rhi_init_info;
    rhi_init_info.game_world_manager = render_system_init_info.game_world_manager;
    rhi_init_info.asset_manager = render_system_init_info.asset_manager;
    rhi_init_info.window_system = render_system_init_info.window_system;
    m_rhi->Initialize(rhi_init_info);
}

void RendererSystem::Clear(){};

void RendererSystem::Tick(float ts) { m_rhi->Tick(); }

/* -------------------------------------------------------------------------- */
/*                                private apis                                */
/* -------------------------------------------------------------------------- */

std::shared_ptr<RHI> RendererSystem::CreateGrapicsAPIInstance(GraphicsAPI api) {
    if (api == GraphicsAPI::OpenGL) {
        return std::make_shared<OpenGLRHI>();
    } else {
        throw std::runtime_error("No such graphics api.");
    }
}

} // namespace RendererDemo
