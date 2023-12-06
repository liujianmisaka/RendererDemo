#pragma once

#include <memory>
#include <imgui.h>
#include "Runtime/Function/Renderer/RHI/RHITypes.hpp"
#include "Runtime/Function/Renderer/RHI/RHIStruct.hpp"
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
    virtual void Tick() = 0;

    virtual void GetImTextureID(ImTextureID& texture_id){};
    virtual void SetViewport(int width, int height){};

    virtual void CreateBuffer(RHIBufferCreateInfo create_info){};
    virtual void CreateVertexLayout(std::vector<RHIElementType> info){};
    virtual void CreateIndexDrawBuffer(){};
};

} // namespace RendererDemo
