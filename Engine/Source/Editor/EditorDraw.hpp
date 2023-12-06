#pragma once

#include <memory>
#include "Editor/UI/EditorUI.hpp"
#include "Runtime/Function/Renderer/RHI/RHI.hpp"
#include "Runtime/Function/Framework/Manager/GameWorldManager.hpp"

namespace RendererDemo {

struct EditorDrawInitInfo {
    std::shared_ptr<RHI> rhi;
    std::shared_ptr<GameWorldManager> game_world_manager;
    std::shared_ptr<EditorUI> editor_ui;
};

class EditorDraw {
public:
    EditorDraw() = default;
    ~EditorDraw() = default;

    void Initialize(EditorDrawInitInfo init_info);
    void Clear();

    void Tick();

    void InitDraw();
    void RuntimeDraw();

private:
    std::shared_ptr<RHI> m_rhi;
    std::shared_ptr<GameWorldManager> m_game_world_manager;

    std::shared_ptr<EditorUI> m_editor_ui;
};

} // namespace RendererDemo
