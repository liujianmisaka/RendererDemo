#pragma once

#include <cstdint>
#include <memory>

#include "Runtime/Function/Renderer/RHI/RHI_Types.hpp"
#include "Runtime/Function/Renderer/RHI/RHI_Struct.hpp"
#include "Runtime/Function/Window/WindowSystem.hpp"
#include "Runtime/Resource/Manager/AssetManager.hpp"

namespace RendererDemo {

class GameWorldManager;

struct RHIInitInfo {
    std::shared_ptr<GameWorldManager> game_world_manager;
    std::shared_ptr<AssetManager> asset_manager;
    std::shared_ptr<WindowSystem> window_system;
};

class RHI {
public:
    virtual ~RHI() = default;

    virtual void Initialize(RHIInitInfo rhi_init_info) = 0;
    virtual void Clear(){};
    virtual void CreateBuffer(RHIBufferCreateInfo create_info){};
    virtual void CreateVertexLayout(std::vector<RHIElementType> info){};
    virtual void CreateIndexDrawBuffer(){};

    virtual void GetTextureOfRenderResult(uint64_t& texture_id){};

    virtual void Tick() = 0;

    /* -------------------------------------------------------------------------- */
    /*                                   Old API                                  */
    /* -------------------------------------------------------------------------- */

    virtual void DrawExample(){};

    // TODO: Add clear functions
};

} // namespace RendererDemo
