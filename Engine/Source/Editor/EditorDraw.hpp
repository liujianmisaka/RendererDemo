#pragma once

#include <memory>
#include "Runtime/Function/Renderer/RHI/RHI.hpp"
#include "Runtime/Function/Framework/Manager/GameWorldManager.hpp"

namespace RendererDemo {

class EditorDraw {
public:
    EditorDraw() = default;
    ~EditorDraw() = default;

    void Initialize(std::shared_ptr<RHI> rhi, std::shared_ptr<GameWorldManager> game_world_manager);
    void Clear();

    void Tick();

    void InitDraw();
    void RuntimeDraw();

private:
    std::shared_ptr<RHI> m_rhi;
    std::shared_ptr<GameWorldManager> m_game_world_manager;
};

} // namespace RendererDemo
